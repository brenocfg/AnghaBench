#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int U64 ;
typedef  int U32 ;

/* Variables and functions */
 double COMPRESSIBILITY_DEFAULT ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 int /*<<< orphan*/  LZ4_VERSION_STRING ; 
 int /*<<< orphan*/  RDG_genOut (int,double,double,int) ; 
 int SEED_DEFAULT ; 
 int SIZE_DEFAULT ; 
 int displayLevel ; 
 int usage (char*) ; 

int main(int argc, char** argv)
{
    int argNb;
    double proba = (double)COMPRESSIBILITY_DEFAULT / 100;
    double litProba = 0.0;
    U64 size = SIZE_DEFAULT;
    U32 seed = SEED_DEFAULT;
    char* programName;

    /* Check command line */
    programName = argv[0];
    for(argNb=1; argNb<argc; argNb++)
    {
        char* argument = argv[argNb];

        if(!argument) continue;   /* Protection if argument empty */

        /* Handle commands. Aggregated commands are allowed */
        if (*argument=='-')
        {
            argument++;
            while (*argument!=0)
            {
                switch(*argument)
                {
                case 'h':
                    return usage(programName);
                case 'g':
                    argument++;
                    size=0;
                    while ((*argument>='0') && (*argument<='9'))
                    {
                        size *= 10;
                        size += *argument - '0';
                        argument++;
                    }
                    if (*argument=='K') { size <<= 10; argument++; }
                    if (*argument=='M') { size <<= 20; argument++; }
                    if (*argument=='G') { size <<= 30; argument++; }
                    if (*argument=='B') { argument++; }
                    break;
                case 's':
                    argument++;
                    seed=0;
                    while ((*argument>='0') && (*argument<='9'))
                    {
                        seed *= 10;
                        seed += *argument - '0';
                        argument++;
                    }
                    break;
                case 'P':
                    argument++;
                    proba=0.0;
                    while ((*argument>='0') && (*argument<='9'))
                    {
                        proba *= 10;
                        proba += *argument - '0';
                        argument++;
                    }
                    if (proba>100.) proba=100.;
                    proba /= 100.;
                    break;
                case 'L':   /* hidden argument : Literal distribution probability */
                    argument++;
                    litProba=0.;
                    while ((*argument>='0') && (*argument<='9'))
                    {
                        litProba *= 10;
                        litProba += *argument - '0';
                        argument++;
                    }
                    if (litProba>100.) litProba=100.;
                    litProba /= 100.;
                    break;
                case 'v':
                    displayLevel = 4;
                    argument++;
                    break;
                default:
                    return usage(programName);
                }
            }

        }
    }

    DISPLAYLEVEL(4, "Data Generator %s \n", LZ4_VERSION_STRING);
    DISPLAYLEVEL(3, "Seed = %u \n", seed);
    if (proba!=COMPRESSIBILITY_DEFAULT) DISPLAYLEVEL(3, "Compressibility : %i%%\n", (U32)(proba*100));

    RDG_genOut(size, proba, litProba, seed);
    DISPLAYLEVEL(1, "\n");

    return 0;
}