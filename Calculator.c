
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*--------------------------------------------------------------------------------*/

typedef struct{ /* Vectors */
    int vector[3];
    int a,b,c;
    char opt,check;
}variable;

typedef struct complex{ /* Complex */
    int r;
    int im;
}cmp;

/*--------------------------------------------------------------------------------*/

//global variables
int r,im;
int flag=0,m,n;
char upper[30] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char lower[30] = "abcdefghijklmnopqrstuvwxyz";
cmp c;
FILE *filep;
char text[100],key[50],encrypt[100],arr[100];
char *txt;

/*-------------------------------------------------------------------------------------*/

//Functions
void basic();
void complex();
void vectors();
void determinant();
void matrix();
void fraction();
void crypto();
void series();
void trigo();
void save();
char* encipher(char*, char*, int );

/*------------------------------------------------------------------------------------------------------------------*/

int main(){
	printf("WELCOME!!!");
	int opt;
	char ch;
	do{
        // system("clear");
		printf("\n1.Basic\n2.Complex\n3.Vectors\n4.Determinant\n5.Matrix\n6.Fractions\n7.Cryptography\n8.Series\n0.Exit\nEnter option: ");
		scanf("%d",&opt);
		switch(opt){
			case 1:
				basic();
				break;
			case 2:
				complex();
				break;
			case 3:
				vectors();
				break;
			case 4:
				determinant();
				break;
			case 5:
				matrix();
				break;
			case 6:
				fraction();
				break;
			case 7:
				crypto();
				break;
            case 8:
                series();
                break;
            case 9:
                trigo();
                break;
			case 0:
				continue;
			default:
				printf("Invalid Input!\n");
		}
	}while(opt != 0);
	printf("\nTHANKYOU!!!");
	return 0;
}

/*-----------------------------------------------------------------------------------------------------------------*/

void crypto(){ 
    void rotate_rot13(char []);
    void rotate_rot47(char []);
    void newcrypto();
    void vigenere();
    int opt_c;
    printf("1.ROT13\n2.ROT47\n3.Vigenere Cipher\n4.Codeword Cipher\nEnter option: ");
    scanf("%d",&opt_c);
    switch(opt_c){
        case 1:
            printf("Enter text to ROT13: ");
            scanf("%s",text);
            rotate_rot13(text);
            break;
        case 2:
            printf("Enter text to ROT47: ");
            scanf("%s",text);
            rotate_rot47(text);
            break;
        case 3:
            vigenere();
            break;
        case 4:
            newcrypto();
            break;
        default:
            printf("Invalid Input!!");
    }
}

/* Cryptography functions */

void rotate_rot13(char text[]){
    for (int i=0;text[i] != '\0';i++){
        if (isupper(text[i])){
            int p = text[i] - 65;
            text[i] = upper[(p+13)%26];
        }
        else if (islower(text[i])){
            int p = text[i] - 97;
            text[i] = lower[(p+13)%26];
        }
    }
    printf("%s\n",text);
    save(1);
}

void rotate_rot47(char text[]){
    for (int i=0;text[i] != '\0';i++){
        if (text[i] >= 33 && text[i]<= 126)
            text[i] = 33+((text[i] + 14)%94);
    }
    printf("%s\n",text);
    save(2);
}

char* encipher(char *src, char *key, int is_encode) {
    int i, klen, slen;
    char *dest;
 
    dest = strdup(src);
 
    /* strip out non-letters */
    for (i = 0, slen = 0; dest[slen] != '\0'; slen++)
        if (isupper(dest[slen]))
            dest[i++] = dest[slen];
 
    dest[i] = '\0';
 
    klen = strlen(key);
    for (i = 0; i < slen; i++) {
        if (!isupper(dest[i]))
            continue;
        dest[i] = 'A' + (is_encode ? dest[i] - 'A' + key[i % klen] - 'A'
                : dest[i] - key[i % klen] + 26) % 26;
    }
 
    return dest;
}
 
void vigenere(){
    int v_opt;
    char *str;
    str = &text[100];
    printf("1.Encrypt\n2.Decyrpt\nEnter option: ");
    scanf("%d",&v_opt);
    if (v_opt == 1){
        printf("Enter Plaintext: ");
        scanf(" %[^\n]s",str);
        printf("Enter key: ");
        scanf(" %s",key);
        txt = encipher(str, key, 1);
        printf("Ciphered: %s\n", txt);
    }
    else{
        printf("Enter Ciphertext: ");
        scanf(" %[^\n]s",str);
        printf("Enter key: ");
        scanf(" %s",key);
        txt = encipher(str, key, 0);
        printf("Deciphered: %s\n", txt);
    }
    save(3);
}


void save(int opt){
    char ch;
    printf("Do you want to save the cipher text?(y/n): ");
    scanf(" %c",&ch);
    if (ch == 'y' || ch == 'Y'){
        filep = fopen("crypto.txt","a");
        switch(opt){
            case 1:
                fputs("ROT13 : ",filep);
                fputs(text,filep);
                break;
            case 2:
                fputs("ROT47 : ",filep);
                fputs(text,filep);
                break;
            case 3:
                fputs("Vigenere KEY: ",filep);
                fputs(key,filep);
                fputs("\nVigenere TEXT: ",filep);
                fputs(txt,filep);
                break;
            case 4:
                fputs("Codeword KEY: ",filep);
                fputs(arr,filep);
                fputs("\n",filep);
                fputs("Encrypted: ",filep);
                fputs(encrypt,filep);
                break;
        }
        fputs("\n",filep);
    }
    fclose(filep);
}

void newcrypto(){
    int s=0,n=1,i;
    printf("enter the code word (length less than 100) \n");
    scanf(" %s",arr);
    for(i=0;arr[i]!='\0';i++){
        s=(arr[i])+s;
        n=n+1;
    }
    s=s/n;s=s/10;
    printf("enter the message in caps \n");
    scanf(" %s",text);
    for (int i=0;text[i] != '\0';i++){
        if (text[i] >= 33 && text[i]<= 126)
                text[i] = text[i] +s;
    }
    strcpy(encrypt,text);
    printf("the encoded message is %s \n ",text);
    for (int i=0;text[i] != '\0';i++){
        if (text[i] >= 33 && text[i]<= 126)
                text[i] = text[i] - s;
    }
    printf("the decoded message is %s \n ",text);
    save(4);
}

/*--------------------------------------------------------------------------------------*/


void complex(){
    void complex_add();
    void complex_sub();
    void complex_mul();
    void complex_di();
    void complex_display();
    void complex_euler();
    int flag=0;
    printf(" n:to stop doing operations and turn off calculator \n"
        "+:to perform addition for  required complex numbers \n"
        "-:to perform subtraction for required complex numbers \n"
        "*:to perform multiplication for 2 complex numbers \n"
        "%%:to perform division for 2 complex numbers \n");
      

    char p;
    scanf (" %c", &p);
    while (p != 'n'){
    if (p == '+')
        complex_add();
    if (p == '-')
        complex_sub();
    if (p == '*')
        complex_mul();
    if (p == '%')
        complex_di();
    if(p=='d')
        complex_display();
    if(p=='e')
        complex_euler();
    printf(" n:to stop doing operations and turn off calculator \n"
                "+:to perform addition for  required complex numbers \n"
                "-:to perform subtraction for required complex numbers \n"
                "*:to perform multiplication for 2 complex numbers \n"
                "%%:to perform division for 2 complex numbers\n"
                "d:display the current result \n"
                "e:to convert current result to euler form and display the euler form \n"
                "a:to store the current result and use it with other functions of the calculator \n ");
    scanf(" %c", &p);
    }
    printf("Thank you have a good day");
}

void complex_add(){
    printf("enter the number of times to perform addition");
    int m, i, l;
    scanf("%d", &m);
    if (flag == 0){
        c.r = c.im = 0;
        flag = 1;
    }
    for (i = 0; i < m; i++){
        printf("enter the real part of complex number %d", i+1);
        scanf("%d", &l);
        c.r = c.r + l;
        printf("enter the imaginary part of complex number %d", i+1);
        scanf("%d", &l);
        c.im = c.im + l;
    }
}

void complex_sub(){
    printf("enter the number of times to perform subtraction");
    int m, i, l;
    scanf("%d", &m);
    if (flag == 0){
        c.r =c.im = 0;
        flag = 1;
    }
    for (i = 0; i < m; i++){
        printf("enter the real part of complex number %d", i+1);
        scanf("%d", &l);
        c.r =c.r - l;
        printf("enter the imaginary part of complex number %d", i+1);
        scanf("%d", &l);
        c.im = c.im - l;
    }
}

void complex_mul(){//multiplication and division of a complex number can be done with only one complex number at a time
     // the user can repeat multiplication operation if he/she wishes to redo multiplcation with the existing result stored in global 
     //structured variable c.r and c.im
    int m, i, l, j, k, v;
    if (flag == 0){
        printf("enter the real part of complex number 1");
        scanf("%d", &c.r);
        printf("enter the imaginary part of complex number 1");
        scanf("%d", &c.im);
        printf("enter the real part of complex number 2");
        scanf("%d", &l);
        printf("enter the imaginary part of complex number 2");
        scanf("%d", &v);
        c.im = (l * c.im) + (v * c.r);
        c.r = (l * c.r) - (c.im * v);
        flag = 1;
    }
    else{
        j = c.r;
        k = c.im;
        printf("enter the real part of complex number ");
        scanf("%d", &l);
        printf("enter the imaginary part of complex number ");
        scanf("%d", &v);
        c.im = (l * k) + (v * j);
        c.r = (l * j) - (k * v);
    }
}

void complex_di(){
    int m, i, l, j, k, v, q,flag=0; 
    if (flag == 0)
    {
        printf("enter the real part of complex number 1");
        scanf("%d", &c.r);
        printf("enter the imaginary part of complex number 1");
        scanf("%d", &c.im);
        printf("enter the real part of complex number 2");
        scanf("%d", &l);
        printf("enter the imaginary part of complex number 2");
        scanf("%d", &v);
        c.im=(l*c.im)-(v*c.r);
        c.r=(l*c.r)+(c.im*v);
        q = (l * l) + (v * v);
        c.im = c.im / q;
        c.r = c.r / q;
        flag = 1;
    }
    else{
        j = c.r;
        k = c.im;
        printf("enter the real part of complex number ");
        scanf("%d", &l);
        printf("enter the imaginary part of complex number");
        scanf("%d", &v);
        c.im = (l * k) - (v * j);
        c.r = (l * j) + (k * v);
        q = (l * l) + (v * v);
        c.im = c.im / q;
        c.r = c.r / q;
    }
}
void complex_display(){
    printf(" \n Result:%d+i%d \n",c.r ,c.im);
}
void complex_euler(){
    int e,o;
    e=(c.r*c.r)+(c.im*c.im);
    printf("Eulers form :%f^i%f",sqrt(e),atan(c.im/c.r));
}


/*------------------------------------------------------------------------------------------------------------------*/

void vectors(){ 
    void vector_add();
    void vector_sub();
    void vector_dot();
    void vector_cross();
    variable mn;
    do{
        printf("Addition (+)\nSubtraction (-)\nDotproduct (.)\nCrossproduct (x)\nEnter Symbol: ");
        scanf(" %c",&mn.opt);
        switch (mn.opt){
            case '+':
                vector_add();
                break;
            case '-':
                vector_sub();
                break;
            case '.':
                vector_dot();
                break;
            case 'x':
                vector_cross();
                break;
            default:
                printf("Invalid Input!\n");
        }
        printf("\n\nCalculate vector again (y/n): ");
        scanf(" %c",&mn.check);
    }while(mn.check == 'Y' || mn.check == 'y');
}

/* vector functions */

void vector_add(){
    
    variable add;
    char check;
    do{
        printf("\nEnter vector: ");
        scanf("%di + %dj + %dk",&add.a,&add.b,&add.c);
        add.vector[0] += add.a;add.vector[1] += add.b;add.vector[2] += add.c;
        printf("Add another vector (y/n): ");
        scanf(" %c",&check);
    }while(check == 'y' || check == 'Y');
    printf("\nVector sum: %di + %dj + %dk",add.vector[0],add.vector[1],add.vector[2]);
}

void vector_sub(){
    
    variable sub;
    printf("\nEnter vector 1: ");
    scanf("%di + %dj + %dk",&sub.a,&sub.b,&sub.c);
    sub.vector[0] = sub.a;sub.vector[1] = sub.b;sub.vector[2] = sub.c;
    printf("Enter vector 2: ");
    scanf("%di + %dj + %dk",&sub.a,&sub.b,&sub.c);
    sub.vector[0] += (-1*sub.a);sub.vector[1] += (-1*sub.b);sub.vector[2] += (-1*sub.c);
    printf("Vector Difference: %di + %dj + %dk",sub.vector[0],sub.vector[1],sub.vector[2]);
}

void vector_dot(){
    
    variable dot;
    printf("\nEnter vector 1: ");
    scanf("%di + %dj + %dk",&dot.a,&dot.b,&dot.c);
    dot.vector[0] = dot.a;dot.vector[1] = dot.b;dot.vector[2] = dot.c;
    printf("Enter vector 2: ");
    scanf("%di + %dj + %dk",&dot.a,&dot.b,&dot.c);
    dot.vector[0] *= dot.a;dot.vector[1] *= dot.b;dot.vector[2] *= dot.c;
    printf("Vector DotProduct: %di + %dj + %dk",dot.vector[0],dot.vector[1],dot.vector[2]);
}

void vector_cross(){
    
    int a1,a2,a3,b1,b2,b3;
    variable cross;
    printf("\nEnter vector 1: ");
    scanf("%di + %dj + %dk",&a1,&a2,&a3);
    printf("Enter vector 2: ");
    scanf("%di + %dj + %dk",&b1,&b2,&b3);
    cross.vector[0] = (a2*b3 - a3*b2);
    cross.vector[1] = (a3*b1 - a1*b3);
    cross.vector[2] = (a1*b2 - a2*b1);
    printf("Vector CrossProduct: %di + %dj + %dk",cross.vector[0],cross.vector[1],cross.vector[2]);
}

/*------------------------------------------------------------------------------------------------------------------*/

void determinant(){ 
    
    int row,column,m,n;
    int det(int matrix[m][n]);
    printf("Enter size: ");
    scanf("%d",&n);
    m=n;
    int A[m][n];
    printf("Enter matrix elements:\n");
    for(row = 0; row < m; row++){
        for(column = 0; column < n; column++)
            scanf("%d",&A[row][column]);
    }
    printf("determinant: %d",det(A));

}

int det(int matrix[m][n]){ 
    int row_size = m;
    int column_size = n;

    if (row_size == 1)
        return (matrix[0][0]);
    else if (row_size == 2)
        return (matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1]);

    else {
        int minor[row_size-1][column_size-1];
        int row_minor, column_minor,frci,sum=0;
        register int row,column;
        for( frci= 0; frci < row_size;frci++) {
            row_minor = 0;
            for(row = 1; row < row_size; row++) {
                column_minor = 0;
                for(column = 0; column < column_size; column++) {
                    if (column == frci)
                        continue;
                    else
                        minor[row_minor][column_minor] = matrix[row][column];
                    column_minor++;
                }
                row_minor++;
            }
            m = row_minor;
            n = column_minor;
            if (frci % 2 == 0)
                sum += matrix[0][frci] * det(minor);
            else
                sum -= matrix[0][frci] * det(minor);
        }
        return sum;
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

void series(){
    
    void series_ap();
    void series_gp();
    void series_hp();
    
    char c;
    printf("To solve problems related to ap press a \n ");
    printf("To solve problems related to gp press g \n");
    printf("To solve problems related to hp press h \n");
    scanf(" %c", &c);
    if(c == 'a')
        series_ap();
    else if(c == 'g')
        series_gp();
    else if(c=='h')
        series_hp();
    else
        printf ("you have entered wrong option \n");
}

void series_ap(){
    
    printf("enter the first term & common difference \n");
    int a, d, n, r;
    scanf("%d \n %d", &a, &d);
    printf("to find the nth term press 1 \n ");
    printf("to find the sum of n terms press 2 \n");
    scanf("%d ", &r);
    if (r == 1){
        printf("enter the value of n \n");
        scanf("%d", &n);
        printf("the value of nth term is %d", (a + ((n - 1) * d)));
    }
    else if(r == 2){
        printf("enter the value of n");
        scanf("%d", &n);
        printf("the value of nth term is %d", ((2 * a) + ((n - 1) * d)));
    }
    else
        printf("incorrect choice ");
}

void series_gp(){
    
    printf("enter the first term & common ratio \n");
    int a, d, n, r;
    scanf("%d \n %d", &a, &d);
    printf("to find the nth term press 1 \n ");
    printf("to find the sum of n terms press 2 \n");
    scanf("%d ", &r);
    if (r == 1){
        printf("enter the value of n \n ");
        scanf("%d", &n);
        printf("the value of nth term is %f \n", (a * (pow (r, n - 1))));
    }
    else if(r == 2){
        printf("enter the value of n \n ");
        scanf("%d", &n);
        printf("the value of nth term is %f \n",(a * (pow (r, n) - 1)) / (r - 1));
    }
    else
        printf("incorrect choice \n ");
}

void series_hp(){
    
    printf("enter the first term & common difference \n");
    float a, d, n, r;
    scanf("%f \n %f", &a, &d);
    printf("to find the nth term press 1 \n ");
    scanf("%f ", &r);
    printf("enter the value of n \n ");
    scanf("%f", &n);
    printf("the value of nth term is %f \n", (1 / (a + ((n - 1) * d))));
}

/*----------------------------------------------------------------------------------*/


void trigo(){
    
    void trignometric();
    void invtrignometric();
    printf("To perform trignometric operations press 1\n");int a;
    printf("To perfrom inverse tringnometric functions press 2 \n");
    scanf("%d",&a);
    if(a==1)
        trignometric();
    else if(a==2)
        invtrignometric();
    else
        printf("wrong option entered");
}
void trignometric(){
    
    int a,x;
    printf("to enter sin function press 1\n");
    printf("to enter cos function press 2\n");
    printf("to perform tan function press 3\n");
    scanf("%d",&a);
    if(a==1){
        printf("enter the value of theta");scanf("%d",&x);
        printf("%f",sin(x));
    }
        if(a==2){
        printf("enter the value of theta");scanf("%d",&x);
        printf("%f", cos(x));
    }    
    if(a==3){
        printf("enter the value of theta");scanf("%d",&x);
        printf("%f",tan(x));
    }
}
void invtrignometric(){
    
    int a,x;
    printf("to enter asin function press 1 \n");
    printf("to enter acos function press 2\n");
    printf("to perform atan function press 3\n");
    scanf("%d",&a);
    if(a==1){
        printf("enter the value of x\n");scanf("%d",&x);
        printf("%f",asin(x));
    }
    if(a==2){
        printf("enter the value of x");scanf("%d",&x);
        printf("%f", acos(x));
    }
    if(a==3){
        printf("enter the value of x");scanf("%d",&x);
        printf("%f",atan(x));
    }
}

/*-----------------------------------------------------------------------------------------------------------------*/

void fraction(){ 

	void frac_add(int,int,int,int);
	void frac_sub(int,int,int,int);
	void frac_mul(int,int,int,int);
	void frac_div(int,int,int,int);
	int a=1,b=1,c=1,d=1;
	char opt,ch;
	do{
		printf("Enter Fraction 1 in the form p/q: ");
		scanf("%d/%d",&a,&b);
		printf("Enter Fraction 2 in the form p/q: ");
		scanf("%d/%d",&c,&d);
		printf("Addition (+)\nSubtraction (-)\nDivision (/)\nMultiplication (x)\nEnter option: ");
		scanf(" %c",&opt);
		if (opt == '+')
			frac_add(a,b,c,d);
		else if (opt == '-')
			frac_sub(a,b,c,d);
		else if (opt == 'x')
			frac_mul(a,b,c,d);
		else if (opt == '/')
			frac_div(a,b,c,d);
		else
			printf("Invaild Input!");
		printf("\nCalculate again (y/n): ");
		scanf(" %c",&ch);
	}while(ch == 'y' || ch == 'Y');
}

void frac_add(int a,int b,int c,int d){ 
	if (b == d)
		printf("%d/%d",a+c,d);
	else{
		a *= d;c *= b;
		printf("%d/%d",a+c,b*d);
	}
}

void frac_sub(int a,int b,int c,int d){ 
	if (((float)a/b) < ((float)c/d))
		printf("Operation Invalid");
	else{
		if (b == d)
			printf("%d/%d",a-c,d);
		else{
			a *= d;c *= b;
			printf("%d/%d",a-c,b*d);
		}
	}
}

void frac_mul(int a,int b,int c,int d){
	printf("%d/%d",a*c,b*d);
}

void frac_div(int a,int b,int c,int d){ 
	printf("%d/%d",a*d,b*c);
}


/*---------------------------------------------------------------------------------------------------------------*/


void basic(){

	char ch;
	int a,b,opt;
	do{
		printf("1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n5.Power\nEnter option: ");
		scanf("%d",&opt);
		int a,b;
		printf("\nEnter expression: ");
		if (opt == 1){
			scanf("%d + %d",&a,&b);
			printf("%d",a+b);
		}
		else if (opt == 2){
			scanf("%d - %d",&a,&b);
			printf("%d",a-b);
		}
		else if (opt == 3){
			scanf("%d * %d",&a,&b);
			printf("%d",a*b);
		}
		else if (opt == 4){
			scanf("%d/%d",&a,&b);
			printf("%.3f",(float)a/b);
		}
		else if (opt == 5){
			scanf("%d ** %d",&a,&b);
			printf("%d",pow(a,b));
		}
		else
			printf("Invalid Input!");
		printf("\nCalculate again (y/n): ");
		scanf(" %c",&ch);
	}while(ch == 'y' || ch == 'Y');
}

/*-----------------------------------------------------------------------------------------------------------------*/

void transpose(float [][25], float [][25], float);


void matrix(){

    void readMatrix(int array[10][10], int rows, int colums);
    void printMatrix(int array[10][10], int rows, int colums);
    void matrixAddSub(int arrayone[10][10], int arraytwo[10][10], int rows, int colums, int mul);
    void matrixScalarMultiply(int array[10][10], int scalar, int rows, int colums);
    void matrixMultiply(int arrayone[10][10], int arraytwo[10][10], int rowsA, int columsA, int columsB);
    void matrixinverse (int array[10][10],int rows, int colums);
    void cofactor(float [][25], float);
    float determinants(float [][25], float);
    int i, j, k;
    float a[25][25], n, d;
    int matrixA[10][10]; 
    int matrixB[10][10];
    int rowA, colA;
    int rowB, colB;
    int operation;
    char again = 'Y';
    int scalar = 0;
    int add = 1;
    int sub = -1;
    while (again == 'Y'){
        printf("\nOperation Menu\n");
        printf("\t1. to Add\n");
        printf("\t2. to Subtract\n");
        printf("\t3. to Scalar Multiply\n");
        printf("\t4. to Multiply two matrices\n");
        printf("\t5. to find inverse of matrix\n");
        printf("Enter yout choice: ");
        scanf(" %d", &operation);

        switch (operation){
        case 1:
            printf("\nEnter the #rows and #cols for matrix A: ");
            scanf("%d%d", &rowA, &colA);

            printf("Enter the #rows and #cols for matrix B: ");
            scanf("%d%d", &rowB, &colB);

            while ((rowA != rowB) && (colA != colB)){
                printf("\nMatrices must be the same size\n");
                printf("\nEnter the #rows and #cols for matrix A: ");
                scanf("%d%d", &rowA, &colA);

                printf("Enter the #rows and #cols for matrix B: ");
                scanf("%d%d", &rowB, &colB);

            }
            printf("\n\tEnter elements of Matrix A a %d x %d matrix.\n", rowA, colA); 
            readMatrix(matrixA, rowA, colA);
            printf("\n\t\tMatrix A\n\n");
            printMatrix(matrixA, rowA, colA);

            printf("\n\tEnter elements of Matrix B a %d x %d matrix.\n", rowB, colB);
            readMatrix(matrixB, rowB, colB);
            printf("\n\t\tMatrix B\n\n");
            printMatrix(matrixB, rowB, colB);

            printf("\nThe Sum of matrixA + matrixB is : \n");
            matrixAddSub(matrixA, matrixB, rowA, colA, add);
            break;
        case 2:
            printf("\nEnter the #rows and #cols for matrix A: ");
            scanf("%d%d", &rowA, &colA);

            printf("Enter the #rows and #cols for matrix B: ");
            scanf("%d%d", &rowB, &colB);

            while ((rowA != rowB) && (colA != colB)){
                printf("\nMatrices must be the same size\n");
                printf("\nEnter the #rows and #cols for matrix A: ");
                scanf("%d%d", &rowA, &colA);

                printf("Enter the #rows and #cols for matrix B: ");
                scanf("%d%d", &rowB, &colB);
            }

            printf("\n\tEnter elements of Matrix A a %d x %d matrix.\n", rowA, colA);
            readMatrix(matrixA, rowA, colA);
            printf("\n\t\tMatrix A\n\n");
            printMatrix(matrixA, rowA, colA);

            printf("\n\tEnter elements of Matrix B a %d x %d matrix.\n", rowB, colB); 
            readMatrix(matrixB, rowB, colB);
            printf("\n\t\tMatrix B\n\n");
            printMatrix(matrixB, rowB, colB);

            printf("\nThe difference between matrixA - matrixB is : \n");
            matrixAddSub(matrixA, matrixB, rowA, colA, sub);
            break;

        case 3:
            printf("\nEnter the scalar: ");
            scanf("%d", &scalar);
            printf("\nThe scalar is: %d ", scalar);

            printf("\nEnter the #rows and #cols for matrix A: ");
            scanf("%d%d", &rowA, &colA);

            printf("\n\tEnter elements of Matrix A a %d x %d matrix.\n", rowA, colA);
            readMatrix(matrixA, rowA, colA);
            printf("\n\t\tMatrix A\n\n");
            printMatrix(matrixA, rowA, colA);

            printf("\nThe scalar multiplication between matrixA * %d is: \n", scalar);
            matrixScalarMultiply(matrixA, scalar, rowA, colA);
            break;

        case 4:
            
            printf("\nEnter the #rows and #cols for matrix A: ");
            scanf("%d%d", &rowA, &colA);

            printf("Enter the #rows and #cols for matrix B: ");
            scanf("%d%d", &rowB, &colB);

           
            while (colA != rowB)
            {
                printf("\n\nError! column of first matrix not equal to row of second.\n\n");
                printf("\nEnter the #rows and #cols for matrix A: ");
                scanf("%d%d", &rowA, &colA);

                printf("Enter the #rows and #cols for matrix B: ");
                scanf("%d%d", &rowB, &colB);
            }


            printf("\n\tEnter elements of Matrix A a %d x %d matrix.\n", rowA, colA);
            printf("\n\t\tMatrix A\n\n");
            readMatrix(matrixA, rowA, colA);

            
            printf("\n\tEnter elements of Matrix B a %d x %d matrix.\n", rowB, colB);
            readMatrix(matrixB, rowB, colB);
            printf("\n\t\tMatrix A\n\n");
            printMatrix(matrixB, rowB, colB);
            
            matrixMultiply(matrixA, matrixB, rowA, colA, colB);
            break;

            case 5:
             
            printf("Enter the order of the Matrix: ");
  scanf("%f", &n);
  printf("Enter the elements of a matrix: \n");
  for (i = 0;i < n; i++){
     for (j = 0;j < n; j++){
        scanf("%f", &a[i][j]);
        }
    }
    
  d = determinants(a, n);
  if (d == 0)
   printf("Since the determinant is zerp (0), therefor inverse is not possible.");
  else
   cofactor(a, n);
  

        default:
            printf("\nIncorrect option! Please choose a number 1-4.");
            break;
        }

        printf("\n\nDo you want to calculate again? Y/N\n");
        scanf(" %c", &again);
       
    }
    printf("\n\nThankyou\n\n");

}



void readMatrix(int array[10][10], int rows, int colums){
    int i, j;
    for (i = 0; i < rows; i++){
        printf("\t%d entries for row %d: ", colums, i + 1);
        for (j = 0; j < colums; j++){
            scanf("%d", &array[i][j]);
        }
    }

    return;
}

void printMatrix(int array[10][10], int rows, int colums){
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < colums; j++){
            printf("\t%d", array[i][j]);
        }
        printf("\n");
    }
}


void matrixAddSub(int arrayone[10][10], int arraytwo[10][10], int rows, int colums, int mul){
    int i, j;
    int sumM[10][10];
    int scaM[10][10];
    for (i = 0; i < rows; i++){
        for (j = 0; j < colums; j++){
            scaM[i][j] = mul * arraytwo[i][j];
            }
        }


    for (i = 0; i < rows; i++){
        for (j = 0; j < colums; j++){
            sumM[i][j] = arrayone[i][j] + scaM[i][j];
            printf("\t%d", sumM[i][j]);
        }
        printf("\n");
    }
}


void matrixScalarMultiply(int array[10][10], int scalar, int rows, int colums){
    int i, j;
    int scaM[10][10];
    for (i = 0; i < rows; i++){
        for (j = 0; j < colums; j++){
            scaM[i][j] = scalar * array[i][j];
            printf("%d\t", scaM[i][j]);
        }
        printf("\n");
    }

}

void matrixMultiply(int arrayone[10][10], int arraytwo[10][10], int rowsA, int columsA,int columsB){
    int i, j, k;
    int mulM[10][10];

    
    for (i = 0; i<rowsA; ++i)
        for (j = 0; j<columsB; ++j)
        {
            mulM[i][j] = 0;
        }

    
    for (i = 0; i<rowsA; ++i)
        for (j = 0; j<columsB; ++j)
            for (k = 0; k<columsA; ++k)
            {
                mulM[i][j] += arrayone[i][k] * arraytwo[k][j];
            }
    printf("\nOutput Matrix:\n");
    for (i = 0; i<rowsA; ++i)
        for (j = 0; j<columsB; ++j)
        {
            printf("\t%d ", mulM[i][j]);
            if (j == columsB - 1)
                printf("\n\n");
        }
}


float determinants(float a[25][25], float k){
  float s = 1, det = 0, b[25][25];
  int i, j, m, n, c;
  if (k == 1){
     return (a[0][0]);
    }
  else{
     det = 0;
     for (c = 0; c < k; c++){
        m = 0;
        n = 0;
        for (i = 0;i < k; i++){
            for (j = 0 ;j < k; j++){
                b[i][j] = 0;
                if (i != 0 && j != c){
                   b[m][n] = a[i][j];
                   if (n < (k - 2))
                    n++;
                   else{
                     n = 0;
                     m++;
                     }
                   }
               }
             }
          det = det + s * (a[0][c] * determinants(b, k - 1));
          s = -1 * s;
          }
    }
 
    return (det);
}
 
 
// function for cofactor calculation
void cofactor(float num[25][25], float f){
    float b[25][25], fac[25][25];
    int p, q, m, n, i, j;
    for (q = 0;q < f; q++){
        for (p = 0;p < f; p++){
            m = 0;
            n = 0;
    for (i = 0;i < f; i++){
        for (j = 0;j < f; j++){
            if (i != q && j != p){
                b[m][n] = num[i][j];
            if (n < (f - 2))
                n++;
            else{
               n = 0;
               m++;
               }
            }
        }
      }
      fac[q][p] = pow(-1, q + p) * determinants(b, f - 1);
    }
  }
  transpose(num, fac, f);
}
 
 
///function to find the transpose of a matrix
void transpose(float num[25][25], float fac[25][25], float r){
  int i, j;
  float b[25][25], inverse[25][25], d;
 
  for (i = 0;i < r; i++){
     for (j = 0;j < r; j++){
         b[i][j] = fac[j][i];
        }
    }
    
  d = determinants(num, r);
  for (i = 0;i < r; i++){
     for (j = 0;j < r; j++){
        inverse[i][j] = b[i][j] / d;
        }
    }
    
   printf("\nThe inverse of matrix: \n");
   for (i = 0;i < r; i++){
     for (j = 0;j < r; j++){
         printf("\t%f", inverse[i][j]);
        }
    printf("\n");
     }
}

/*----------------------------------------------------------------------------------------------------*/