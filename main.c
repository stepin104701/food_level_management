#include<stdio.h>
#include<conio.h>
#include<string.h>

#include<stdlib.h>
void administration();
void customer();
void mainmenu();
void addrecord(void);
void deleterecord(void);
void viewrecord(void);
int getdata();
int vtotal=0;
int nvtotal=0;
void vegetarian(void);
void nonvegetarian(void);



int s;
char findrecord;
int again;
int quantity;
double total=0;
int t;


struct employee
{

	char name[30];
	int id;
	//char DOB[10];
	int dd; int mm; int yyyy;
	float salary;
	char department[20];

	int quantity;
};
struct employee e;

FILE *fp,*ft,*dp,*dt;

int main(){
	mainmenu();
	return 0;
}
void mainmenu(void)
{
	printf("Welcome to ABC hotel");
	printf("Enter your choice \n1.admin \n2.customer\n");
	int choice;
	scanf("%d",&choice);
	if(choice==1)
	{
		administration();
	}
	else if(choice==2)
	{
		customer();
	}
	else
	{
		exit(0);
	}
}
void administration(void)
{
	system("cls");
	printf("Enter your choice \n1.Add record \n2.Delete record \n3.View record \n4.Exit \n");
	int n;
	scanf("%d",&n);
		printf("\n\n");
	if(n==1)
	{
		addrecord();
	}
	else if(n==2)
	{
		deleterecord();
	}
	else if(n==3)
	{
		viewrecord();
	}
	else if(n==4)
	{
		mainmenu();
	}

}
void addrecord(void)
{
	system("cls");
	fp=fopen("record1.txt","a");
	if(getdata()==1)
	{
		fseek(fp,0,SEEK_END);
		fwrite(&e,sizeof(e),1,fp);
		fclose(fp);
		printf("\n\n");
		printf("The Record Is Successfully Saved ! !\n\n");
		//printf("Save any more?(Y / N): ");
		//if(getch()=='n')
        administration();
		//else
	    	//system("cls");
	    	//addrecord();
	}
}


void deleterecord(void)
{
	system("cls");
    int d;
    char another='y';
    while(another=='y')  //infinite loop
    {
	system("cls");
	printf("Enter The Employee ID To Delete :\n");
	scanf(" %d",&d);
	fp=fopen("record1.txt","r+");
	rewind(fp);
	while(fread(&e,sizeof(e),1,fp)==1)
	{
	    if(e.id==d)
	    {
			findrecord='t';
	    }
	}
	if(findrecord!='t')
	{
	    printf("No record is found\n\n");
	}
	if(findrecord=='t' )
	{
			ft=fopen("test1.txt","w");  //temporary file for delete
			rewind(fp);
			while(fread(&e,sizeof(e),1,fp)==1)
			{
		    	if(e.id!=d)
		    	{
					fseek(ft,0,SEEK_CUR);
					fwrite(&e,sizeof(e),1,ft); //write all in tempory file except that
		    	}                              //we want to delete
			}
			fclose(ft);
			fclose(fp);
			remove("record1.txt");
			rename("test1.txt","record1.txt"); //copy all item from temporary file to fp except that
	}
}
administration();
}

void viewrecord(void)
{
    system("cls");
    printf("Employee Details\n\n");
    printf("                 DEPARTMENT        ID        EMPLOYEE NAME        D.O.B\n\n");

    fp=fopen("record1.txt","r");
    while(fread(&e,sizeof(e),1,fp)==1)
    {
		printf("                 %s",e.department);
		printf("        %d",e.id);
		printf("        %s",e.name);
		printf("        %d/%d/%d",e.dd,e.mm,e.yyyy);
		printf("\n\n");
	}

      fclose(fp);
      returnfunc();
}


void customer(void)
{

	system("cls");
	printf("Enter Your choice\n\n");
	printf("1.Veg\n 2.Non veg\n");
	int k;
	scanf("%d",&k);
	if(k==1)
	{
		system("cls");
		vegetarian();
	}
	else if(k==2)
	{
		system("cls");
		nonvegetarian();
	}
	else
	{
		printf("Wrong Input !Please Re-enter The Correct Option......\n\n");
		exit(0);
	}
}
void vegetarian(void)
{
	printf("MENU \n1.rice 100rs \n2.chapati 50rs \n3.curry 100rs \n4.Exit \n");
	int vchoice;
	scanf("%d",&vchoice);
	if(vchoice==1)
	{
		vtotal+=100;
		printf("%d",vtotal);
		vegetarian();
	}
	else if(vchoice==2)
	{
		vtotal+=50;
		printf("%d",vtotal);
		vegetarian();
	}
	else if(vchoice==3)
	{
		vtotal+=100;
		printf("%d",vtotal);
		vegetarian();
	}
	else if(vchoice==4)
	{
		exit(0);
	}
}

void nonvegetarian(void)
{
	printf("MENU \n1.rice 100rs \n2.puri 50rs \n3.chicken 100rs \n4.Exit \n");
	int nvchoice;
	scanf("%d",&nvchoice);
	if(nvchoice==1)
	{
		nvtotal+=100;
		printf("%d",nvtotal);
		nonvegetarian();
	}
	else if(nvchoice==2)
	{
		nvtotal+=50;
		printf("%d",nvtotal);
		nonvegetarian();
	}
	else if(nvchoice==3)
	{
		nvtotal+=100;
		printf("%d",nvtotal);
		nonvegetarian();
	}
	else if(nvchoice==4)
	{
		exit(0);
	}
}

void returnfunc(void)
{
    {
		printf(" Press ENTER to return to main menu");
    }
    e:
    if(getch()==13) //allow only use of enter
    administration();
    else
    goto e;
}

int getdata()
{
	//*int t;
	printf("        Employee ID :\t");
	scanf("%d",&t);
	if(checkid(t)==0)
	{
		printf("\n\n");
		printf("\a                        The Employee Record Already Exists !!!\a");
		getch();
		mainmenu();
		return 0;
	}
	e.id=t;
	printf("        Employee Name : ");
	scanf("%s",e.name);
	printf("        Date Of Birth (dd/mm/yyyy) :");
	scanf("%d/%d/%d",&e.dd,&e.mm,&e.yyyy);
	printf("        Department :");
	scanf("%s",e.department);
	return 1;
}

int checkid(int c)  //check whether the record is exist in list or not
{
	rewind(fp);
	while(fread(&e,sizeof(e),1,fp)==1)
	if(e.id==c)

	return 0;  //returns 0 if employee exits

	return 1; //return 1 if it not
}


