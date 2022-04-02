//                                ____________________________________
//                               |            2022 PROJECT            |
//                               |      LINEAR ALGEBRA OPERATIONS     |                                        ______________
//                               |  DEVELOPER:   NIKOLAOS TOULKERIDHS |                                       |   Ntoylker   |
//                               |____________________________________|                                       |______________|
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <dirent.h> // Χρησιμοποιείται στη συνάρτηση "void txt_files_from_folder_printer()"


// Συναρτήσεις για επαφή των πινάκων με τα αρχεία
void pass_array_to_file(FILE *file, double **array, int rows, int cols) // ΠΕΡΝΆΕΙ ΈΝΑΝ ΠΊΝΑΚΑ ΣΕ ΈΝΑ ΑΡΧΕΊΟ 
{                                                   // ΧΡΗΣΙΜΟΠΟΙΕΊΤΑΙ ΣΧΕΔΌΝ ΑΠΌ ΌΛΕΣ ΤΙΣ ΣΥΝΑΡΤΉΣΕΙΣ ΤΟΥ ΚΏΔΙΚΑ ΑΥΤΟΎ
    int i,k;                                        // μετρητές
    fprintf(file,"%d %d\n", rows, cols);            // εκτυπώνει στην αρχή του αρχείου 2 αριθμούς: τον αριθμό των γραμμών και τον αριθμό των στηλών.
    for(i=0;i<rows;i++)                             // έτσι εξυπηρετείται η βασική διαδικασία που έχει επιλεχθεί για αυτό το πρόγραμμα -> ΤΟ ΔΙΆΒΑΣΜΑ ΤΩΝ ΓΡΑΜΜΏΝ ΚΑΙ ΤΩΝ ΣΤΗΛΏΝ ΕΝΌΣ ΠΊΝΑΚΑ ΑΠΌ ΤΟ ΊΔΙΟ ΤΟ ΑΡΧΕΊΟ ΤΟΥ ΠΊΝΑΚΑ
    {
        for(k=0;k<cols;k++)
        {
            fprintf(file,"%15.5lf ",array[i][k]);   // Μορφοποίηση εντός αρχείου: ακρίβεια 5 δεκαδικών ψηφίων και φάρδος 15 χαρακτήρων -> ΆΛΛΑΖΕΙ MANUALLY ΑΝΆΛΟΓΑ ΤΙΣ ΑΝΆΓΚΕΣ ΤΟΥ ΧΡΉΣΤΗ
        }
        fputc('\n',file);
    }
}
void pass_file_to_array(FILE *file, double **array, int rows, int cols) // ΠΕΡΝΆΕΙ ΤΑ ΔΕΔΟΜΈΝΑ ΕΝΌΣ ΑΡΧΕΊΟΥ ΣΕ ΈΝΑΝ ΠΊΝΑΚΑ
{
    int i,k;                                    // μετρητές
    for(i=0;i<rows;i++)
        for(k=0;k<cols;k++)
            fscanf(file,"%lf",&array[i][k]);    
}
void txt_files_from_folder_printer()                                    // ΠΡΟΒΆΛΛΕΙ ΌΛΑ ΤΑ .txt ΑΡΧΕΊΑ ΑΠΌ ΤΟΝ ΦΆΚΕΛΟ ΠΟΥ ΒΡΊΣΚΕΤΑΙ ΤΟ executable
{
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if( strstr(dir->d_name, ".txt") != NULL)    // επιλογή αρχείων με file extension .txt
                printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
}

// ΣΥΝΑΡΤΉΣΕΙΣ ΠΟΥ ΒΟΗΘΆΝΕ ΣΤΟ TESTING ΤΗΣ ΛΕΙΤΟΥΡΓΙΚΌΤΗΤΑΣ ΤΟΥ ΠΡΟΓΡΆΜΜΑΤΟΣ -> όχι πραγματική χρήση (ελάχιστες είναι οι περιπτώσεις που χρειάζεται ένας πίνακας με απολύτως τυχαίους αριθμούς)
void init_array_to_file(FILE *file, int rows, int cols)                 // ΑΡΧΙΚΟΠΟΙΕΊ ΕΝΑ ΑΡΧΕΊΟ ΜΕ ΈΝΑΝ ΠΊΝΑΚΑ ΠΟΥ ΠΕΡΙΈΧΕΙ ΤΥΧΑΊΟΥΣ ΑΡΙΘΜΟΎΣ
{
    int i,k;
    fprintf(file,"%d %d\n",rows,cols);                      // τυπώνει στην αρχή του αρχείου τον αριθμό των γραμμών και των στηλών
    for(i=0;i<rows;i++)                                     // όπως προειπώθηκε, βοηθάει στις βασικές διαδικασίες του προγράμματος
    {
        for(k=0;k<cols;k++)
            fprintf(file,"%15.5lf ",(rand()%1000)/1.33);    // στην συγκεκριμένη μορφή "...%1000..." οι αρθμοί που παράγονται είναι 3ψήφιοι(ως προς το ακέραιο μέρος) -> ΑΛΛΆΖΕΙ manually ΑΠΌ ΤΟΝ ΧΡΉΣΤΗ
        fputc('\n',file);                                   // μορφοποίηση εντός αρχείου: 15 χαρακτήρες πλάτος, 5 δεκαδικά ψηφία ακρίβεια
    }
}

// Συναρτήσεις για βασική διαχείριση 2-Dimensional-Arrays 
void create_array(double ***array, int rows, int cols)                  // ΔΗΜΙΟΥΡΓΕΊ ΜΕ DYNAMIC MEMORY ALLOCATION ΈΝΑΝ 2-DIMENSIONAL-ARRAY
{   // ως όρισμα δέχεται έναν τριπλό pointer, δηλαδή pointer σε 2D array(στο πρώτο του στοιχείο)
    int i,k;                                                // μετρητές

    (*array) = (double **)malloc(sizeof(double*)*rows);     // memory allocation για rows σε πλήθος συστοιχίες δεικτών σε double
    if((*array) == NULL)                                    // routine error check
    {
        printf("Error allocating memory for an array or a vector!");
        exit(0);
    }

    for(i=0;i<rows;i++)
    {
        (*array)[i]=(double*)malloc(sizeof(double)*cols);   // memory allocation για cols σε πλήθος στοιχεία double των rows σε πλήθος συστοιχιών συστοιχιών σε double
        if((*array)[i]==NULL)                               // routine error check
        {
            printf("Error allocating memory for an array or a vector!");
            exit(0);
        }
    }
}
void print_array(double **array, int rows, int cols)                    // ΠΡΟΒΆΛΛΕΙ ΈΝΑΝ ΔΙΣΔΙΆΣΤΑΤΟ ΠΊΝΑΚΑ ΜΕ ΚΟΜΨΉ ΜΟΡΦΉ
{
    putchar('\n');
    int i,k;                                    // μετρητές
    for(i=0;i<rows;i++)
    {
        putchar('|');                           // αγκύλη κελιού
        for(k=0;k<cols;k++)
            printf("%15.5lf ",array[i][k]);     // 15 χαρακτήρες πλάτος, 5 δεκαδικά ψηφία ακρίβεια -> ΑΛΛΆΖΕΙ manually ΑΠΌ ΤΟΝ ΧΡΉΣΤΗ
        putchar('|');
        putchar('\n');                          // ΑΛΛΑΓΉ ΓΡΑΜΜΉΣ ΑΝΆ row ΤΟΥ ΠΊΝΑΚΑ
    }
    putchar('\n');
}
void destroy_array(double **array, int rows, int cols)                   // ΑΠΟΔΕΣΜΕΎΕΙ ΤΗΝ ΜΝΉΜΗ ΠΟΥ ΚΑΤΑΛΑΜΒΆΝΕΙ ΕΝΑΣ ΔΙΣΔΙΆΣΤΑΤΟΣ ΠΊΝΑΚΑΣ
{                           // πρόκειται για πίνακα που είχε δεσμέψει τη μνήμη που καταλαμβάνει ΔΥΝΑΜΙΚΆ
    int i,k;                // μετρητές 
    for (i=0;i<rows;i++)    
        free(array[i]);     // ελευθερώνει πρώτα τις συστοιχίες (γραμμές του πίνακα)
    free(array);            // ολοκληρωτική ελευθέρωση
}
void init_your_array(double **array, int rows, int cols)//**                 // ΖΗΤΆΕΙ ΑΠΌ ΤΟΝ ΧΡΉΣΤΗ ΤΗΝ ΕΙΣΑΓΩΓΉ ΤΙΜΏΝ ΓΙΑ ΚΆΘΕ ELEMENT ΕΝΌΣ 2D ARRAY
{
    int i,k;                                            // μετρητές
    for(i=0;i<rows;i++)
    {
        for(k=0;k<cols;k++)
        {
            printf("~ Value for r%d-c%d: ",i+1,k+1);    // ζητάει τις τιμές
            scanf("%lf",&array[i][k]);                  // αποθήκευση αυτών στα elements του πίνακα
            fflush(stdin);
        }
    }
}


// determinant    cofactor    transpose
double determinant(double **array1, int rows)                                                                           // ΥΠΟΛΟΓΊΖΕΙ ΤΗΝ ΟΡΊΖΟΥΣΑ ΕΝΌΣ ΠΊΝΑΚΑ (ΑΝΑΔΡΟΜΙΚΉ ΣΥΝΆΡΤΗΣΗ)
{
    double s=1, det=0;
    double **array2;
    int i,j,m,n,c;
    create_array(&array2,rows,rows);
    // ALGORITHMOS DETERMINANT
    if(rows==1)
        return (array1[0][0]);
    else
    {
        det=0;
        for(c=0; c<rows; c++)
        {
            m=0;
            n=0;
            for(i=0;i<rows;i++)
            {
                for(j=0;j<rows;j++)
                {
                    array2[i][j]=0;
                    if(i!=0 && j!=c)
                    {
                        array2[m][n] = array1[i][j];
                        if(n<(rows-2))
                            n++;
                        else
                        {
                            n=0;
                            m++;
                        }
                    }
                }
            }
            det = det + s * (array1[0][c]*determinant(array2, rows-1));
            s = -1 * s;
        }
    }
    destroy_array(array2,rows,rows);
    return (det);
}
void transpose_parts(double **num, double **fac, int rows)                                                              // ΧΡΗΣΙΜΟΠΟΙΕΊΤΑΙ ΣΤΟΝ ΑΛΓΌΡΙΘΜΟ ΤΗΣ ΣΥΝΆΡΤΗΣΗΣ ΑΝΤΙΣΤΡΟΦΉΣ ΕΝΌΣ ΠΊΝΑΚΑ
{
    int i,j;
    double **b, **inverse;
    double d;
    create_array(&b,rows,rows);
    create_array(&inverse,rows,rows);

    //ALGORITHM
    for(i=0;i<rows;i++)
    {
        for(j=0;j<rows;j++)
        {
            b[i][j] = fac[j][i];
        }
    }
    d=determinant(num,rows);
    for(i=0;i<rows;i++)
    {
        for(j=0;j<rows;j++)
        {
            inverse[i][j] = b[i][j] / d;
        }
    }
    destroy_array(b,rows,rows);
    destroy_array(inverse,rows,rows);
}
void transpose_last_part_PASS_INVERSE_VALUES(double **num, double **fac, int rows, double **array_to_pass_inverse)      // ΠΑΝΟΜΟΙΌΤΥΠΗ ΜΕ ΤΗΝ ΠΡΟΗΓΟΎΜΕΝΗ ΣΥΝΆΡΤΗΣΗ ΑΠΛΆ ΤΏΡΑ ΘΑ ΑΠΟΘΗΚΕΥΤΕΊ ΚΆΠΟΥ ΤΟ ΑΠΟΤΈΛΕΣΜΑ ΤΗΣ (Ο ΑΝΤΊΣΤΡΟΦΟΣ ΕΝΌΣ ΠΊΝΑΚΑ) 
{
    int i,j;
    double **b, **inverse;
    double d;
    create_array(&b,rows,rows);
    create_array(&inverse,rows,rows);

    //ALGORITHM
    for(i=0;i<rows;i++)
    {
        for(j=0;j<rows;j++)
        {
            b[i][j] = fac[j][i];
        }
    }
    d=determinant(num,rows);
    for(i=0;i<rows;i++)
    {
        for(j=0;j<rows;j++)
        {
            inverse[i][j] = b[i][j] / d;
        }
    }
    for(i=0;i<rows;i++)
    {
        for(j=0;j<rows;j++)
        {
            array_to_pass_inverse[i][j]=inverse[i][j];
        }
    }
    //HERE I WANT TO SAVE THE inverse array
    destroy_array(b,rows,rows);
    destroy_array(inverse,rows,rows);
}
void cofactor(double **num, int rows, double **inverse)                                                                 // ΤΙΣ ΠΡΟΗΓΟΎΜΕΝΕΣ ΤΡΕΙΣ ΣΥΝΑΡΤΉΣΕΙΣ ΓΙΑ ΝΑ ΥΠΟΛΟΓΊΣΕΙ ΤΟΝ ΑΝΤΊΣΤΡΟΦΟ ΕΝΌΣ ΠΊΝΑΚΑ
{
    double **b, **fac;
    int p,q,m,n,i,j;
    create_array(&b,rows,rows);
    create_array(&fac,rows,rows);
    //ALGORITHM
    for(q=0;q<rows;q++)
    {
        for(p=0;p<rows;p++)
        {
            m=0;
            n=0;
            for(i=0;i<rows;i++)
            {
                for(j=0;j<rows;j++)
                {
                    if(i!=q && j!=p)
                    {
                        b[m][n] = num [i][j];
                        if (n < (rows-2))
                            n++;
                        else
                        {
                            n=0;
                            m++;
                        }
                    }
                }
            }
            fac[q][p] = pow(-1,q+p) * determinant(b,rows-1);
        }
        if(q!=rows-1)
            transpose_parts(num, fac, rows);
        else
        {
            transpose_last_part_PASS_INVERSE_VALUES(num, fac, rows,inverse);
        }
    }
    destroy_array(b,rows,rows);
    destroy_array(fac,rows,rows);
}

// ΣΥΝΑΡΤΉΣΕΙΣ ΠΟΥ ΒΟΗΘΆΝΕ ΣΤΙΣ ΣΥΝΑΡΤΉΣΕΙΣ ΓΙΑ ARRAYS (ΚΑΙ ΘΑ ΒΟΗΘΟΎΣΑΝ ΣΤΙΣ ΣΥΝΑΡΤΉΣΕΙΣ ΓΙΑ VECTORS)
void file_openner(FILE *file,char name[FILENAME_MAX+1], double ***array, int *rows, int *cols, int check)                               // ΖΗΤΆΕΙ ΤΟ ΌΝΟΜΑ ΕΝΌΣ ΑΡΧΕΊΟΥ, ΑΝΟΊΓΕΙ ΤΟ ΑΡΧΕΊΟ ΚΑΙ ΠΕΡΝΆΕΙ ΤΙΣ ΤΙΜΈΣ ΤΟΥ ΣΕ ΈΝΑΝ ΠΊΝΑΚΑ 
{   // ΩΣ ΟΡΊΣΜΑΤΑ ΠΕΡΝΆΩ ΤΙΣ ΔΙΕΥΘΎΝΣΕΙΣ ΤΟΥ ΠΊΝΑΚΑ, ΤΟΥ ΑΡΙΘΜΟΎ ΤΩΝ ΓΡΑΜΜΏΝ ΚΑΙ ΤΟΥ ΑΡΙΘΜΟΎ ΤΩΝ ΣΤΗΛΏΝ ΏΣΤΕ ΝΑ ΜΠΟΡΏ ΝΑ ΠΡΟΚΑΛΈΣΩ ΜΕΤΑΒΟΛΈΣ ΣΤΙΣ ΤΙΜΈΣ ΤΟΥΣ
    // ΣΤΗΝ ΣΥΝΆΡΤΗΣΗ ΔΊΝΟΝΤΑΙ ΟΙ ΔΙΕΥΘΎΝΣΕΙΣ ΑΥΤΈΣ ΚΕΝΈΣ ΑΠΌ ΣΗΜΑΝΤΙΚΉ ΠΛΗΡΟΦΟΡΊΑ ΚΑΙ ΜΕΤΆ ΤΗΝ ΚΛΉΣΗ ΤΗΣ, ΈΧΟΥΝ ΓΕΜΊΣΕΙ ΜΕ: -> τη διεύθυνση ενός 2D πίνακα rowsXcols
    int i,k;
    if(check==1)
        printf("~ Insert the name of the first array ~(Press 0 to exit this operation): ");
    else if(check==2)
        printf("~ Insert the name of the second array ~(Press 0 to exit this operation): ");

    start_array_function_1_openning:                // 'INSERT NAME' LOOP
    for(i=0;i<FILENAME_MAX+1;i++)                   // mhdenismos tou name -> apofugh problhmatwn
        name[i]='\0';

    scanf(" ");
    fgets(name,FILENAME_MAX+1,stdin);
    name[strlen(name)-1]='\0';

    // ESCAPING IF 0 IS GIVEN -> LUNEI KAMPOSA PROBLHMATAKIA
    if(strcspn("0",name)==0 && strlen(name)==1)
    {
        return;
    }
    strcat(name,".txt");                             // adding .txt

    // CHECKING EXISTANCE OF AN ARRAY WITH NAME "name.txt" 
    file=fopen(name,"r");
    if(file==NULL)
    {
        fclose(file);                                // kleinei thn 'pseudo-anagnwsh' tou arxeiou 
        printf("Array with name \"%s\" does not exist!\n",name);
        if(check==1)
            printf("\n~ Insert again the name of the first array ~(Press 0 to exit this operation): ");
        else if(check==2)
            printf("\n~ Insert again the name of the second array ~(Press 0 to exit this operation): ");
        goto start_array_function_1_openning;       // loupa uparjhs arxeiou
    }

    fscanf(file,"%d %d",rows,cols);                 // pairnei tis duo prwtes times tou arxeiou
    create_array(array,*rows,*cols);                // dynamically creating enan array rowsXcols
    pass_file_to_array(file,*array,*rows,*cols);    // pernaei tis times apo to file -> se enan prosorino array (embeleia sunarthshs)
    fclose(file);                                   // kleinei to arxeio, den mas xreiazetai parakatw
}
void existence_check(int choice_for_array_save, char name_new[FILENAME_MAX+1], FILE *file_new, double **array_new, int rows, int cols)  // ΕΛΈΓΧΕΙ ΑΝ ΥΠΆΡΧΕΙ ΈΝΑ ΑΡΧΕΊΟ ΤΟΥ ΟΠΟΊΟΥ ΤΟ ΌΝΟΜΑ ΖΗΤΆΕΙ ΚΑΙ ΔΗΜΙΟΥΡΓΕΊ ΈΝΑ ΚΑΙΝΟΎΡΙΟ ΑΡΧΕΊΟ ΌΤΑΝ ΤΟ ΕΙΣΑΓΏΜΕΝΟ ΌΝΟΜΑ ΔΕΝ ΥΠΆΡΧΕΙ
{
    int i;
    // NEW ARRAY: take name, file open "w", create temp_array, pass array to file, close file  ***
    if(choice_for_array_save==1)
    {
        // NAMING THE NEW ARRAY
        printf("~ Insert the name of the new array: ");

        array_creation:
        for(i=0;i<FILENAME_MAX+1;i++)               // mhdenismos tou array_sum gia apofugh tuxon problhmatwn me thn loupa tou detector
            name_new[i]='\0';
            
        scanf(" ");
        fgets(name_new,FILENAME_MAX+1,stdin);
        name_new[strlen(name_new)-1]=0;             // afairesh xarakthra allaghs grammhs
        strcat(name_new,".txt");                    // attach sto filename to ".txt" file extension
        
        // CHECKING EXISTENCE OF AN ARRAY WITH NAME "name_new.txt" 
        file_new=fopen(name_new,"r");
        if(file_new!=NULL)
        {
            fclose(file_new);                       // kleinei thn 'pseudo-anagnwsh' tou arxeiou 
            printf("Array with name \"%s\" already exists!\n"
                 "\n~ Insert another name for the new array: ",name_new);
            goto array_creation;
        }
        fclose(file_new);
        
        // CREATING A FILE WITH NAME "name_new.txt"
        file_new=fopen(name_new,"w");

        // PERNAW TIS TIMES TOU ATHROISMATOS PINAKWN STO NEW FILE
        pass_array_to_file(file_new,array_new,rows,cols);

        // CLOSING FILE file_new
        fclose(file_new);                      
    }
    else // DIAGRAFETAI O PINAKAS, DEN MAS ENDIAFEREI
    {
        printf("The result of the operation will be deleted!\n");
    }
}


// ΣΥΝΑΡΤΉΣΕΙΣ ΓΙΑ ARRAYS
void array_sum()                            // ΥΠΟΛΟΓΊΖΕΙ ΤΟ ΆΘΡΟΙΣΜΑ 2 ΠΙΝΆΚΩΝ                                 ΚΑΙ ΖΗΤΆΕΙ ΑΠΌ ΤΟΝ ΧΡΉΣΤΗ ΑΝ ΠΡΈΠΕΙ ΝΑ ΤΟ ΑΠΟΘΗΚΈΥΣΕΙ ΣΕ ΝΈΟ ΑΡΧΕΊΟ Ή ΝΑ ΤΟ ΔΙΑΓΡΆΨΕΙ
{
    // DECLARATIONS
    int i,k;
    int choice_for_array_save=0;

    FILE *file1;    //"r"
    char name1[FILENAME_MAX+1];
    double **array1;
    int rows1,cols1;

    FILE *file2;    //"r"
    char name2[FILENAME_MAX+1];
    double **array2;
    int rows2,cols2;

    FILE *file_sum; //"w"
    char name_sum[FILENAME_MAX+1];
    double **array_sum;
    // no need for rows and cols variables
   
    // ***   FIRST ARRAY: name, existance check, file open "r", create temp_array, pass file to temp_array, close file  ***
    file_openner(file1,name1,&array1,&rows1,&cols1,1);
    // ***   SECOND ARRAY: name, existance check, file open "r", create temp_array, pass file to temp_array, close file  ***
    file_openner(file2,name2,&array2,&rows2,&cols2,2);
    
    // ***   ADDITION CHECK + RETURN to exit the function
    if(rows1!=rows2 || cols1!=cols2)
    {
        printf( "Arrays \"%s\" and \"%s\" are not equal in size\n"
                "They can not be added!\n",name1,name2);
        return; // EXITING THE ADDING OPERATION
    }

    // *** ADDITION ***
    create_array(&array_sum,rows1,cols1);
    for(i=0;i<rows1;i++)
        for(k=0;k<cols1;k++)
            array_sum[i][k]=array1[i][k]+array2[i][k];

    // ***   PRINTING THE ADDITION's RESULT
    printf("\nThe result of the addition of \"%s\" and \"%s\" is:\n",name1,name2);
    print_array(array_sum,rows1,cols1);

    // ***   ASKING TO SAVE OR DELETE
    printf("~ Would you like to save the result? ~(Press '1' for YES or any other button for NO): ");
    scanf("%d",&choice_for_array_save);
    fflush(stdin);

    // ***   SUM ARRAY: take name, file open "w", create temp_array, pass array to file, close file  ***
    existence_check(choice_for_array_save,name_sum,file_sum,array_sum,rows1,cols1); 
    
    // ***   FREE() allocated memory
    destroy_array(array1,rows1,cols1);
    destroy_array(array2,rows2,cols2);
    destroy_array(array_sum,rows1,cols1);
}
void array_sub()                            // ΥΠΟΛΟΓΊΖΕΙ ΤΗΝ ΑΦΑΊΡΕΣΗ ΕΝΌΣ ΠΊΝΑΚΑ ΑΠΌ ΈΝΑΝ ΆΛΛΟ ΠΊΝΑΚΑ         ΚΑΙ ΖΗΤΆΕΙ ΑΠΌ ΤΟΝ ΧΡΉΣΤΗ ΑΝ ΠΡΈΠΕΙ ΝΑ ΤΟ ΑΠΟΘΗΚΈΥΣΕΙ ΣΕ ΝΈΟ ΑΡΧΕΊΟ Ή ΝΑ ΤΟ ΔΙΑΓΡΆΨΕΙ
{
    // DECLARATIONS
    int i,k;
    int choice_for_array_save=0;

    FILE *file1;    //"r"
    char name1[FILENAME_MAX+1];
    double **array1;
    int rows1,cols1;

    FILE *file2;    //"r"
    char name2[FILENAME_MAX+1];
    double **array2;
    int rows2,cols2;

    FILE *file_sub; //"w"
    char name_sub[FILENAME_MAX+1];
    double **arr_sub;
    // no need for rows and cols variables
   

    // ***   FIRST ARRAY: name, existance check, file open "r", create temp_array, pass file to temp_array, close file  ***
    file_openner(file1,name1,&array1,&rows1,&cols1,1);
    // ***   SECOND ARRAY: name, existance check, file open "r", create temp_array, pass file to temp_array, close file  ***
    file_openner(file2,name2,&array2,&rows2,&cols2,2);
    
    // ***   SUBTRACTION CHECK + RETURN to exit the function
    if(rows1!=rows2 || cols1!=cols2)
    {
        printf( "Arrays/Vectors \"%s\" and \"%s\" are not equal in size\n"
                "They can not be sutracted!\n",name1,name2);
        return;                                      // EXITING THE ADDING OPERATION
    }

    // *** SUBTRACTION ***
    create_array(&arr_sub,rows1,cols1);
    for(i=0;i<rows1;i++)
        for(k=0;k<cols1;k++)
            arr_sub[i][k]=array1[i][k]-array2[i][k];

    // ***   PRINTING THE SUBTRACTION RESULT
    printf("\nThe result of the subtraction of \"%s\" out of \"%s\" is:\n",name2,name1);
    print_array(arr_sub,rows1,cols1);

    // ***   ASKING TO SAVE OR DELETE
    printf("~ Would you like to save the result? ~(Press '1' for YES or any other button for NO): ");
    scanf("%d",&choice_for_array_save);
    fflush(stdin);

    // ***   SUB ARRAY: take name, file open "w", create temp_array, pass array to file, close file  ***
    existence_check(choice_for_array_save,name_sub,file_sub,arr_sub,rows1,cols1); 

    // ***   FREE() allocated memory
    destroy_array(array1,rows1,cols1);
    destroy_array(array2,rows2,cols2);
    destroy_array(arr_sub,rows1,cols1);
}
void array_num_product()                    // ΥΠΟΛΟΓΊΖΕΙ ΤΟ ΓΙΝΌΜΕΝΟ ΕΝΌΣ ΠΊΝΑΚΑ ΜΕ ΈΝΑΝ ΑΡΙΘΜΌ                ΚΑΙ ΖΗΤΆΕΙ ΑΠΌ ΤΟΝ ΧΡΉΣΤΗ ΑΝ ΠΡΈΠΕΙ ΝΑ ΤΟ ΑΠΟΘΗΚΈΥΣΕΙ ΣΕ ΝΈΟ ΑΡΧΕΊΟ Ή ΝΑ ΤΟ ΔΙΑΓΡΆΨΕΙ
{
    // DECLARATIONS
    int i,k;
    int choice_for_array_save=0;
    double num;

    FILE *file1;    //"r"
    char name1[FILENAME_MAX+1];
    double **array1;
    int rows1,cols1;

    FILE *file_prod;
    char name_prod[FILENAME_MAX+1];
    double **array_prod;

    // ***   FIRST ARRAY: name, existance check, file open "r", create temp_array, pass file to temp_array, close file  ***
    file_openner(file1,name1,&array1,&rows1,&cols1,1);

    // ASKING FOR A REAL NUMBER
    printf("~ Insert a Real Number: ");
    scanf("%lf",&num);
    fflush(stdin);

    // CREATING THE NEW TEMP_ARRAY_PROD_NUM
    create_array(&array_prod,rows1,cols1);
    
    // MULTIPLICATION
    for(i=0;i<rows1;i++)
        for(k=0;k<cols1;k++)
            array_prod[i][k]=array1[i][k]*num;

    // PRINTING THE ARRAY
    printf("\nThe Product of the \"%s\" array/vector and %lf is: \n",name1,num);
    print_array(array_prod,rows1,cols1);

    // ASKING TO SAVE OR DELETE
    printf("~ Would you like to save the result? ~(Press '1' for YES or any other button for NO): ");
    scanf("%d",&choice_for_array_save);
    fflush(stdin);

    // ***   prod ARRAY: take name, file open "w", create temp_array, pass array to file, close file  ***
    existence_check(choice_for_array_save,name_prod,file_prod,array_prod,rows1,cols1); 

    // *** FREE() allocated memory;
    destroy_array(array1,rows1,cols1);
    destroy_array(array_prod,rows1,cols1);
}
void array_array_prod()                     // ΥΠΟΛΟΓΊΖΕΙ ΤΟ ΓΙΝΌΜΕΝΟ 2 ΠΙΝΆΚΩΝ                                 ΚΑΙ ΖΗΤΆΕΙ ΑΠΌ ΤΟΝ ΧΡΉΣΤΗ ΑΝ ΠΡΈΠΕΙ ΝΑ ΤΟ ΑΠΟΘΗΚΈΥΣΕΙ ΣΕ ΝΈΟ ΑΡΧΕΊΟ Ή ΝΑ ΤΟ ΔΙΑΓΡΆΨΕΙ
{
    // DECLARATIONS
    int i,k,b;
    int choice_for_array_save=0;
    double sum=0.0;

    FILE *file1;    //"r"
    char name1[FILENAME_MAX+1];
    double **array1;
    int rows1,cols1;

    FILE *file2;    //"r"
    char name2[FILENAME_MAX+1];
    double **array2;
    int rows2,cols2;

    FILE *file_prod; //"w"
    char name_prod[FILENAME_MAX+1];
    double **array_prod;
    // no need for rows and cols variables
    
    // ***   FIRST ARRAY: name, existance check, file open "r", create temp_array, pass file to temp_array, close file  ***
    file_openner(file1,name1,&array1,&rows1,&cols1,1);
    // ***   SECOND ARRAY: name, existance check, file open "r", create temp_array, pass file to temp_array, close file  ***
    file_openner(file2,name2,&array2,&rows2,&cols2,2);

    // ***   product CHECK + RETURN to exit the function
    if(rows2!=cols1)
    {
        printf( "Arrays \"%s\" and \"%s\" are not equal in size\n"
                "There cannot be a product!\n",name1,name2);
        return;  // exiting the operation
    }

    // ***   PRODUCT   ***
    create_array(&array_prod,rows1,cols2);
    for(i=0;i<cols2;i++)
    {
        for(k=0;k<rows1;k++)
        {
            for(b=0;b<cols1;b++)
            {
                sum+=array1[k][b]*array2[b][i];
            }
            array_prod[k][i]=sum;
            sum=0.0;
        }
    }

    // ***   PRINTING THE PRODUCT RESULT
    printf("\nThe result of the product of \"%s\" and \"%s\" is:\n",name1,name2);
    print_array(array_prod,rows1,cols2);

    // ***   ASKING TO SAVE OR DELETE
    printf("~ Would you like to save the result? ~(Press '1' for YES or any other button for NO): ");
    scanf("%d",&choice_for_array_save);
    fflush(stdin);

    // ***   PRODUCT ARRAY: take name, file open "w", create temp_array, pass array to file, close file  ***
    existence_check(choice_for_array_save,name_prod,file_prod,array_prod,rows1,cols2);

    // ***   FREE() allocated memory
    destroy_array(array1,rows1,cols1);
    destroy_array(array2,rows2,cols2);
    destroy_array(array_prod,rows1,cols2);
}
void array_transpose()                      // ΥΠΟΛΟΓΊΖΕΙ ΤΟΝ ΑΝΆΣΤΡΟΦΟ ΕΝΌΣ ΠΊΝΑΚΑ                             ΚΑΙ ΖΗΤΆΕΙ ΑΠΌ ΤΟΝ ΧΡΉΣΤΗ ΑΝ ΠΡΈΠΕΙ ΝΑ ΤΟΝ ΑΠΟΘΗΚΈΥΣΕΙ ΣΕ ΝΈΟ ΑΡΧΕΊΟ Ή ΝΑ ΤΟ ΔΙΑΓΡΆΨΕΙ
{
    // DECLARATIONS
    int i,k;
    int choice_for_array_save=0;

    FILE *file1;            //"r"
    char name1[FILENAME_MAX+1];
    double **array1;
    int rows1,cols1;

    FILE *file_transpose;   //"w"
    char name_transpose[FILENAME_MAX+1];
    double **array_transpose;

    // FIRST ARRAY: name, existance check, file open "r", create temp_array, pass file to temp_array, close file  ***
    file_openner(file1,name1,&array1,&rows1,&cols1,1);

    // ANASTROFOS ALGORITHMOS
    create_array(&array_transpose,cols1,rows1);
    for(i=0;i<rows1;i++)
        for(k=0;k<cols1;k++)
            array_transpose[k][i]=array1[i][k];

    // PRINTING THE ARRAY
    printf("\nThe Transpose of the \"%s\" array is: \n",name1);
    print_array(array_transpose,cols1,rows1);

    // ASKING TO SAVE OR DELETE
    printf("~ Would you like to save the result? ~(Press '1' for YES or any other button for NO): ");
    scanf("%d",&choice_for_array_save);
    fflush(stdin);

    // TRANSPOSE ARRAY: take name, file open "w", create temp_array, pass array to file, close file  ***
    existence_check(choice_for_array_save,name_transpose,file_transpose,array_transpose,cols1,rows1);

    // FREE() allocated memory
    destroy_array(array1,rows1,cols1);
    destroy_array(array_transpose,cols1,rows1);
}
void from_array_row_elim()                  // ΔΙΑΓΡΆΦΕΙ ΜΊΑ ΖΗΤΟΎΜΕΝΗ ΑΠΌ ΤΟΝ ΧΡΉΣΤΗ ΓΡΑΜΜΉ ΑΠΌ ΈΝΑΝ ΠΊΝΑΚΑ    ΚΑΙ ΖΗΤΆΕΙ ΑΠΌ ΤΟΝ ΧΡΉΣΤΗ ΑΝ ΠΡΈΠΕΙ ΝΑ ΤΟΝ ΑΠΟΘΗΚΈΥΣΕΙ ΣΕ ΝΈΟ ΑΡΧΕΊΟ Ή ΝΑ ΤΟ ΔΙΑΓΡΆΨΕΙ
{
    // DECLARATIONS
    int i,k,counter=0;
    int choice_for_array_save=0;
    int row_eliminate=-1;

    FILE *file1;    //"r"
    char name1[FILENAME_MAX+1];
    double **array1;
    int rows1,cols1;

    FILE *file_NEW; //"w"
    char name_NEW[FILENAME_MAX+1];
    double **array_NEW;
    // no need for size

    // FIRST ARRAY: name, existance check, file open "r", create temp_array, pass file to temp_array, close file  ***
    file_openner(file1,name1,&array1,&rows1,&cols1,1);

    // CREATING THE NEW TEPM_ARRAY_NEW
    create_array(&array_NEW,rows1-1,cols1);

    // ELIMINATING THE GIVEN ROW
    do{
    printf("\nInsert the number of the row to eliminate: ");
    scanf("%d",&row_eliminate);
    fflush(stdin);}
    while(row_eliminate<0 || row_eliminate>rows1);

    // algorithmos apaloifhs
    for(i=0;i<cols1;i++)                                // mhdenizei ta stoixeia ths zhtoumenhs grammhs
        array1[row_eliminate-1][i]=0.0;
    for(i=0;i<rows1;i++)                                // tracing ston arxiko pinaka
    {                                                   // edw, kaluptontai ta mhdenismena (mias sugkekrimenhs grammhs) stoixeia apo tis amesws epomenes grammes
        for(k=0;k<cols1;k++)                            // "olisthisi grammhs pros ta panw" dhladh
        {
            if(i==row_eliminate-1)
                counter=1;
            if((array1[i][k]==0.0) && (counter==1))
            {
                if(k==cols1-1)
                    counter++;                          //enas metrhths wste th deuterh fora na apofeuxthei auth h 'if'
            }
            else if(counter==2)
                array_NEW[i-1][k]=array1[i][k];
            else
                array_NEW[i][k]=array1[i][k];
        }
    }

    // PRINTING THE NEW_ARRAY
    printf("\nThe New Array/Vector is: \n");
    print_array(array_NEW,rows1-1,cols1);

    // ASKING TO SAVE OR DELETE
    printf("~ Would you like to save the result? ~(Press '1' for YES or any other button for NO): ");
    scanf("%d",&choice_for_array_save);
    fflush(stdin);

    // ***   NEW_ARRAY after row elim: take name, file open "w", create temp_array, pass array to file, close file  ***
    existence_check(choice_for_array_save,name_NEW,file_NEW,array_NEW,rows1-1,cols1);

    // FREE() allocated memory
    destroy_array(array1,rows1,cols1);
    destroy_array(array_NEW,rows1-1,cols1);
}
void from_array_column_elim()               // ΔΙΑΓΡΆΦΕΙ ΜΊΑ ΖΗΤΟΎΜΕΝΗ ΑΠΌ ΤΟΝ ΧΡΉΣΤΗ ΣΤΉΛΗ ΑΠΌ ΈΝΑΝ ΠΊΝΑΚΑ     ΚΑΙ ΖΗΤΆΕΙ ΑΠΌ ΤΟΝ ΧΡΉΣΤΗ ΑΝ ΠΡΈΠΕΙ ΝΑ ΤΟΝ ΑΠΟΘΗΚΈΥΣΕΙ ΣΕ ΝΈΟ ΑΡΧΕΊΟ Ή ΝΑ ΤΟ ΔΙΑΓΡΆΨΕΙ
{
    // DECLARATIONS
    int i,k,counter=0;
    int choice_for_array_save=0;
    int col_eliminate=-1;

    FILE *file1;    //"r"
    char name1[FILENAME_MAX+1];
    double **array1;
    int rows1,cols1;

    FILE *file_NEW; //"w"
    char name_NEW[FILENAME_MAX+1];
    double **array_NEW;
    // no need for size

    // FIRST ARRAY: name, existance check, file open "r", create temp_array, pass file to temp_array, close file  ***
    file_openner(file1,name1,&array1,&rows1,&cols1,1);

    // CREATING THE NEW TEPM_ARRAY_NEW
    create_array(&array_NEW,rows1,cols1-1);

    // ELIMINATING THE GIVEN COLUMN
    do{
    printf("\nInsert the number of the column to eliminate: ");
    scanf("%d",&col_eliminate);
    fflush(stdin);
    }
    while(col_eliminate<0 || col_eliminate>cols1);
    
    // algorithmos apaloifhs                            // PANOMOIOTUPOS ME TON ALGORITHMO APALOIFHS GRAMMHS APO PINAKA
    for(i=0;i<rows1;i++)
        array1[i][col_eliminate-1]=0.0;         
    for(k=0;k<cols1;k++)        // tracing ston arxiko pinaka
    {
        for(i=0;i<rows1;i++)
        {
            if(k==col_eliminate-1)
                counter=1;
            if((array1[i][k]==0.0) && (counter==1))
            {
                if(i==rows1-1)
                    counter++;  //enas metrhths wste th deuterh fora na apofeuxthei auth h 'if'
            }
            else if(counter==2)
                array_NEW[i][k-1]=array1[i][k];
            else
                array_NEW[i][k]=array1[i][k];
        }
    }

    // PRINTING THE NEW_ARRAY
    printf("\nThe New Array/Vector is: \n");
    print_array(array_NEW,rows1,cols1-1);

    // ASKING TO SAVE OR DELETE
    printf("~ Would you like to save the result? ~(Press '1' for YES or any other button for NO): ");
    scanf("%d",&choice_for_array_save);
    fflush(stdin);

    // NEW_ARRAY after column elim: take name, file open "w", create temp_array, pass array to file, close file  ***
    existence_check(choice_for_array_save,name_NEW,file_NEW,array_NEW,rows1,cols1-1);

    // FREE() allocated memory
    destroy_array(array1,rows1,cols1);
    destroy_array(array_NEW,rows1,cols1-1);
}
void determinant_calculator()               // ΥΠΟΛΟΓΊΖΕΙ ΤΗΝ ΟΡΊΖΟΥΣΑ (ΑΝ ΓΊΝΕΤΑΙ) ΑΠΌ ΈΝΑΝ ΠΊΝΑΚΑ ΚΑΙ ΤΗΝ ΠΡΟΒΆΛΕΙ ΣΤΟΝ ΧΡΉΣΤΗ
{
    // DECLARATIONS
    int i,k;
    double d;

    FILE *file1;    //"r"
    char name1[FILENAME_MAX+1];
    double **array1;
    int rows1,cols1;

    // ***   FIRST ARRAY: name, existance check, file open "r", create temp_array, pass file to temp_array, close file  ***
    file_openner(file1,name1,&array1,&rows1,&cols1,1);

    // checking if r1=c1 -> is a matrix
    if(rows1!=cols1)
    {
        printf("\nArray \"%s\" is not a matrix (rows=cols)!\n",name1);
        printf("Its Determinant can not be calculated\n");
        return;
    }
    // else continue...
    // rows1=cols1

    // RESULT PRINTING    
    d=determinant(array1,rows1);
    printf("\nThe Determinant of the matrix \"%s\" is: %.5lf\n",name1,d);

    // FREE() array1
    destroy_array(array1,rows1,cols1);
    return;
}
void array_inverse()                        // ΥΠΟΛΟΓΊΖΕΙ ΤΟΝ ΑΝΤΊΣΤΡΟΦΟ ΕΝΌΣ ΠΊΝΑΚΑ (ΑΝ ΥΠΆΡΧΕΙ)               ΚΑΙ ΖΗΤΆΕΙ ΑΠΌ ΤΟΝ ΧΡΉΣΤΗ ΑΝ ΠΡΈΠΕΙ ΝΑ ΤΟΝ ΑΠΟΘΗΚΈΥΣΕΙ ΣΕ ΝΈΟ ΑΡΧΕΊΟ Ή ΝΑ ΤΟΝ ΔΙΑΓΡΆΨΕΙ
{
    // DECLARATIONS
    int i,k;
    double d;
    int choice_for_array_save=0;

    FILE *file1;        //"r"
    char name1[FILENAME_MAX+1];
    double **array1;
    int rows1,cols1;

    FILE *file_inverse;  //"w"
    char name_inverse[FILENAME_MAX+1];
    double **array_inverse;
    //no need for inverse_array's size

    // ***   FIRST ARRAY: name, existance check, file open "r", create temp_array, pass file to temp_array, close file  ***
    file_openner(file1,name1,&array1,&rows1,&cols1,1);
    
    // MATRIX CHECK
    if(rows1!=cols1)
    {
        printf("\nArray is not a matrix(rows1=cols1)\n"
                 "Its inverse can not be calculated!\n");
        return;
    }

    //ALGORITHM FOR INVERSE PRINT AND SAVE
    create_array(&array_inverse,rows1,rows1); //rows1=cols1=size of inverse matrix
    d=determinant(array1,rows1);
    if(d==0)
    {
        printf( "\nDet(\"%s\") = 0.0\n"
                "Inverse of this Array is not possible!\n",name1);
        return;
    }
    if(rows1==1)
    {
        printf( "\nArray is a value\n"
                "Its Inverse is 1/Array: %.5lf \n",(1.0/array1[0][0]));
        array_inverse[0][0]=(1.0/array1[0][0]);
        return;
    }
    else
        cofactor(array1,rows1,array_inverse);
    
    printf("\nThe inverse of matrix \"%s\" is: \n",name1);
    print_array(array_inverse,rows1,rows1);
    
    // ASKIGN TO SAVE the new array (inverse)
    printf("~ Would you like to save the result? ~(Press '1' for YES or any other button for NO): ");
    scanf("%d",&choice_for_array_save);
    fflush(stdin);

    // ARRAY_INVERSE: take name, file open "w", create temp_array, pass array to file, close file  ***
    existence_check(choice_for_array_save,name_inverse,file_inverse,array_inverse,rows1,rows1);

    // FREE() array1/array_inverse
    destroy_array(array1,rows1,cols1);
    destroy_array(array_inverse,rows1,cols1);
}


// συνάρτηση ένδειξης σημείου ΚΕΝΟΎ ΚΏΔΙΚΑ κατά
void print_no_time()
{
    printf("\nEasy to write code, there was no time though (ALL VECTORS SELECTIONS ARE JUST EMPTY CODE THAT DOESNT DISTURB THE PROGRAM'S FUNCTIONALITY)\n");
}

int main(void)
{
    //  ***     HELLO WORLD     ***
    {
    srand(time(NULL)); // random number generator
    printf( "\t\t\t\t\t _____________________________________\n"
            "\t\t\t\t\t|                                     |                                        ______________ \n"
            "\t\t\t\t\t|            2022 PROJECT             |                                       |              |\n"
            "\t\t\t\t\t|      LINEAR ALGEBRA OPERATIONS      |                                       |   Ntoylker   |\n"
            "\t\t\t\t\t|  DEVELOPER:   NIKOLAOS TOULKERIDHS  |                                       |______________|\n"
            "\t\t\t\t\t|_____________________________________|\n");
    
    do
    {
        printf("\n~ Press the Space button to begin");
    }
    while(getch()!=' ');

    printf( "\n\n\tDEVELOPER'S ADVICE TO THE USER:"
            "\nWhen you create/load/save/rename/delete an array/vector\n"
            "Write the name WITHOUT THE \".txt\" file extension !!!\n");
    do
    {
        printf("\n~ Press the Space button to continue");
    }
    while(getch()!=' ');
    }
    
    int choice_1=0; // metablhth pou tha xrhsimepsei sthn lhpsh ths apofashs tou xrhsth kai ulopoihsh auths
    // mhdenismos ths choice_1 -> apofugh problhmatwn eisodou xrhsth
    
    
    //   ***     MAIN MENU      ***  
    {
    printf( "\n\n\t*** MAIN MENU ***\n"
            "| 1 | Create an array/vector\n"
            "| 2 | Load an array/vectors\n"
            "| 3 | See the available arrays/vectors\n"
            "| 4 | Rename an array/vector\n"
            "| 5 | Delete an array/vector\n"
            "| 6 | Use Arrays\n"
            "| 7 | BACK TO MAIN MENU\n"
            "| 8 | END PROGRAM\n"
            "| 9 | CREDIT SCENES\n");
    }
    
    
    //   ***    COMBAT SCENE    ***
    {
    while(1)                    // MAIN LOOP
    {
        asking_user:            // all cases come back here until the "terminate" choice is given
        choice_1=0;             // mhdenismos ths choice_1 -> apofugh problhmatwn eisodou xrhsth
        printf("\n~ (MAIN) What do you want to do? ~(Press 7 for main menu): ");
        scanf("%d",&choice_1);
        fflush(stdin);
        switch(choice_1)        // SWITCH DIADRASHS XRHSTH-PROGRAMMATOS  
        {
            case 1:             // CREATE AN ARRAY
            {                                                                
                FILE *file_1;

                int rows,cols;                              // αριθμός γραμμών και στηλών
                int i;                                      // μετρητής 
                int inside_1_choice;                        // μεταβλητή αποθήκευσης της επιλογής initialization                       
                char array_name[FILENAME_MAX+1];            // συστοιχία αποθήκευσης του στρινγκ ονόματος

                printf("\n~ Insert the name of the new array ~(Press 0 to exit this operation): ");

                start_of_1:                                 // MAIN 'GIVE_NAME' LOOP
                for(i=0;i<FILENAME_MAX+1;i++)               // mhdenismos tou array_name gia apofugh tuxon problhmatwn me thn loupa tou detector
                    array_name[i]='\0';
                scanf(" ");                                 // antimetwpish problhmatwn me thn buffer kai thn fgets
                fgets(array_name,FILENAME_MAX+1,stdin);
                array_name[strlen(array_name)-1]=0;         // afairesh xarakthra allaghs grammhs
                
                // ESCAPING IF 0 IS GIVEN -> LUNEI KAMPOSA PROBLHMATAKIA
                if(strcspn("0",array_name)==0 && strlen(array_name)==1)
                {
                    goto asking_user;
                }

                strcat(array_name,".txt");                  // attach sto filename to ".txt" file extension
                
                // CHECKING EXISTANCE OF AN ARRAY WITH NAME "array_name.txt" 
                file_1=fopen(array_name,"r");
                if(file_1!=NULL)                            // routine check
                {
                    fclose(file_1);                         // kleinei thn 'pseudo-anagnwsh' tou arxeiou 
                    printf("Array with name \"%s\" already exists!\n"
                        "\n~ Insert another name for the array you want to create ~(Press 0 to exit this operation): ",array_name);
                    goto start_of_1;
                }
                fclose(file_1);                             // kleinei thn 'pseudo-anagnwsh' tou arxeiou 
                
                // FILE CREATING
                file_1=fopen(array_name,"w");
                if(file_1==NULL)                            // routine check
                {
                    printf("Could not Create array \"%s\"!",array_name);
                    goto terminator;
                }

                // ΔΙΑΔΙΚΑΣΊΕΣ
                do{                                         // rows
                    printf("~ Insert the number of ROWS of the array: ");
                    scanf("%d",&rows);
                    fflush(stdin);
                }while(rows<=0);
                
                do{                                         // cols
                    printf("~ Insert the number of COLUMNS of the array: ");
                    scanf("%d",&cols);
                    fflush(stdin);
                }while(cols<=0);

                // initialization
                printf("Array's initialization:\n"
                        "~ 1.Provide your own values for the array's members\n"
                        "~ 2.Initialize randomly (USE: to test the program's functionality): ");
                scanf("%d",&inside_1_choice);
                fflush(stdin);
                while(inside_1_choice<=0 || inside_1_choice>=3)
                {
                    printf("~ Insert a number between 1 and 2, according to the list above: ");
                    scanf("%d",&inside_1_choice);
                    fflush(stdin);
                }

                switch(inside_1_choice) // INSIDE CHOICE FOR ARRAY'S INITIAL VALUES
                {
                case 1:                 // MANUAL INITIALIZATION
                    {
                        double **temp_array;
                        create_array(&temp_array,rows,cols);
                        init_your_array(temp_array,rows,cols);
                        pass_array_to_file(file_1,temp_array,rows,cols);
                        destroy_array(temp_array,rows,cols);
                        break;
                    }
                case 2:                 // RANDOM INITIALIZATION 
                    {
                        init_array_to_file(file_1,rows,cols);
                        break;
                    }
                default:                // USELESS because of while defensive loop for 'inside_1_choice'
                    break;
                }
                
                // CLOSING FILE
                fclose(file_1);

                break; // exiting switch(choice_1);
            }
            case 2:             // LOAD AN ARRAY
            {
                FILE *file_1;

                int rows,cols;
                char array_name[FILENAME_MAX+1];
                double **array;                                 // pointer pou tha deijei ston array mesw ths sunarthshs kai meta tha ginei free();

                ask_for_arrays_name_to_load:                    // 'INSERT NAME' LOOP
                for(int a=0;a<FILENAME_MAX+1;a++)               // grhgoros mhdenismos twn stoixeiwn ths sustoixias array_name, to not cause any trouble later on
                    array_name[a]=0;
                
                printf("\n~ Insert the name of the array to load ~(Press 0 to exit this operation): ");
                scanf(" ");                                     // antimetwpish sfalmatwn eisagwghs
                fgets(array_name,FILENAME_MAX+1,stdin);
                array_name[strlen(array_name)-1]='\0';

                // ESCAPING IF 0 IS GIVEN -> LUNEI KAMPOSA PROBLHMATAKIA
                if(strcspn("0",array_name)==0 && strlen(array_name)==1)
                {
                    goto asking_user;
                }

                strcat(array_name,".txt");                      // attach sto filename to ".txt" file extension

                file_1=fopen(array_name,"r");                   // diabazei to arxeio "array_name"
                if(file_1==NULL)                                // routine check
                {
                    printf("Could not find array with name \"%s\"!\n",array_name);
                    goto ask_for_arrays_name_to_load;
                }

                fscanf(file_1,"%d %d",&rows,&cols);             // diabazei apo to .txt tis diastaseis tou pinaka. (toi opoies exoun dothei apo thn init_array_to_file ALREADY)

                create_array(&array,rows,cols);                 // DHMIOURGEI ARRAY ME DYNAMIC MEMORY ALLOCATION
                pass_file_to_array(file_1,array,rows,cols);     // DIABAZEI TIS TIMES APO TO .txt FILE KAI TIS PERNAEI STON ARRAY
                printf("\n***\t%s\t***",array_name);            // morfopoihsh emfanishs
                print_array(array,rows,cols);                   // PRINTAREI TON ARRAY
                destroy_array(array,rows,cols);                 // ELEUTHERWNEI THN MNHMH POU DESMEUSE O ARRAY

                // CLOSING FILE
                fclose(file_1);
                
                break; // exiting switch(choice_1);
            }
            case 3:             // SHOW AVAILABLE ARRAYS
            {
                printf( "\nThe available arrays are:\n");
                printf("--------------------\n");
                txt_files_from_folder_printer();
                printf("--------------------\n"); // diorthwsi sthn stdout, morfopoihsh ejodou
                break; // exiting switch(choice_1);
            }
            case 4:             // RENAME AN EXISTING ARRAY
            {
                FILE *file_1;
                char current_file_name[FILENAME_MAX+1];
                char new_file_name[FILENAME_MAX+1];
                int attempts=0;                                                 // μεταβλητή ελέγχου: αν 3 φορές αποτύχει το rename ενός πίνακα -> ΘΑ ΤΕΡΜΑΤΊΖΕΙ ΤΟ ΠΡΌΓΡΑΜΜΑ

                // ASKING FOR THE ARRAY'S NAME
                printf("\n~ Insert the array's name ~(Press 0 to exit this operation): ");                 // eisodos tou palio onomatos

                ask_for_name_to_rename:                                         // 'INSERT NAME' LOOP
                scanf(" "); 
                fgets(current_file_name, FILENAME_MAX+1, stdin);
                current_file_name[strlen(current_file_name)-1]='\0';            // mhdenismos tou xaralthra allaghs grammhs
                
                // ESCAPING IF 0 IS GIVEN -> LUNEI KAMPOSA PROBLHMATAKIA
                if(strcspn("0",current_file_name)==0 && strlen(current_file_name)==1)
                {
                    goto asking_user;
                }

                strcat(current_file_name,".txt");                                      // attach sto filename to ".txt" file extension

                // CHECKING EXISTANCE OF AN ARRAY WITH NAME "array_name.txt" 
                file_1=fopen(current_file_name,"r");
                if(file_1==NULL)
                {
                    fclose(file_1);                                             // kleinei thn 'pseudo-anagnwsh' tou arxeiou 
                    printf("Array with name \"%s\" does not exist!\n"
                        "\n~ Insert again the name of the array you want rename ~(Press 0 to exit this operation): ",current_file_name);
                    goto ask_for_name_to_rename;
                } // else -> FILE "current_file_name" EXISTS
                fclose(file_1);                                                 // kleinei thn 'pseudo-anagnwsh' tou arxeiou 
                
                // ASKING FOR THE ARRAY'S NEW NAME
                printf("\n~ Insert \"%s\" new name ~(Press 0 to exit this operation): ",current_file_name);
                scanf(" "); 
                fgets(new_file_name, FILENAME_MAX+1, stdin);
                new_file_name[strlen(new_file_name)-1]='\0';                    // mhdenismos tou xaralthra allaghs grammhs

                // ESCAPING IF 0 IS GIVEN -> LUNEI KAMPOSA PROBLHMATAKIA
                if(strcspn("0",new_file_name)==0 && strlen(new_file_name)==1)
                {
                    fclose(file_1);                                             // closing the file that openned above, the file of the array that would be renamed
                    goto asking_user;
                }

                strcat(new_file_name,".txt");

                // RENAMING CHECK
                if(rename(current_file_name, new_file_name))
                {
                    printf( "Array with name \"%s\" exists already\n",new_file_name);
                    printf( "Array \"%s\" could not be renamed!\n",current_file_name);
                    if(attempts==0)
                    {
                        printf( "You will be given 3 more attempts to rename an array, your failure will mean the program's termination!\n");
                    }
                    if(attempts==3)
                    {
                        printf( "\nRENAMING ATTEMPTS LIMIT REACHED!\n");
                        goto terminator;                                        // GOES ALL THE WAY DOWN TO TERMINATE THE PROGRAM 
                    }
                    printf( "\nAttempt number: %d"
                            "\n~ Insert again the name of the array you want rename: ",attempts+1);
                    attempts++;
                    goto ask_for_name_to_rename;
                }
                else
                {
                    printf("\nArray \"%s\" successfully renamed to \"%s\"!\n",current_file_name,new_file_name);
                }       
                break;
            }
            case 5:             // DELETE AN EXISTING ARRAY
            {
                FILE *file_1;
                char name_of_file_to_delete[FILENAME_MAX+1];

                printf("\n~ Insert the name of the array you want to delete ~(Press 0 to exit this operation): ");
                ask_for_name_of_array_to_delete:                                    // 'INSERT NAME' LOOP
                scanf(" "); 
                fgets(name_of_file_to_delete, FILENAME_MAX+1,stdin);
                name_of_file_to_delete[strlen(name_of_file_to_delete)-1] = '\0';    // mhdenismos xarakthra '\n'
                
                // ESCAPING IF 0 IS GIVEN -> LUNEI KAMPOSA PROBLHMATAKIA
                if(strcspn("0",name_of_file_to_delete)==0 && strlen(name_of_file_to_delete)==1)
                {
                    goto asking_user;
                }
                
                strcat(name_of_file_to_delete,".txt");                                          // attach sto filename to ".txt" file extension

                // CHECKING EXISTANCE OF AN ARRAY WITH NAME "array_name.txt" 
                file_1=fopen(name_of_file_to_delete,"r");
                if(file_1==NULL)
                {
                    fclose(file_1);                                                 // kleinei thn 'pseudo-anagnwsh' tou arxeiou 
                    printf("Array with name \"%s\" does not exist!\n"
                        "\n~ Insert again the name of the array you want delete ~(Press 0 to exit this operation): ",name_of_file_to_delete);
                    goto ask_for_name_of_array_to_delete;
                } // else -> FILE "name_of_file_to_delete" EXISTS
                fclose(file_1);   
                
                if (remove(name_of_file_to_delete))
                    printf("Array with name \"%s\" could not be deleted!\n",name_of_file_to_delete);
                else
                    printf("Array with name \"%s\" successfully deleted!\n",name_of_file_to_delete);

                break; // exiting switch(choice_1)
            }
            /*case 6:             // vectors  --> WORKS BUT DOES ACTUALLY NOTHING --> IS THE PLACE WHERE ALL THE FUNCTIONS FOR VECTORS OPERATE -> 'what could have been' 
            {
                int choice_arr_1;
                printf("\n\tMAIN VECTORS MENU\n"
                        "Insert ' 1' to add 2 vectors\n"
                        "Insert ' 2' to subtract 2 vectors\n"
                        "Insert ' 3' to multiply a vector with a real number\n"
                        "Insert ' 4' to calculate the dot product of 2 vectors\n"
                        "Insert ' 5' to calculate the X product of 2 vectors\n"
                        "Insert ' 6' to calculate magnitude of a vector\n"
                        "Insert ' 7' to calculate the angle between 2 vectors\n"
                        "Insert ' 8' to take a look at a vector/array\n"
                        "Insert ' 9' to take a look at ALL the available vectors/arrays\n"
                        "Insert '10' to go back to the VECTORS main menu\n"
                        "Insert '11' to END operations with vectors and go BACK at the MAIN MENU\n" );

                asking_user_in_vectors_operations:  // MAIN 'VECTOR CHOICE' LOOP
                choice_arr_1=0;
                printf("\n~ (VECTORS) What do you want to do? ~(Press 10 for VECTORS main menu): ");
                scanf("%d",&choice_arr_1);
                fflush(stdin);
                switch(choice_arr_1)
                {
                    case 1:
                    {
                        //EDW THA EMPAINE TO FUNCTION CALL
                        print_no_time;
                        goto asking_user_in_vectors_operations;
                    }
                    case 2:
                    {
                        //EDW THA EMPAINE TO FUNCTION CALL
                        print_no_time;
                        goto asking_user_in_vectors_operations;
                    }
                    case 3:
                    {
                        //EDW THA EMPAINE TO FUNCTION CALL
                        print_no_time;
                        goto asking_user_in_vectors_operations;
                    }
                    case 4:
                    {
                        //EDW THA EMPAINE TO FUNCTION CALL
                        print_no_time;
                        goto asking_user_in_vectors_operations;
                    }
                    case 5:
                    {
                        //EDW THA EMPAINE TO FUNCTION CALL
                        print_no_time;
                        goto asking_user_in_vectors_operations;
                    }
                    case 6:
                    {
                        //EDW THA EMPAINE TO FUNCTION CALL
                        print_no_time;
                        goto asking_user_in_vectors_operations;
                    }
                    case 7:
                    {
                        //EDW THA EMPAINE TO FUNCTION CALL
                        print_no_time;
                        goto asking_user_in_vectors_operations;
                    }
                    case 8:         // SHOW A VECTOR/ARRAY                  
                    {
                        FILE *file_1;
                        int rows,cols;
                        char array_name[FILENAME_MAX+1];
                        double **array;                                 // pointer pou tha deijei ston array mesw ths sunarthshs... meta tha ton kanoume free();

                        load_given_array_VECTORS:
                        for(int a=0;a<FILENAME_MAX+1;a++)               // grhgoros mhdenismos twn stoixeiwn ths sustoixias array_name, to not cause any trouble later on
                            array_name[a]=0;
                        printf("\n~ Insert the name of the vector/array you want to see ~(Press 0 to exit this operation): ");
                        scanf(" ");                                     // antimetwpish sfalmatwn eisagwghs
                        fgets(array_name,FILENAME_MAX+1,stdin);
                        array_name[strlen(array_name)-1]='\0';

                        // ESCAPING IF 0 IS GIVEN -> LUNEI KAMPOSA PROBLHMATAKIA
                        if(strcspn("0",array_name)==0 && strlen(array_name)==1)
                        {
                            goto asking_user_in_vectors_operations;
                        }

                        strcat(array_name,".txt");                      // attach sto filename to ".txt" file extension

                        file_1=fopen(array_name,"r");                   // diabazei to arxeio "array_name"
                        if(file_1==NULL)
                        {
                            printf("Could not find vector/array with name \"%s\"!\n",array_name);
                            goto load_given_array_VECTORS;
                        }

                        fscanf(file_1,"%d %d",&rows,&cols);             // diabazei apo to .txt tis diastaseis tou pinaka. (tis opoies exw dwsei apo thn init_array_to_file ALREADY)

                        create_array(&array,rows,cols);                 // DHMIOURGEI ARRAY ME DYNAMIC MEMORY ALLOCATION
                        pass_file_to_array(file_1,array,rows,cols);     // DIABAZEI TIS TIMES APO TO .txt FILE KAI TIS PERNAEI STON ARRAY
                        printf("\n***\t%s\t***",array_name);            // morfopoihsh stdout
                        print_array(array,rows,cols);                   // PRINTAREI TON ARRAY
                        destroy_array(array,rows,cols);                 // ELEUTHERWNEI THN MNHMH POU KATALAMBANE O ARRAY

                        // CLOSING FILE
                        fclose(file_1);
                        
                        goto asking_user_in_vectors_operations;         // exiting switch(choice_arr_1);
                    }
                    case 9:         // SHOWING THE AVAILABLE VECTORS/ARRAYS 
                    {
                        printf( "\nThe available vectors/arrays are:\n");
                        printf("--------------------\n");
                        txt_files_from_folder_printer();
                        printf("--------------------\n"); // diorthwsi sthn stdout, morfopoihsh ejodou
                        goto asking_user_in_vectors_operations; // exiting switch(choice_arr_1);
                    }
                    case 10:        // GOING BACK TO THE VECTORS MENU      
                    {
                        printf( "\n----------------------------------------\n"
                                "Insert ' 1' to add 2 vectors\n" /// CHECKED with the printing patch
                                "Insert ' 2' to subtract 2 vectors\n"
                                "Insert ' 3' to multiply a vector with a real number\n"
                                "Insert ' 4' to calculate the dot product of 2 vectors\n"
                                "Insert ' 5' to calculate the X product of 2 vectors\n"
                                "Insert ' 6' to calculate magnitude of a vector\n"
                                "Insert ' 7' to calculate the angle between 2 vectors\n"
                                "Insert ' 8' to take a look at a vector/array\n"
                                "Insert ' 9' to take a look at ALL the available vectors/arrays\n"
                                "Insert '10' to go back to the VECTORS main menu\n"
                                "Insert '11' to END operations with vectors and go BACK at the MAIN MENU\n"
                                "----------------------------------------\n");
                        goto asking_user_in_vectors_operations;
                    }
                    case 11:        // GOING BACK TO THE MAIN MENU         
                    {
                        // IT WILL JUST BREAK AND GO BACK TO THE MAIN MENU
                        break;
                    }
                    default:        // LOOP -> INSERT AGAIN                 
                    {
                        printf("Your action must be a number between 1 and 11, according to the VECTORS menu! ~(Press 10 to have a look)\n");
                        break; // exiting switch(choice_arr_1);
                    }
                }
                if(choice_arr_1<=0 || choice_arr_1>=12) // NO code in 1,2,3,4,5,6,7 choices
                {
                    goto asking_user_in_vectors_operations; // GOES UP, TO THE MAIN 'VECTOR CHOICE' LOOP
                }
                break; // exiting switch(choice_arr_1);
            }*/
            case 6:             // ARRAYS   --> WORKS
            {
                int choice_arr_1;
                printf( "\n\tMAIN ARRAYS MENU\n"
                        "Insert ' 1' to add 2 arrays\n" 
                        "Insert ' 2' to subtract 2 arrays\n"
                        "Insert ' 3' to multiply an array with a real number\n"
                        "Insert ' 4' to multiply an array with another array\n"
                        "Insert ' 5' to calculate the transpose of an array\n"
                        "Insert ' 6' to eliminate a row from the array\n"
                        "Insert ' 7' to eliminate a column from the array\n"
                        "Insert ' 8' to calculate the Determinant of an array\n"
                        "Insert ' 9' to inverse an array\n"
                        "Insert '10' to take a look at an array/vector\n"
                        "Insert '11' to take a look at ALL the available arrays/vectors\n"
                        "Insert '12' to go back to the ARRAYS main menu\n"
                        "Insert '13' to END operations with arrays and go BACK at the MAIN MENU\n");

                asking_user_in_arrays_operations:               // MAIN 'CHOICE ARRAY' LOOP
                choice_arr_1=0;
                printf("\n~ (ARRAYS) What do you want to do? ~(Press 12 for ARRAYS main menu): ");
                scanf("%d",&choice_arr_1);
                fflush(stdin);
                switch(choice_arr_1)                            // ***_____ARRAYS CHOICES_____***
                {
                    case 1:         // ADD 2 ARRAYS                         
                    {
                        array_sum();
                        goto asking_user_in_arrays_operations;
                    }
                    case 2:         // SUBTRACT 2 ARRAYS                    
                    {
                        array_sub();
                        goto asking_user_in_arrays_operations;
                    }
                    case 3:         // PRODUCT OF ARRAY AND REAL NUMBER     
                    {
                        array_num_product();
                        goto asking_user_in_arrays_operations;
                    }
                    case 4:         // PRODUCT OF 2 ARRAYS                 
                    {
                        array_array_prod();
                        goto asking_user_in_arrays_operations;
                    }
                    case 5:         // TRANSPOSE OF ARRAY                   
                    {
                        array_transpose();
                        goto asking_user_in_arrays_operations;
                    }
                    case 6:         // ROW ELIMINATION FROM ARRAY           
                    {
                        from_array_row_elim();
                        goto asking_user_in_arrays_operations;
                    }
                    case 7:         // COLUMN ELIMINATION FROM ARRAY       
                    {
                        from_array_column_elim();
                        goto asking_user_in_arrays_operations;
                    }
                    case 8:         // CALCULATES DETERMINANT OF ARRAY     
                    {
                        determinant_calculator();
                        goto asking_user_in_arrays_operations;
                    }
                    case 9:         // INVERSES AN ARRAY                    
                    {
                        array_inverse();
                        goto asking_user_in_arrays_operations;
                    }
                    case 10:        // ASKING AND SHOWING THE GIVEN ARRAY  
                    {
                        FILE *file_1;
                        int rows,cols;
                        char array_name[FILENAME_MAX+1];
                        double **array;                                 // deiktakos pou tha deijei ston array mesw ths sunarthshs... meta tha ton kanoume free();

                        load_given_array_ARRAYS:                        // 'INSERT NAME' LOOP

                        for(int a=0;a<FILENAME_MAX+1;a++)               // grhgoros mhdenismos twn stoixeiwn ths sustoixias array_name, to not cause any trouble later on
                            array_name[a]=0;

                        printf("\n~ Insert the name of the array/vector you want to see ~(Press 0 to exit this operation): ");
                        scanf(" ");                                     // antimetwpish sfalmatwn eisagwghs
                        fgets(array_name,FILENAME_MAX+1,stdin);
                        array_name[strlen(array_name)-1]='\0';

                        // ESCAPING IF 0 IS GIVEN -> LUNEI KAMPOSA PROBLHMATAKIA
                        if(strcspn("0",array_name)==0 && strlen(array_name)==1)
                        {
                            goto asking_user_in_arrays_operations;
                        }

                        strcat(array_name,".txt");                      // attach sto filename to ".txt" file extension

                        file_1=fopen(array_name,"r");                   // diabazei to arxeio "array_name"
                        if(file_1==NULL)
                        {
                            printf("Could not find array/vector with name \"%s\"!\n",array_name);
                            goto load_given_array_ARRAYS;
                        }

                        fscanf(file_1,"%d %d",&rows,&cols);             // diabazei apo to .txt tis diastaseis tou pinaka. (tis opoies exw dwsei apo thn init_array_to_file ALREADY)

                        create_array(&array,rows,cols);                 // DHMIOURGEI ARRAY ME DYNAMIC MEMORY ALLOCATION
                        pass_file_to_array(file_1,array,rows,cols);     // DIABAZEI TIS TIMES APO TO .txt FILE KAI TIS PERNAEI STON ARRAY
                        printf("\n***\t%s\t***",array_name);            // morfopoihsh stdout
                        print_array(array,rows,cols);                   // PRINTAREI TON ARRAY
                        destroy_array(array,rows,cols);                 // ELEUTHERWNEI THN MNHMH POU KATALAMBANE O ARRAY

                        // CLOSING FILE
                        fclose(file_1);
                        
                        goto asking_user_in_arrays_operations;          // exiting switch(choice_arr_1);
                    }
                    case 11:        // SHOWING AVAILABLE ARRAYS             
                    {
                        printf( "\nThe available arrays/vectors are:\n");
                        printf("--------------------\n");
                        txt_files_from_folder_printer();
                        printf("--------------------\n");       // diorthwsi sthn stdout, morfopoihsh ejodou
                        goto asking_user_in_arrays_operations;  // exiting switch(choice_arr_1);
                    }
                    case 12:        // SHOWING THE ARRAYS MAIN MENU         
                    {
                        printf("\n----------------------------------------\n" 
                                "Insert ' 1' to add 2 arrays\n"
                                "Insert ' 2' to subtract 2 arrays\n"
                                "Insert ' 3' to multiply an array with a real number\n"
                                "Insert ' 4' to multiply an array with another array\n"
                                "Insert ' 5' to calculate the transpose of an array\n"
                                "Insert ' 6' to eliminate a row from the array\n"
                                "Insert ' 7' to eliminate a column from the array\n"
                                "Insert ' 8' to calculate the Determinant of an array\n"
                                "Insert ' 9' to inverse an array\n"
                                "Insert '10' to take a look at an array\n"
                                "Insert '11' to take a look at ALL the available arrays\n"
                                "Insert '12' to go back to the ARRAYS main menu\n"
                                "Insert '13' to END operations with arrays and go BACK at the MAIN MENU\n"
                                "----------------------------------------\n");
                        goto asking_user_in_arrays_operations;
                    }
                    case 13:        // GOING BACK TO THE MAIN MENU          
                    {
                        // IT WILL JUST BREAK AND GO BACK TO THE MAIN MENU
                        break;
                    }
                    default:        // LOOP -> INSERT AGAIN             
                    {
                        printf("Your action must be a number between 1 and 13, according to the ARRAYS menu! ~(Press 12 to have a look)\n");
                        break; // exiting switch(choice_arr_1);
                    }
                }
                if(choice_arr_1<=0 || choice_arr_1>=14)          
                {
                    goto asking_user_in_arrays_operations;
                }
                break; // exiting switch(choice_arr_1);
            }
            case 7:             // BACK TO MAIN MENU              
            {
                printf( "\n-----------------------------\n"
                        "     ***  MAIN MENU  ***\n"  
                        "| 1 | Create an array\n"
                        "| 2 | Load an array\n"
                        "| 3 | See the available arrays\n"
                        "| 4 | Rename an array\n"
                        "| 5 | Delete an array\n"
                        "| 6 | Use Arrays\n"
                        "| 7 | BACK TO MAIN MENU\n"
                        "| 8 | END PROGRAM\n"
                        "| 9 | CREDIT SCENES\n"
                        "-----------------------------\n");
                break; // exiting switch(choice_1);
            }
            case 8:             // TERMINATE PROGRAM           
            {
                goto terminator; // no need for a break
            }
            case 9:             // CREDIT SCENES
            {
                printf("\nit was the...\n");
                printf( "\t\t\t\t\t ____________________________________\n"
                        "\t\t\t\t\t|                                    |                                        ______________ \n"
                        "\t\t\t\t\t|            2022 PROJECT            |                                       |              |\n"
                        "\t\t\t\t\t|      LINEAR ALGEBRA OPERATIONS     |                                       |   Ntoylker   |\n"
                        "\t\t\t\t\t|  DEVELOPER:   NIKOLAOS TOULKERIDHS |                                       |______________|\n"
                        "\t\t\t\t\t|____________________________________|\n"
                        "\n\nThe following links are YouTube videos that helped:\n"
                        "\thttps://www.youtube.com/watch?v=xDVC3wKjS64&list=PLcFhVT75zrZjWVlPwj-nthLFz775VxR4i&index=4\n"
                        "\thttps://www.youtube.com/watch?v=K_GXeTL5cbE&list=PLcFhVT75zrZjWVlPwj-nthLFz775VxR4i&index=5&t=509s\n"
                        "\thttps://www.youtube.com/watch?v=eOPJ8vym_PE&list=PLcFhVT75zrZjWVlPwj-nthLFz775VxR4i&index=6\n"
                        "\thttps://www.youtube.com/watch?v=189GZ_nRqAk\n"
                        "\thttps://www.youtube.com/watch?v=u1e0gLoz1SU&t=383s\n"
                        "And of course:\n"
                        "\thttps://stackoverflow.com\n"
                        "\thttps://www.geeksforgeeks.org\n"
                        "\thttps://www.javatpoint.com\n");

                goto terminator; // no need for a break
            }
            default:            // DEFENSIVE LOOP -> INSERT AGAIN         
            {
                printf("Your action must be a number between 1 and 9, according to the menu! ~(Press 7 to have a look)\n");
                break; // exiting switch(choice_1); while(1) -> MAIN 'CHOICE' LOOP
            }
        }
    }
    }// END OF COMBAT SCENE
    
    
    //   ***    TERMINATING     ***
    terminator:
    {
    printf("\nYou can find your arrays in the folder where PROJECT.exe exists!\n");
    printf("\nTERMINATED\n");
    }
    
    return 0;
}
