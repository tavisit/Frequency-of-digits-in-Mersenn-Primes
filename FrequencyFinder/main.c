#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "string.h"
#include <unistd.h> // note that you need this for getopt to work
#define MAX_BUFFER_SIZE 4096
#define INT_MIN -2147483648

void ParseFile(FILE * fileIn, FILE * fileOut,int __power)
{
    fprintf(fileOut,"%d\n",__power);                                    //  Dispaying the power of the current number for indexing
    int * frequencyDigits= (int*)malloc(sizeof(int)*10);                //  Allocate memory for the frequency of digits
    memset(frequencyDigits,0,10);                                       //  Set the initial frequency to 0

    char lineDigit;                                                     //  Declaring the character representing each digit
    while((lineDigit=getc(fileIn))!=EOF)                                //  Read each digit of the number from current file
    {
        if(( lineDigit >= '0' && lineDigit <= '9' ))                    //  check if the character is a digit
        {
            frequencyDigits[lineDigit-'0']++;                           //  if it is, increase the frequency of that digit
        }
    }

    for(int i=0;i<10;i++)
        fprintf(fileOut,"         %d : %d\n",i,frequencyDigits[i]);     //  print each frequency along with an indentation to index easier

    free(frequencyDigits);                                              //  free the memory allocated for frequency
}
int main()
{
    FILE *fpIn  = fopen("List.txt","r");                //  input stream containing all the numbers with a specific power
    FILE *fpOut = fopen("OutputFile.txt","w");          //  output stream
    char * lineFile = (char*)malloc(sizeof(char)*500);

    while ( fgets ( lineFile, 500, fpIn ) != NULL )     //  read each power until the end of file
    {
        int __power;
        printf("%s\n",lineFile);                        //  print to the console to verify the output directly
        __power = atoi(lineFile);                       //  print into the folder the power to be able to format the Excel file
        char * actualFilePath = (char*)malloc(sizeof(char)*150);

                                                        //  the whole procedure bellow builds the path of the following file
        strcpy(actualFilePath,"Resources/M");
        strcpy(actualFilePath+strlen(actualFilePath),lineFile);
        strcpy(actualFilePath+strlen(actualFilePath)-1,".txt");
                                                        //  end of procedure

        FILE * fileIn = fopen(actualFilePath,"r");
        ParseFile(fileIn,fpOut,__power);                //  Call the function listed above to parse the file
        fclose(fileIn);
    }

    fclose(fpIn);
    fclose(fpOut);

    return 0;
}
