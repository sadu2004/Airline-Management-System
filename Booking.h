#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include"definitions.h"
#include"graphADT.h"

char* getfield(char* line, int num)
{
    char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ","))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

void printseats()
{
printf("\n                          _____");
printf("\n                         /  |  \\");
printf("\n                        /___|___\\");
printf("\n                      /           \\");
printf("\n                    /               \\");
printf("\n                   /                 \\");
printf("\n                  /                   \\");
printf("\n                 |   A B C     D E F   |");
printf("\n             <<  |  | | | | 1 | | | |  |  >>");
printf("\n                 |  | | | | 2 | | | |  |                        FIRST CLASS");
printf("\n                 |  | | | | 3 | | | |  |");
printf("\n                 |                     |");
printf("\n                /|  | | | | 4 | | | |  |\\");
printf("\n              /  |  | | | | 5 | | | |  |  \\                    BUSINESS CLASS");
printf("\n            /    |  | | | | 6 | | | |  |    \\");
printf("\n          /  <<  |                     |  >>  \\");
printf("\n        /        |  | | | | 7 | | | |  |        \\");
printf("\n      /          |  | | | | 8 | | | |  |          \\");
printf("\n    /            |  | | | | 9 | | | |  |            \\");
printf("\n  /           /  |  | | | |10 | | | |  |  \\          \\        ECONOMY CLASS");
printf("\n/          /     |  | | | |11 | | | |  |     \\         \\");
printf("\n|       /    <<  |  | | | |12 | | | |  |  >>    \\       |");
printf("\n|____/           |  | | | |13 | | | |  |           \\____|");
printf("\n                 |  | | | |14 | | | |  |");
printf("\n                 |  | | | |15 | | | |  |\n");
getchar();
getchar();


}

// const char* getfield(char* line, int num)
// {
//     const char* tok;
//     for (tok = strtok(line, ";");
//             tok && *tok;
//             tok = strtok(NULL, ";\n"))
//     {
//         if (!--num)
//             return tok;
//     }
//     return NULL;
// }


float path_cost(int fir,int busi,int eco, struct path *trip, float per)
{   
    if(trip->num == 0){
        return 0;
    }
    float total=0;
    for (int i=0; i<trip->num; i++)
    {
        printf("%d %d %d\n",fir,busi,eco);
        printf("%d \n",trip->route[i].details.economy);
        total = total+fir*(trip->route[i].details.first) + busi*(trip->route[i].details.business) + eco*(trip->route[i].details.economy);
        getchar();
    }

    trip->cost=total*per/100;
    return trip->cost;
}

void display(struct path pat)
{
    if( pat.num < 1){
        printf("\nNO FLIGHTS AVAILABLE\n\n");
        return;
    }
    else

    {
        printf("\nFlIGHT ROUTES\n");

            for( int i=0; i<pat.num; i++)
            {
                printf("%s", place[pat.route[i].details.source]);
                printf("->");
                printf("%s", place[pat.route[i].details.dest]);
                printf("\n\tFlight code: %s\n\tDeparture time: %d:%d\n\tArrival time: %d:%d\n", pat.route[i].details.fcode, pat.route[i].details.deptime.hh, pat.route[i].details.deptime.mm, pat.route[i].details.arrtime.hh, pat.route[i].details.arrtime.mm);
                printf("\tDate: %d/%d/%d\n", pat.route[i].flight_date.day, pat.route[i].flight_date.month, pat.route[i].flight_date.year);
                printf("\tFirst : %d Business : %d Economy : %d",pat.route[i].details.first,pat.route[i].details.business,pat.route[i].details.economy);
                printf("\n");
            }
        printf("Total cost of path: %.2f \n", pat.cost);
    }

}

int is_direct(struct path *trip)
{
    return trip->num==1;
}

int single(struct path *trip)
{
    return trip->num==2;
}

int multi(struct path *trip)
{
    return trip->num>=3;
}
int no_filter(struct path *trip)
{
    return 1;
}
void filter(struct path paths[], int (*f)(struct path*),  int* path_no)
{
    int count=0;
    for (int i=0; i<*path_no; i++)
    {
        if ((*f)(&paths[i]))
        {
            paths[count]=paths[i];
            count++;
        }


    }
    *path_no=count;

}

void ticket_view_pnr(long long int pnr)
{
    printf("TICKET DETAILS\n");
    FILE *fptr= fopen("bookings.csv", "r");
    char buffer[1024];
    char *value;
    int row = 0;
    int column = 0;
 
    while (!feof(fptr)){
        fgets(buffer,1024,fptr);
        if(strlen(buffer)<2){
            break;
        }
        column = 0;
        char* tmp = strdup(buffer);
        long long int val = (long long int) convertstl(getfield(tmp,2));
        if(val != pnr){
            free(tmp);
            row++;
            continue;
        }
        free(tmp);
        value = strtok(buffer, ",");
        while(value != NULL){
            if (column == 0) {
                    printf("Username: %s\n",value);
                }
            else if (column == 1) {
                    printf("PNR: %s\n",value);
            }
            else if (column == 2) {
                    printf("Source: %s\n",place[(int) *value-48]);
            }
            else if (column == 3) {
                    printf("Destination: %s\n",place[(int)*value-48]);
            }
            else if (column == 4) {
                    printf("FCode: %s\n",value);
            }
            else if (column == 5) {
                printf("Date: %s\n",value);
            }
            else if (column == 6) {
                printf("Class: %s\n",value);
            }
            value = strtok(NULL, ",");
            column++;
        }
        row++;
    }
    fclose(fptr);
}


int lcost(struct path *trip1, struct path *trip2)
{
    return trip1->cost<trip2->cost;
}

int hcost(struct path *trip1, struct path *trip2)
{
    return trip1->cost>trip2->cost;
}

int stops(struct path *trip1, struct path *trip2)
{
    return trip1->num<trip2->num;
}

void sort(struct path paths[], int path_no, int (*f)(struct path*, struct path*))
{   int min_index;
    for (int i=0; i<path_no-1; i++)
    {
        min_index=i;
        for(int j=i+1; j<path_no; j++)
        {
            if ((*f)(&paths[j], &paths[min_index]))
                min_index=j;
        }

        struct path temp=paths[min_index];
        paths[min_index]=paths[i];
        paths[i]=temp;

    }
}



void book(char* username)
{
    //f=fopen("a.bin", "rb+");
    int n; //no. of passengers
    FILE *f;
    enum days d1;
    enum places src;
    enum places des;
    float per;
    time_t timer;
    struct tm curr_time;
    int diff;
    struct date dep_date;
    while(1)
    {

        time(&timer);
        curr_time=*localtime(&timer);  //Current time
        printf("\nEnter date of departure as day/month/year: ");
        scanf(" %d/%d/%d", &dep_date.day, &dep_date.month, &dep_date.year);
        diff=convert(dep_date.month, dep_date.day,  dep_date.year)-convert(curr_time.tm_mon+1, curr_time.tm_mday, curr_time.tm_year+1900);
        if (diff<0)
            printf("\n\nEntered date is past current date.\nPlease re-enter.\n\n");
        else if (diff>30)
            printf("\n\nBooking is available only for uptil 30 days before the flight journey.\nPlease re-enter.\n\n");
        else
            break;
    }

    // struct tm curr=*localtime(&timer);
    // int d = curr.tm_mday+diff;
    // int m = curr.tm_mon+1;
    // int y = curr.tm_year+1900;
    // int weekday  = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;
    // weekday += 1;
    d1 = (enum days) convert( dep_date.month, dep_date.day, dep_date.year)%7+1;
    if (diff>20)
        per=90;
    else if(diff>10)
        per=95;
    else
        per=100;
    //Variation in price based on time of booking



    printf("\n\nSOURCE\n\nOptions:\n0.CHENNAI\n1.BANGALORE\n2.PUNE\n3.DELHI\n4.KOCHI\n5.MUMBAI\n6.HYDERABAD\n7.SINGAPORE\n8.LONDON\n9.DUBAI\n");
    printf("Enter option: ");
    scanf("%d",&src);
    printf("\n\nDESTINATION\nOptions:\n0.CHENNAI\n1.BANGALORE\n2.PUNE\n3.DELHI\n4.KOCHI\n5.MUMBAI\n6.HYDERABAD\n7.SINGAPORE\n8.LONDON\n9.DUBAI\n");
    printf("Enter option: ");
    scanf("%d",&des);
    getchar();

    system("cls");

    int choice2;

    printf("Enter no. of passengers: ");
    scanf("%d", &n);
    ticket t[n];
    int pscount[3]={0,0,0};
    for (int i=0; i<n; i++)
    {   
        //memcpy((t+i).u,*(all_users+i),sizeof(struct user_details));
        strcpy(t[i].username,username);
        printf("Passenger : %d\n", i+1);
        while(1)
        {
            printf("\n\nChoose Class\n1. First Class\n2. Business Class\n3. Economy Class\nEnter: ");
            scanf("%d",&choice2);
            if (choice2!=1&&choice2!=2&&choice2!=3)
                printf("Invalid Choice.\nPlease Re-enter.\n");
            else{
                t[i].tclass = choice2;
                pscount[choice2-1]+=1;
                break;
            }
        }



    }

    // struct path paths[100]; //Stores all possible paths from source to destination
    struct path trip1;
    struct path trip2;       //Stores a particular path       //Stores a particular path          //No. of paths from source->destination
    trip1.num=0;  
    trip2.num=0;             //No. of flights taken in trip          //Total no. of paths from source->destination          //No. of flights taken in trip          //Total no. of paths from source->destination
    // int visited[10];        //To keep track of visited places to avoid cycles in the graph
    // for (int i=0; i<10; i++)
    // {
    //     visited[i]=0;       //Marking all places as unvisited
    // }

    struct flight flarr[300];
    int num=0; //no. of available flights
    f=fopen("schedule.csv", "r");
    char buffer[1024];
    char* value;
    int diffarr[250];
    struct flight temp;
    int diff3;
        int row = 0;
        int column = 0;
    int p_arr1[3];
    for(int i=0;i<3;i++)
    {
        p_arr1[i]=pscount[i];
    }
        while (!feof(f)){
            fgets(buffer,1024,f);
            column = 0;
            // char* tmp = strdup(buffer);
            // int val = (int) *getfield(tmp,7+days);
            // if(!val){
            //     free(temp);
            //     row++;
            //     continue;
            // }
            // free(tmp);
            value = strtok(buffer, ",");
            while(value != NULL){
                if (column == 0) {
                    strcpy(temp.details.fcode,value);
                }
                else if (column == 1) {
                    temp.details.source = (enum places) convertstf(value);
                }
                else if (column == 2) {
                    temp.details.dest = (enum places) convertstf(value);
                }
                else if (column == 3) {
                    temp.details.deptime.hh = (value[1]==':') ? ((int)value[0]-48) : ((int)value[0]-48)*10+((int)value[1]-48);
                    temp.details.deptime.mm = (value[1]==':') ? ((strlen(value)==4) ? ((int)value[2]-48)*10+((int)value[3]-48) : ((int)value[2]-48)) : ((strlen(value)==5) ? ((int)value[3]-48)*10+((int)value[4]-48) : ((int)value[3]-48));
                }
                else if (column == 4) {
                    temp.details.arrtime.hh = (value[1]==':') ? ((int)value[0]-48) : ((int)value[0]-48)*10+((int)value[1]-48);
                    temp.details.arrtime.mm = (value[1]==':') ? ((strlen(value)==4) ? ((int)value[2]-48)*10+((int)value[3]-48) : ((int)value[2]-48)) : ((strlen(value)==5) ? ((int)value[3]-48)*10+((int)value[4]-48) : ((int)value[3]-48));
                }
                else if (column == 5) {
                    temp.details.first = convertstf(value);
                }
                else if (column == 6) {
                    temp.details.business = convertstf(value);
                }
                else if (column == 7) {
                    temp.details.economy = convertstf(value);
                }
                else if (column == 8) {
                    temp.details.day = (enum days) ((int)*value-48);
                }
                else if (column == 9) {
                    temp.flight_date.day = (value[1]=='/') ? ((int)value[0]-48) : ((int)value[0]-48)*10+((int)value[1]-48);
                    temp.flight_date.month = (value[1]=='/') ? ((value[3]=='/') ? ((int)value[2]-48) : ((int)value[2]-48)*10+((int)value[3]-48)) : ((value[4]=='/') ? ((int)value[3]-48) : ((int)value[3]-48)*10+((int)value[4]-48));
                    temp.flight_date.year = (value[1]=='/') ? ((value[3]=='/') ? ((int)value[4]-48)*1000+((int)value[5]-48)*100+((int)value[6]-48)*10+((int)value[7]-48) :((int)value[5]-48)*1000+((int)value[6]-48)*100+((int)value[7]-48)*10+((int)value[8]-48))  : ((value[4]=='/') ?  ((int)value[5]-48)*1000+((int)value[6]-48)*100+((int)value[7]-48)*10+((int)value[8]-48) : ((int)value[6]-48)*1000+((int)value[7]-48)*100+((int)value[8]-48)*10+((int)value[9]-48) );
                    diff3 = convert(temp.flight_date.month, temp.flight_date.day, temp.flight_date.year)-convert(dep_date.month, dep_date.day,  dep_date.year);
                }
                value = strtok(NULL, ",");
                column++;
            }
            if(diff3 < 0){
                continue;
            }
            else if(diff3 > 6){
                continue;
            }
            diffarr[row] = diff3;
            flarr[row] = temp;
            row++;
        }
        fclose(f);
    num = --row;
    int diff2;
    linkedList* adj_list[10]; //adjacency list
    createAdjList(adj_list, 10);
    for (int i=0; i<num; i++)
    {   
        //diff2 = convert(flights[i].flight_date.month, flights[i].flight_date.day, flights[i].flight_date.year)-convert(dep_date.month, dep_date.day,  dep_date.year);
        if(diffarr[i] < 0){
            continue;
        }
        else if(diffarr[i] > 3){
            break;
        }
        ins_end(flarr[i], adj_list[(int) flarr[i].details.source]);
    }
    // printf("%d %d %d\n",p_arr1[0],p_arr1[1],p_arr1[2]);
    trip1 = dja(src,des,d1,adj_list);
    // printf("%d %d %d\n",p_arr1[0],p_arr1[1],p_arr1[2]);
    trip1.cost = path_cost(p_arr1[0],p_arr1[1],p_arr1[2], &trip1, per);
    trip2 = dja_cost(src,des,d1,adj_list,p_arr1);
    trip2.cost = path_cost(p_arr1[0],p_arr1[1],p_arr1[2], &trip2, per);
    printf("Fastest Flight:\n");
    display(trip1);
    printf("Cheapest Flight:\n");
    display(trip2);
    getchar();
    getchar();


    if(trip1.num!=0 || trip2.num!=0)

    {
        printf("\n\n\n\n");
        // scanf("%d", &choice2);
        // int (*fil)(struct path*);
        // int (*s)(struct path*, struct path*);
        // switch(choice1)
        // {
        //     case 1: fil=&is_direct;break;
        //     case 2: fil=&single;break;
        //     case 3: fil=&multi;break;
        //     case 4: fil=&no_filter;break;
        // }

        // switch(choice2)
        // {
        //     case 1: s=&lcost;break;
        //     case 2: s=&hcost;break;
        //     case 3: s=&stops;break;

        // }


        // filter(paths, fil,  &path_no);
        // sort(paths, path_no, s);

        // display(paths[0]);

        char choice[10];
        struct path finp;

        // printf("Enter username: ");
        // scanf("%s",user);

        printf("\nEnter choice of to be booked or x to exit: ");
        scanf("%s",choice);
        if(strcmp("x", choice)==0){
            printf("Booking Cancelled\n");
            return;
        }
        int d = (int) *choice-48;
        if(d == 1){
            finp = trip1;
        }
        else{
            finp = trip2;
        }
        FILE *file=fopen("bookings.csv","a");
        // for(int i=0;i<2000;i++){
        //     if(strcmp(flights[i].details.fcode,choice)==0){
        //         final = flights[i];
        //         break;
        //     }
        // }
        
            for(int i=0;i<n;i++){
                strcpy(t[i].fcode,trip1.route[0].details.fcode);
                t[i].flight_date = trip1.route[0].flight_date;
                t[i].source = trip1.route[0].details.source;
                t[i].dest = trip1.route[0].details.dest;
                srand( (unsigned int) time(NULL));  
                float f1 = 10000000000000.0;  
                float f2 = ((float) rand()/ RAND_MAX) * f1;
                t[i].pnr = ((long long int) f2)+i;
                fprintf(file,"%s,%lld,%u,%u,%s,%d/%d/%d,%d\n",t[i].username,t[i].pnr,t[i].source,t[i].dest,t[i].fcode,t[i].flight_date.day,t[i].flight_date.month,t[i].flight_date.year,t[i].tclass);
            }
        fclose(file);
        for(int i=0;i<n;i++){
            ticket_view_pnr(t[i].pnr);
        }
        getchar();
        getchar();
        //printf("\n\nSEATING ARRANGEMENT\n\n");
        //printseats();

    }
}