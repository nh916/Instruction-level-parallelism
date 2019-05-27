#include <stdio.h>
#include <stdlib.h>


struct node {
    int dest;
    int src1;
    int src2;
    float delay;
} *instr_set = NULL;
typedef struct node instr;
int num_instr;

void option1() {
    char instr_string[9];
    int i;

    printf("Enter total number of instructions: ");
    scanf("%d", &num_instr);
    printf("\n");


    instr_set = (instr *) malloc((num_instr + 1) * sizeof(instr));

    instr_set[0].dest = -1;
    for (i = 1; i <= num_instr; ++i) {
        printf("%d)", i);
        scanf("%s", instr_string);
        instr_set[i].dest = instr_string[1] - '0';
        instr_set[i].src1 = instr_string[4] - '0';
        instr_set[i].src2 = instr_string[7] - '0';


    }
    printf("\n");
}

void option2() {
    int delay;
    int overlap = 0;
    int total_delay;
    int i;
    int j;


    for (i = 2; i <= num_instr; ++i) {
        delay = 0;

        if ((instr_set[i - 2].dest == instr_set[i].src1) || (instr_set[i - 2].dest == instr_set[i].src2)) {
            if (overlap == 0) {
                delay = 1;
                overlap = 1;
            } else {
                delay = 0;
                overlap = 0;
            }
        } else {
            overlap = 0;
        }

        if ((instr_set[i - 1].dest == instr_set[i].src1) || (instr_set[i - 1].dest == instr_set[i].src2)) {
            delay = 2;
            overlap = 1;
        }

        instr_set[i].delay = delay + 1 + instr_set[i - 1].delay;

    }


    total_delay = instr_set[num_instr].delay + 6;


    printf("Total cycles: %d \n", total_delay);

    for (i = 1; i <= num_instr; ++i) {
        for (j = 0; j < instr_set[i].delay; ++j) {
//            printf("\t");
            printf("    ");
        }
        printf("|F_I|D_I|C_O|F_O|E_I|W_O|\n");
    }
    printf("\n");
}

void option3() {
    float delay;
    int overlap1 = 0, overlap2 = 0, overlap3 = 0, overlap4 = 0, overlap5 = 0;
    int i;
    float j;
    float total_delay;
    float previous_delay;

    instr_set[1].delay = 0;

    for (i = 2; i <= num_instr; ++i) {
        delay = 0;

        if (i > 5) {
            if ((instr_set[i - 5].dest == instr_set[i].src1) || (instr_set[i - 5].dest == instr_set[i].src2)) {
                if ((overlap1 == 0) && (overlap2 == 0) && (overlap3 == 0) && (overlap4 == 0)) {
                    delay = 0.5 - previous_delay;
                    overlap5 = 1;
                } else {
                    delay = 0;
                    overlap5 = 0;
                }
            }
        }

        if (i > 4) {
            if ((instr_set[i - 4].dest == instr_set[i].src1) || (instr_set[i - 4].dest == instr_set[i].src2)) {
                if ((overlap1 == 0) && (overlap2 == 0) && (overlap3 == 0)) {
                    delay = 1 - previous_delay;
                    overlap4 = 1;
                } else {
                    delay = 0;
                    overlap4 = 0;
                }
            }
        }

        if (i > 3) {
            if ((instr_set[i - 3].dest == instr_set[i].src1) || (instr_set[i - 3].dest == instr_set[i].src2)) {
                if ((overlap1 == 0) && (overlap2 == 0)) {
                    delay = 1.5 - previous_delay;
                    overlap3 = 1;
                } else {
                    delay = 0;
                    overlap3 = 0;
                }
            }
        }
        if (i > 2) {
            if ((instr_set[i - 2].dest == instr_set[i].src1) || (instr_set[i - 2].dest == instr_set[i].src2)) {
                if ((overlap1 == 0)) {
                    delay = 2 - previous_delay;
                    overlap2 = 1;
                } else {
                    delay = 0;
                    overlap2 = 0;
                }
            }
        }

        if (i > 1) {
            if ((instr_set[i - 1].dest == instr_set[i].src1) || (instr_set[i - 1].dest == instr_set[i].src2)) {
                delay = 2.5 - previous_delay;
                overlap2 = 1;
            } else {
                delay = 0;
                overlap2 = 0;
            }
        }

        previous_delay = delay;

        instr_set[i].delay = delay + 0.5 + instr_set[i - 1].delay;
    }
    total_delay = instr_set[num_instr].delay + 6;
    printf("Total cycles: %.1f\n", total_delay);

    for (i = 1; i <= num_instr; ++i) {
        for (j = 0; j < instr_set[i].delay; j+= 0.5) {
            printf("  ");
        }
        printf("|F_I|D_I|C_O|F_O|E_I|W_O|\n");
    }
    printf("\n");
    return;
}


int main() {
    int choice = 0;

    while (choice != 4) {
        printf("\nInstruction-level parallelism\n");
        printf("-----------------------------\n");
        printf("1) Enter instructions\n");
        printf("2) Calculate total cycle count on a 6-stage pipeline architecture\n");
        printf("3) Calculate total cycle count on a 6-stage superpipeline architecture\n");
        printf("4) Quit program\n");

        printf("\nEnter selection: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 1:
                option1();
                break;
            case 2:
                option2();
                break;
            case 3:
                option3();
                break;
            case 4:
                return 0000;
            default:
                printf("Not a valid choice. Please try again. \n");
        }
    }
}
