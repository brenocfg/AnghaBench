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
typedef  char* LPSTR ;
typedef  int INT ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  ICMP ; 
 int /*<<< orphan*/  IP ; 
 int /*<<< orphan*/  Interval ; 
 int /*<<< orphan*/  Protocol ; 
 int /*<<< orphan*/  TCP ; 
 void* TRUE ; 
 int /*<<< orphan*/  UDP ; 
 int /*<<< orphan*/  Usage () ; 
 int /*<<< orphan*/  _T (char*) ; 
 scalar_t__ _istdigit (char) ; 
 int /*<<< orphan*/  _stricmp (char*,char*) ; 
 scalar_t__ _stscanf (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ) ; 
 void* bDoDispSeqComp ; 
 void* bDoShowAllCons ; 
 void* bDoShowEthStats ; 
 void* bDoShowNumbers ; 
 void* bDoShowProcName ; 
 void* bDoShowProcessId ; 
 void* bDoShowProtoCons ; 
 void* bDoShowProtoStats ; 
 void* bDoShowRouteTable ; 
 void* bLoopOutput ; 
 void* bNoOptions ; 
 int tolower (char) ; 

BOOL ParseCmdline(int argc, char* argv[])
{
    LPSTR Proto;
    CHAR c;
    INT i;

    if ((argc == 1) || (_istdigit(*argv[1])))
        bNoOptions = TRUE;

    /* Parse command line for options we have been given. */
    for (i = 1; i < argc; i++)
    {
        if ((argc > 1) && (argv[i][0] == '-' || argv[i][0] == '/'))
        {
            while ((c = *++argv[i]) != '\0')
            {
                switch (tolower(c))
                {
                    case 'a' :
                        bDoShowAllCons = TRUE;
                        break;
                    case 'b' :
                        bDoShowProcName = TRUE;
                        break;
                    case 'e' :
                        bDoShowEthStats = TRUE;
                        break;
                    case 'n' :
                        bDoShowNumbers = TRUE;
                        break;
                    case 'p' :
                        bDoShowProtoCons = TRUE;
                        Proto = argv[i+1];
                        if (!_stricmp("IP", Proto))
                            Protocol = IP;
                        else if (!_stricmp("ICMP", Proto))
                            Protocol = ICMP;
                        else if (!_stricmp("TCP", Proto))
                            Protocol = TCP;
                        else if (!_stricmp("UDP", Proto))
                            Protocol = UDP;
                        else
                        {
                            Usage();
                            return EXIT_FAILURE;
                        }
                        break;
                    case 'r' :
                        bDoShowRouteTable = TRUE;
                        break;
                    case 's' :
                        bDoShowProtoStats = TRUE;
                        break;
                    case 'o' :
                        bDoShowProcessId = TRUE;
                        break;
                    case 'v' :
                        _tprintf(_T("got v\n"));
                        bDoDispSeqComp = TRUE;
                        break;
                    default :
                        Usage();
                        return EXIT_FAILURE;
                }
            }
        }
        else if (_istdigit(*argv[i]))
        {
            if (_stscanf(argv[i], "%lu", &Interval) != EOF)
                bLoopOutput = TRUE;
            else
                return EXIT_FAILURE;
        }
//        else
//        {
//            Usage();
//            EXIT_FAILURE;
//        }
    }

    return EXIT_SUCCESS;
}