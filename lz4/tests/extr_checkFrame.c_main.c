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
typedef  int /*<<< orphan*/  cRess_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXM_THROW (int,char*,char const*,int /*<<< orphan*/ ) ; 
 int FUZ_usage (char const* const) ; 
 int /*<<< orphan*/  LZ4_VERSION_STRING ; 
 int createCResources (int /*<<< orphan*/ *) ; 
 int displayLevel ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int frameCheck (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,size_t) ; 
 int /*<<< orphan*/  freeCResources (int /*<<< orphan*/ ) ; 
 int no_prompt ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int use_pause ; 

int main(int argc, const char** argv)
{
    int argNb;
    unsigned bsid=0;
    size_t blockSize=0;
    const char* const programName = argv[0];

    /* Check command line */
    for (argNb=1; argNb<argc; argNb++) {
        const char* argument = argv[argNb];

        if(!argument) continue;   /* Protection if argument empty */

        /* Decode command (note : aggregated short commands are allowed) */
        if (argument[0]=='-') {
            if (!strcmp(argument, "--no-prompt")) {
                no_prompt=1;
                displayLevel=1;
                continue;
            }
            argument++;

            while (*argument!=0) {
                switch(*argument)
                {
                case 'h':
                    return FUZ_usage(programName);
                case 'v':
                    argument++;
                    displayLevel++;
                    break;
                case 'q':
                    argument++;
                    displayLevel--;
                    break;
                case 'p': /* pause at the end */
                    argument++;
                    use_pause = 1;
                    break;

                case 'b':
                    argument++;
                    bsid=0;
                    while ((*argument>='0') && (*argument<='9')) {
                        bsid *= 10;
                        bsid += (unsigned)(*argument - '0');
                        argument++;
                    }
                    break;

                case 'B':
                    argument++;
                    blockSize=0;
                    while ((*argument>='0') && (*argument<='9')) {
                        blockSize *= 10;
                        blockSize += (size_t)(*argument - '0');
                        argument++;
                    }
                    break;

                default:
                    ;
                    return FUZ_usage(programName);
                }
            }
        } else {
            int err;
            FILE *srcFile;
            cRess_t ress;
            if (bsid == 0 || blockSize == 0)
              return FUZ_usage(programName);
            DISPLAY("Starting frame checker (%i-bits, %s)\n", (int)(sizeof(size_t)*8), LZ4_VERSION_STRING);
            err = createCResources(&ress);
            if (err) return (err);
            srcFile = fopen(argument, "rb");
            if ( srcFile==NULL ) {
                freeCResources(ress);
                EXM_THROW(1, "%s: %s \n", argument, strerror(errno));
            }
            err = frameCheck(ress, srcFile, bsid, blockSize);
            freeCResources(ress);
            fclose(srcFile);
            return (err);
        }
    }
    return 0;
}