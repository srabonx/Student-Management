#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

using std::string;

void menu(void);
void add_data(void);
void stu_info(FILE *myFile,int roll,string name);
void view_data(void);
void remove_single_data(void);
void remove_data(void);
void update_data(void);
void search_data(void);
void add_marks(void);
void subjects(FILE *myFile);
void functions(void);
void land_page(void);
void stu_login(void);
void fac_login(void);
void land_func(void);
void display_gen_info(void);
void display_mark_info(void);

class student {
public:
    string name;
    int id;
    int roll;
    string department;
    char blood_group[3];

    int phy,eec,spl,eng,eec_lab,spl_lab;
};


class fac_log_info{
public:
     char name[11];
     int pass;
};

class student s;
class fac_log_info fl;

int choice;
int land_choice;

void land_page(void){
     system("cls");
     system("color 0b");

     std::cout<<"\n\t-----STUDENT MANAGEMENT SYSTEM V-3.0-----\n\n";
     std::cout<<"\n1. Student Login\n";
     std::cout<<"\n2. Faculty Login\n";
     std::cout<<"\n3. Exit\n";
     std::cout<<"\n-----Enter Your Choice : ";
     std::cin>>land_choice;

     land_func();
}

void land_func(void){
   switch (land_choice){
    case 1:
        system("cls");
        stu_login();
        break;
    case 2:
        system("cls");
        fac_login();
        break;
    case 3:
        system("cls");
        exit(0);
        break;
    default:
        std::cout<<"\nInvalid Input\n";

   }
   std::cout<<"\nPress any key to continue ... ";
   getch();
   land_page();
}

void set_fac_inf(void){
    system("cls");
   FILE *logFile=fopen("log-info.bin","ab");

   std::cout<<"\n\t-----ADD FACULTY LOGIN INFO-----\n\n";
   std::cout<<"(under 10 letters,symbols,digits)\n";
   std::cout<<"Name     : ";
   fflush(stdin);
   std::cin>>fl.name;
   std::cout<<"Password : ";
   fflush(stdin);
   std::cin>>fl.pass;

   fwrite(&fl,sizeof(fl),1,logFile);
   fclose(logFile);

}



void stu_login(void){
       system("cls");
       FILE *myFile=fopen("student-record.bin","rb");
       int roll,id;
       char option;
       bool exist=false;
       std::cout<<"\n\t-----STUDENT LOGIN-----\n\n";
       std::cout<<"Enter Roll no. and ID\n";
       std::cout<<"Roll : ";
       std::cin>>roll;
       std::cout<<"ID   : ";
       std::cin>>id;

       while(fread(&s,sizeof(s),1,myFile)==true){
        if(s.roll==roll && s.id==id){
            exist=true;
            break;
        }
       }
       if(exist==false){
        std::cout<<"Invalid info..\n";
       }
       else{
                system("cls");
                std::cout<<"\n\t-----STUDENT INFO-----\n\n";
                display_gen_info();
                std::cout<<"\nView Marks ? (y/n) : ";
                std::cin>>option;
                option=toupper(option);
                 if(option=='Y')
                    display_mark_info();
                fclose(myFile);
       }
}

void fac_login(void){
    bool exist=false;
    bool inf_exist=false;
    char u_name[11];
    int u_pass;

    FILE *logFile=fopen("log-info.bin","rb+");

    while(fread(&fl,sizeof(fl),1,logFile)==true){
        exist=true;
    }
    if(exist==false){
        set_fac_inf();
    }
    fclose(logFile);

    std::cout<<"\n\t----- FACULTY LOGIN -----\n\n";
    std::cout<<"Name        : ";
    fflush(stdin);
    std::cin>>u_name;
    std::cout<<"Password    : ";
    fflush(stdin);
    std::cin>>u_pass;

    logFile=fopen("log-info.bin","rb+");

    while(fread(&fl,sizeof(fl),1,logFile)==true){
        if(strcmp(fl.name,u_name)==0 && fl.pass==u_pass){
            inf_exist=true;
            break;
        }
    }
    if(inf_exist==false){
        std::cout<<"\nInvalid Info\n";
    }
    else{
        menu();
    }
   fclose(logFile);
}

void menu(void){
   system("cls");
   system("color 0b");

   std::cout<<"\n\t-----STUDENT MANAGEMENT SYSTEM V-3.0-----\n\n";
   std::cout<<"1. Add Student Data \n";
   std::cout<<"2. View Student Data \n";
   std::cout<<"3. Add Marks \n";
   std::cout<<"4. Remove Student Data\n";
   std::cout<<"5. Remove All Data\n";
   std::cout<<"6. Update Student Data\n";
   std::cout<<"7. Search Data\n";
   std::cout<<"8. Go Back\n";
   std::cout<<"9. Exit\n";
   std::cout<<"\n-----Enter Your Choice : ";

   std::cin>>choice;

   functions();
}

void functions(){
   switch (choice){
    case 1:
       system("cls");
       add_data();
       break;
    case 2:
      system("cls");
      view_data();
      break;
    case 3:
      system("cls");
      add_marks();
      break;
    case 4:
      system("cls");
      remove_single_data();
      break;
    case 5:
      system("cls");
      remove_data();
      break;
    case 6:
      system("cls");
      update_data();
      break;
    case 7:
      system("cls");
      search_data();
      break;
    case 8:
        system("cls");
        land_page();
        break;
    case 9:
        system("cls");
        exit(0);

   default:
      std::cout<<"Invalid input!";
   }

   std::cout<<"\nPress any key to continue ... ";
   getch();
   menu();

}

int has_roll(int roll){
    FILE *temp;
    temp=fopen("student-record.bin","rb+");
       while(fread(&s,sizeof(s),1,temp)==true){
            if(s.roll==roll){

                return 1;
            }
        }
        fclose(temp);
        return 0;
}

void display_gen_info(){

        std::cout<<"Name        : "<<s.name<<std::endl;
        std::cout<<"Roll        : "<<s.roll<<std::endl;
        std::cout<<"ID          : "<<s.id<<std::endl;
        std::cout<<"Department  : "<<s.department<<std::endl;
        std::cout<<"Blood Group : "<<s.blood_group<<std::endl;
        std::cout<<"\n\t----------------\n\n";
}

void display_mark_info(){
                std::cout<<"\nName        : "<<s.name<<std::endl;
                std::cout<<"Roll        : "<<s.roll<<std::endl;
                std::cout<<"-----MARKS-----\n\n";
                std::cout<<"Phy         : "<<s.phy<<std::endl;
                std::cout<<"EEC         : "<<s.eec<<std::endl;
                std::cout<<"SPL         : "<<s.spl<<std::endl;
                std::cout<<"ENG         : "<<s.eng<<std::endl;
                std::cout<<"EEC LAB     : "<<s.eec_lab<<std::endl;
                std::cout<<"SPL LAB     : "<<s.spl_lab<<std::endl;
                std::cout<<"\n\t----------------\n\n";
}
void stu_info(FILE *myFile ,int roll,string name){
        char option;
        std::cout<<"Name        : ";
        fflush(stdin);
        getline(std::cin,name);
        std::cout<<"Roll        : ";
        fflush(stdin);
        std::cin>>roll;
        while(roll==0){
            std::cout<<"0 cannot be Roll number..Enter new Roll : ";
            std::cin>>roll;
        }

     while(1){

        if(has_roll(roll)==0){
            s.roll=roll;
            s.name=name;
            break;
        }
        else{
            std::cout<<"Roll already exists. Enter new Roll : ";
            std::cin>>roll;
        }
     }
        std::cout<<"ID          : ";
        fflush(stdin);
        std::cin>>s.id;
        std::cout<<"Department  : ";
        fflush(stdin);
        getline(std::cin,s.department);
        std::cout<<"Blood Group : ";
        fflush(stdin);
        std::cin>>s.blood_group;

        std::cout<<"\nAdd Marks ? (y/n) : ";
        std::cin>>option;
        option=toupper(option);
        if(option=='Y')
            subjects(myFile);
        else
            s.phy=0,s.eec=0,s.spl=0,s.eng=0,s.eec_lab=0,s.spl_lab=0;

        fwrite(&s,sizeof(s),1,myFile);

        fclose(myFile);
}

void add_data(void){
    string input;
    int roll;
    string name;
    FILE *myFile;

    myFile=fopen("student-record.bin","ab");

        std::cout<<"\n\t-----ADD STUDENT DATA-----\n\n";
        stu_info(myFile,roll,name);
        std::cout<<"\n-----DATA ADDED SUCCESSFULLY-----\n";

}

void view_data (void){
   FILE *myFile;
   myFile=fopen("student-record.bin","rb");

   bool exist=false;
   int choice;
   std::cout<<"\n\t-----VIEW ALL DATA-----\n\n";
   std::cout<<"1. View General Info\n";
   std::cout<<"2. View Marks \n";
   std::cout<<"\n---Enter your choice : ";
   std::cin>>choice;
   if(choice==1){
   system("cls");
   std::cout<<"\n\t----- VIEW GENERAL INFO -----\n\n";
   while(fread(&s,sizeof(s),1,myFile)==true){
    exist=true;
    display_gen_info();
     }
   }
   else if(choice==2){
    system("cls");
    std::cout<<"\n\t----- VIEW MARKS -----\n\n";
    while(fread(&s,sizeof(s),1,myFile)==true){
    exist=true;
    display_mark_info();
     }
   }
    if(exist==false){
    std::cout<<"\nNo data found...\n\n";
   }
}

void add_marks(void){
     FILE *myFile=fopen("student-record.bin","rb+");
     bool exist=false;
     int roll;

     std::cout<<"\n\t-----ADD STUDENT MARKS-----\n\n";
     std::cout<<"Enter student roll number : ";
     std::cin>>roll;

     while(fread(&s,sizeof(s),1,myFile)==true){
        if(s.roll==roll){
            exist=true;
            break;
        }
     }
     if(exist==false){
        std::cout<<"\nSorry student data not found..\n";
        return;
     }
     else {
        display_gen_info();
     }

     subjects(myFile);
     fclose(myFile);
     std::cout<<"\n---MARKS ADDED....\n";
}

void subjects(FILE *myFile){
    fseek(myFile,-(sizeof(s)),SEEK_CUR);
    std::cout<<"PHY      : ";
    fflush(stdin);
    std::cin>>s.phy;
    std::cout<<"EEC      : ";
    fflush(stdin);
    std::cin>>s.eec;
    std::cout<<"SPL      : ";
    fflush(stdin);
    std::cin>>s.spl;
    std::cout<<"ENG      : ";
    fflush(stdin);
    std::cin>>s.eng;
    std::cout<<"EEC LAB  : ";
    fflush(stdin);
    std::cin>>s.eec_lab;
    std::cout<<"SPL LAB  : ";
    fflush(stdin);
    std::cin>>s.spl_lab;
    fwrite(&s,sizeof(s),1,myFile);
    fclose(myFile);
}

void remove_single_data(void){
   FILE *myFile;
   FILE *temp;
   myFile=fopen("student-record.bin","rb");
   temp=fopen("temp.txt","wb");
   bool exist=false;
   int roll;
   std::cout<<"\n\t-----REMOVE SINGLE DATA-----\n\n";
   std::cout<<"\nEnter Roll number : ";
   std::cin>>roll;
   while(fread(&s,sizeof(s),1,myFile)==true){
    if(s.roll==roll){
        exist=true;
    }
    else{
        fwrite(&s,sizeof(s),1,temp);
    }
   }
   if(exist==false){
    std::cout<<"\nSorry data not found..\n";
    return;
   }

   fclose(myFile);
   fclose(temp);

   myFile=fopen("student-record.bin","wb");
   temp=fopen("temp.txt","rb");

   while(fread(&s,sizeof(s),1,temp)==true){
    fwrite(&s,sizeof(s),1,myFile);
   }
   fclose(myFile);
   fclose(temp);
   std::cout<<"\nData successfully deleted..\n";
}

void remove_data(void){
   std::fstream myFile;
   myFile.open("student-record.bin",std::ios::out | std::ios::trunc);
   myFile.close();

   std::cout<<"\n\t-----REMOVE ALL DATA-----\n\n";
   std::cout<<"\nData cleared successfully ...\n\n";

}

void update_data(void){
    FILE *myFile;
    myFile=fopen("student-record.bin","rb+");
    int id,roll;
    string name;
    bool found=false;
    std::cout<<"\n\t-----UPDATE STUDENT DATA-----\n\n";
    std::cout<<"Enter student roll : ";
    std::cin>>id;

    while(fread(&s,sizeof(s),1,myFile)==true){
        if(s.roll==id){
            found=true;
            break;
        }
    }
    if(found==false){
        std::cout<<"Sorry data not found...\n\n";
        return;
    }
    fseek(myFile,-(sizeof(s)),SEEK_CUR);
        display_gen_info();
        s.roll=0;

    fwrite(&s,sizeof(s),1,myFile);
    fclose(myFile);

      myFile=fopen("student-record.bin","rb+");
      while(fread(&s,sizeof(s),1,myFile)==true){
        if(s.roll==0){
            found=true;
            break;
        }
    }
    fseek(myFile,-(sizeof(s)),SEEK_CUR);
    std::cout<<"\n\t-----ENTER UPDATED DATA-----\n\n";
     stu_info(myFile,roll,name);
    std::cout<<"\n\t-----DATA SUCCESSFULLY UPDATED-----\n";

}

void search_data(void){
      FILE *myFile;
      myFile=fopen("student-record.bin","rb+");

      int choice;
      char option;
      system("cls");
      std::cout<<"\n\t-----SEARCH DATA-----\n\n";
      std::cout<<"\n1. Search with Roll Number \n";
      std::cout<<"\n2. Search with blood group \n";
      std::cout<<"\n-----Select option : ";
      std::cin>>choice;

      if(choice==1){
            system("cls");
        int roll_num;
        bool found=false;
        std::cout<<"\nEnter Roll Number : ";
        std::cin>>roll_num;
        while(fread(&s,sizeof(s),1,myFile)==true){
            if(s.roll==roll_num){
                found=true;
                break;
            }
        }
        if(found==false){
            std::cout<<"\nSorry Data not found....Press any key to go back"<<std::endl;
            getch();
            search_data();
        }
        fseek(myFile,-(sizeof(s)),SEEK_CUR);
                display_gen_info();
                std::cout<<std::endl;
                std::cout<<"View Marks? (y/n) : ";
                std::cin>>option;
                option=toupper(option);
                if(option=='Y')
                    display_mark_info();

                fclose(myFile);

     }
     else if(choice==2){
         system("cls");
         char blood_grp[3];
         bool found=false;
         std::cout<<"\nEnter Blood Group : ";
         std::cin>>blood_grp;
         while(fread(&s,sizeof(s),1,myFile)==true){

            if(strcmp(s.blood_group,blood_grp)==0){
                display_gen_info();
                found=true;
            }
         }
        if(found==false){
            std::cout<<"\nSorry Data not found....Press any key to go back"<<std::endl;
            getch();
            search_data();
        }
     }
     else{
        std::cout<<"\nInvalid Input. Press any key to go back..";
        getch();
        menu();
     }

}

int main (void){
  land_page();
}
