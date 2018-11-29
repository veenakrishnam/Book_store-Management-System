#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<fstream>
#include<iostream>
#include<stdlib.h>
using namespace std;
class record
{
    public: char isbn[20],name[20],author[20],publisher[20],cost[20];
}
rec[20],found[20];
int i,no,num,total,tempnum=0,count;
char emp_no[5],rt_name[20];
void sortrecord()
{
    int i,j;
    record temp;
    for(i=0;i<no-1;i++)
    for(j=0;j<no-i-1;j++)
    if(strcmp(rec[j].name,rec[j+1].name)>0)
    {
        temp=rec[j];
        rec[j]=rec[j+1];
        rec[j+1]=temp;
    }
}
void indexfile()
{
    fstream index,index2;
    int i;
    index.open("secindex.txt",ios::in |ios::app);
    index2.open("record.txt",ios::in |ios::app);
    for(i=tempnum;i<total;i++)
    {
        index<<rec[i].name<<"|"<<rec[i].isbn<<"|"<<i<<"\n";
        index2<<i<<"|"<<rec[i].name<<"|"<<rec[i].isbn<<"|"<<
        rec[i].author<<"|"<<rec[i].publisher<<"|"<<rec[i].cost<<"\n";
    }
    index.close();
    index2.close();
}
void retrieve_record(char*index)
{
    fstream file;
    char author[20],publisher[20],isbn[20],name[20],cost[20],ind[5];
    file.open("record.txt",ios::in);
    for(i=0;i<total;i++)
    {
        file.getline(ind,20,'|');
        file.getline(name,20,'|');
        file.getline(isbn,20,'|');
        file.getline(author,20,'|');
        file.getline(publisher,20,'|');
        file.getline(cost,20,'\n');
        if(strcmp(index,ind)==0)
        {
            cout<<"ISBN\t\tNAME\t\tAUTHOR\t\tPUBLISHER\tCOST\n";
            cout<<isbn<<"\t\t"<<name<<"\t\t"<<author<<"\t\t"<<publisher<<"\t\t"<<cost<<"\n";
        }
    }
    file.close();
}
void retrieve_details()
{
    fstream file;
    char author[20],publisher[20],isbn[20],name[20],cost[20],ind[5];
    char chssn[20],index[20][20];
    file.open("secindex.txt",ios::in);
    int k=0;
    for(i=0;i<total;i++)
    {
        file.getline(name,20,'|');
        file.getline(isbn,20,'|');
        file.getline(ind,4,'\n');
        if(strcmp(name,rt_name)==0)
        {
            strcpy(found[k].name,name);
            strcpy(found[k].isbn,isbn);
            strcpy(index[k],ind);
        }
        else
        {
            strcpy(found[k].isbn,"null");
        }
        k++;
    }
    file.close();
    if(k==1)
    {
        retrieve_record(index[0]);
        return;
    }
    else
    {
        cout<<"choose the books isbn\n";
        for(int i=0;i<k;i++)
        {
            if(strcmp(found[i].isbn,"null"))
            {
                cout<<"ISBN:"<<found[i].isbn<<"\tNAME:"<<found[i].name<<endl;
            }
        }
    }
    cin>>chssn;
    for(i=0;i<k;i++)
    {
        if(strcmp(chssn,found[i].isbn)==0)
        {
            retrieve_record(index[i]);
            return;
        }
    }
    cout<<"invalid entry\n";
    return;
}
void delete_record(char*indx)
{
    char author[20],publisher[20],isbn[20],name[20],cost[20],ind[5];
    fstream file1,file2;
    char index[20][20];
    file2.open("record.txt",ios::in);
    for(i=0;i<total;i++)
    {
        file2.getline(ind,4,'|');
        file2.getline(name,20,'|');
        file2.getline(isbn,20,'|');
        file2.getline(author,20,'|');
        file2.getline(publisher,20,'|');
        file2.getline(cost,20,'\n');
        strcpy(index[i],ind);
        strcpy(rec[i].isbn,isbn);
        strcpy(rec[i].name,name);
        strcpy(rec[i].author,author);
        strcpy(rec[i].publisher,publisher);
        strcpy(rec[i].cost,cost);
    }
    int flag=-1;
    for(i=0;i<total;i++)
    {
        if(strcmp(index[i],indx)==0)
        flag=i;
    }
    if(flag==-1)
    {
        cout<<"error\n";
        return;
    }
    if(flag==(total-1))
    {
        total = total - 1;
        tempnum--;
        cout<<"record deleted\n";
        cout<<total;
        return;
    }
    for(i=flag;i<total;i++)
    {
        rec[i]=rec[i+1];
    }
    total = total - 1;
    tempnum--;
    cout<<"record deleted\n";
    file2.close();
    cout<<total;
    file1.open("secindex.txt",ios::out);
    file2.open("record.txt",ios::out);
    for(i=0;i<total;i++)
    {
        file1<<rec[i].name<<"|"<<rec[i].isbn<<"|"<<i<<"\n";
        file2<<i<<"|"<<rec[i].name<<"|"<<rec[i].isbn<<"|"<<
        rec[i].author<<"|"<<rec[i].publisher<<"|"<<rec[i].cost<<"\n";
    }
    file1.close();
    file2.close();
}
void delete_index(char*nam)
{
    fstream file;
    char author[20],publisher[20],isbn[20],name[20],cost[20],ind[5];
    char chssn[20],index[20][20];
    int i,k=0;
    file.open("secindex.txt",ios::in);
    for(i=0;i<total;i++)
    {
        file.getline(name,20,'|');
        file.getline(isbn,20,'|');
        file.getline(ind,4,'\n');
        if(strcmp(nam,name)==0)
        {
            strcpy(found[k].name,name);
            strcpy(found[k].isbn,isbn);
            strcpy(index[k],ind);
        }
        else
        {
            strcpy(found[k].isbn,"null");
        }
        k++;
    }
    file.close();
    if(k==1)
    {
        delete_record(index[0]);
        return;
    }
    else
    {
        cout<<"choose the books isbn\n";
        for(i=0;i<k;i++)
        {
            if(strcmp(found[i].isbn,"null"))
            {
                cout<<"ISBN:"<<found[i].isbn<<"\t"<<"NAME:"<<found[i].name<<endl;
            }
        }
    }
    cin>>chssn;
    for(i=0;i<k;i++)
    {
        if(strcmp(chssn,found[i].isbn)==0)
        {
            delete_record(index[i]);
            return;
        }
    }
    cout<<"invalid entry\n";
    return;
}
void update_record(char*index)
{
    fstream file,file1,file2;
    char author[20],publisher[20],isbn[20],name[20],cost[20],ind[5];
    file.open("record.txt",ios::in);
    for(i=0;i<total;i++)
    {
        file.getline(ind,20,'|');
        file.getline(name,20,'|');
        file.getline(isbn,20,'|');
        file.getline(author,20,'|');
        file.getline(publisher,20,'|');
        file.getline(cost,20,'\n');
        if(strcmp(index,ind)==0)
        {
            cout<<"Enter the New Name:";
            cin>>rec[i].name;
            cout<<"New ISBN:";
            cin>>rec[i].isbn;
            cout<<"New Author:";
            cin>>rec[i].author;
            cout<<"New Publisher:";
            cin>>rec[i].publisher;
            cout<<"New Cost:";
            cin>>rec[i].cost;

            sortrecord();

            file1.open("secindex.txt",ios::out);
            file2.open("record.txt",ios::out);
            for(i=0;i<total;i++)
            {
                file1<<rec[i].name<<"|"<<rec[i].isbn<<"|"<<i<<"\n";
                file2<<i<<"|"<<rec[i].name<<"|"<<rec[i].isbn<<"|"<<
                rec[i].author<<"|"<<rec[i].publisher<<"|"<<rec[i].cost<<"\n";
            }
            file1.close();
            file2.close();
        }
    }
    file.close();
}
void update_index(char*nam)
{
    fstream file;
    char author[20],publisher[20],isbn[20],name[20],cost[20],ind[5];
    char chssn[20],index[20][20];
    int i,k=0;
    file.open("secindex.txt",ios::in);
    for(i=0;i<total;i++)
    {
        file.getline(name,20,'|');
        file.getline(isbn,20,'|');
        file.getline(ind,4,'\n');
        if(strcmp(nam,name)==0)
        {
            strcpy(found[k].name,name);
            strcpy(found[k].isbn,isbn);
            strcpy(index[k],ind);
        }
        else
        {
            strcpy(found[k].isbn,"null");
        }
        k++;
    }
    file.close();
    if(k==1)
    {
        update_record(index[0]);
        return;
    }
    else
    {
        cout<<"choose the books isbn\n";
        for(i=0;i<k;i++)
        {
            if(strcmp(found[i].isbn,"null"))
            {
                cout<<"ISBN:"<<found[i].isbn<<"\t"<<"NAME:"<<found[i].name<<endl;
            }
        }
    }
    cin>>chssn;
    for(i=0;i<k;i++)
    {
        if(strcmp(chssn,found[i].isbn)==0)
        {
            update_record(index[i]);
            return;
        }
    }
    cout<<"invalid entry\n";
    return;
}
int main()
{
    fstream file1;
    char rt_ssn[20],book_name[20],book_isbn[20];
    char new_isbn[20];
    char author[20],publisher[20],name[20],cost[20],ind[5];
    int i,j,flag,flag1,flag2,flagsame,choice;
    cout<<"\t\t-----------------------------------------\n";
    cout<<"\t\tWelcome to Book Store Management System\n";
    cout<<"\t\t-----------------------------------------\n\t\tThis project is done by Veena and Bhavana\n";
    for(;;)
    {
        cout<<"\nChoose the option\n1:Add\n2:Search\n3:Delete\n4:Display\n5:Update\n6:Exit\n";
        cin>>choice;
        switch(choice)
        {
            case 1:cout<<"Enter the no of books\n";
            cin>>no;
            flagsame = 0;
            count = 0;
            total = total + no;
            for(i=tempnum;i<total;i++)
            {
                cout<<"Enter the Name:";
                cin>>rec[i].name;
                cout<<"ISBN:";
                cin>>rec[i].isbn;
                flagsame = 0;
                for(j=0;j<i;j++)
                {
                    if(strcmp(rec[i].isbn,rec[j].isbn)==0)
                    {
                        cout<<"\n Error!! Same ISBN found\n";
                        flagsame = 1;
                    }
                }
                if(flagsame)
                {
                    total = total - no;
                    total = total + count;
                    break;
                }
                cout<<"Author:";
                cin>>rec[i].author;
                cout<<"Publisher:";
                cin>>rec[i].publisher;
                cout<<"Cost:";
                cin>>rec[i].cost;
                count = count + 1;
            }
            sortrecord();
            indexfile();
            if(flagsame)
            {
                tempnum = tempnum - no;
                tempnum = tempnum + count;
            }
            else
            {
                tempnum = tempnum + no;
            }
            break;
            case 2:cout<<"Enter the name of the book to be searched\n";
            cin>>book_name;
            file1.open("secindex.txt",ios::in);
            if(!file1)
            {
                cout<<"file creation error\n";
                exit(0);
            }
            flag1=0;
            for(i=0;i<total;i++)
            {
                file1.getline(rt_name,20,'|');
                file1.getline(book_isbn,20,'|');
                file1.getline(emp_no,4,'\n');
                if(strcmp(book_name,rt_name)==0)
                {
                    retrieve_details();
                    flag1=1;
                }
            }
            if(!flag1)
                cout<<"record search failed\n";
            file1.close();
            break;
            case 3:cout<<"Enter the name of the book to be deleted\n";
            cin>>book_name;
            file1.open("secindex.txt",ios::in);
            if(!file1)
            {
                cout<<"file creation error\n";
                exit(0);
            }
            flag=0;
            for(i=0;i<total;i++)
            {
                file1.getline(rt_name,20,'|');
                file1.getline(book_isbn,20,'|');
                file1.getline(ind,4,'\n');
                if(strcmp(book_name,rt_name)==0)
                {
                    delete_index(rt_name);
                    flag=1;
                    break;
                }
            }
            if(!flag)
                cout<<"deletion failed\n";
            file1.close();
            break;
            case 4:cout<<"ISBN\t\tNAME\t\tAUTHOR\t\tPUBLISHER\tCOST\n";
            for(i=0;i<total;i++)
            {
                cout<<rec[i].isbn<<"\t\t"<<rec[i].name<<"\t\t"<<rec[i].author<<"\t\t"<<rec[i].publisher<<"\t\t"<<rec[i].cost<<"\n";
            }
            break;
            case 5:
            cout<<"Enter the name of the book to be updated\n";
            cin>>book_name;
            file1.open("secindex.txt",ios::in);
            if(!file1)
            {
                cout<<"file creation error\n";
                exit(0);
            }
            flag2=0;
            for(i=0;i<total;i++)
            {
                file1.getline(rt_name,20,'|');
                file1.getline(book_isbn,20,'|');
                file1.getline(ind,4,'\n');
                if(strcmp(book_name,rt_name)==0)
                {
                    update_index(rt_name);
                    flag2=1;
                    break;
                }
            }
            if(!flag2)
                cout<<"updation failed\n";
            file1.close();
            break;
            case 6:
            exit(0);
            break;
            default:cout<<"invalid choice\n";
            exit(0);
            break;
        }
    }
}

