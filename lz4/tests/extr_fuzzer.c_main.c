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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*) ; 
 int FUZ_COMPRESSIBILITY_DEFAULT ; 
 int FUZ_test (int,unsigned int,unsigned int,double,int) ; 
 int /*<<< orphan*/  FUZ_unitTests (int /*<<< orphan*/ ) ; 
 int FUZ_usage (char const*) ; 
 int /*<<< orphan*/  LZ4HC_CLEVEL_DEFAULT ; 
 int /*<<< orphan*/  LZ4HC_CLEVEL_OPT_MIN ; 
 char* LZ4_versionString () ; 
 unsigned int NB_ATTEMPTS ; 
 int XXH32 (int /*<<< orphan*/  const*,int,int) ; 
 int g_displayLevel ; 
 int /*<<< orphan*/  getchar () ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int main(int argc, const char** argv)
{
    U32 seed = 0;
    int seedset = 0;
    int argNb;
    unsigned nbTests = NB_ATTEMPTS;
    unsigned testNb = 0;
    int proba = FUZ_COMPRESSIBILITY_DEFAULT;
    int use_pause = 0;
    const char* programName = argv[0];
    U32 duration = 0;

    /* Check command line */
    for(argNb=1; argNb<argc; argNb++) {
        const char* argument = argv[argNb];

        if(!argument) continue;   // Protection if argument empty

        // Decode command (note : aggregated commands are allowed)
        if (argument[0]=='-') {
            if (!strcmp(argument, "--no-prompt")) { use_pause=0; seedset=1; g_displayLevel=1; continue; }
            argument++;

            while (*argument!=0) {
                switch(*argument)
                {
                case 'h':   /* display help */
                    return FUZ_usage(programName);

                case 'v':   /* verbose mode */
                    g_displayLevel++;
                    argument++;
                    break;

                case 'p':   /* pause at the end */
                    use_pause=1;
                    argument++;
                    break;

                case 'i':
                    argument++;
                    nbTests = 0; duration = 0;
                    while ((*argument>='0') && (*argument<='9')) {
                        nbTests *= 10;
                        nbTests += (unsigned)(*argument - '0');
                        argument++;
                    }
                    break;

                case 'T':
                    argument++;
                    nbTests = 0; duration = 0;
                    for (;;) {
                        switch(*argument)
                        {
                            case 'm': duration *= 60; argument++; continue;
                            case 's':
                            case 'n': argument++; continue;
                            case '0':
                            case '1':
                            case '2':
                            case '3':
                            case '4':
                            case '5':
                            case '6':
                            case '7':
                            case '8':
                            case '9': duration *= 10; duration += (U32)(*argument++ - '0'); continue;
                        }
                        break;
                    }
                    break;

                case 's':
                    argument++;
                    seed=0; seedset=1;
                    while ((*argument>='0') && (*argument<='9')) {
                        seed *= 10;
                        seed += (U32)(*argument - '0');
                        argument++;
                    }
                    break;

                case 't':   /* select starting test nb */
                    argument++;
                    testNb=0;
                    while ((*argument>='0') && (*argument<='9')) {
                        testNb *= 10;
                        testNb += (unsigned)(*argument - '0');
                        argument++;
                    }
                    break;

                case 'P':  /* change probability */
                    argument++;
                    proba=0;
                    while ((*argument>='0') && (*argument<='9')) {
                        proba *= 10;
                        proba += *argument - '0';
                        argument++;
                    }
                    if (proba<0) proba=0;
                    if (proba>100) proba=100;
                    break;
                default: ;
                }
            }
        }
    }

    printf("Starting LZ4 fuzzer (%i-bits, v%s)\n", (int)(sizeof(size_t)*8), LZ4_versionString());

    if (!seedset) {
        time_t const t = time(NULL);
        U32 const h = XXH32(&t, sizeof(t), 1);
        seed = h % 10000;
    }
    printf("Seed = %u\n", seed);

    if (proba!=FUZ_COMPRESSIBILITY_DEFAULT) printf("Compressibility : %i%%\n", proba);

    if ((seedset==0) && (testNb==0)) { FUZ_unitTests(LZ4HC_CLEVEL_DEFAULT); FUZ_unitTests(LZ4HC_CLEVEL_OPT_MIN); }

    nbTests += (nbTests==0);  /* avoid zero */

    {   int const result = FUZ_test(seed, nbTests, testNb, ((double)proba) / 100, duration);
        if (use_pause) {
            DISPLAY("press enter ... \n");
            (void)getchar();
        }
        return result;
    }
}