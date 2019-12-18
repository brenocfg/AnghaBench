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
typedef  int wchar_t ;
typedef  int WCHAR ;
typedef  int* LPWSTR ;
typedef  int INT ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EOF ; 
 void* FALSE ; 
 int /*<<< orphan*/  ICMP ; 
 int /*<<< orphan*/  IDS_USAGE ; 
 int /*<<< orphan*/  IP ; 
 int /*<<< orphan*/  Interval ; 
 int /*<<< orphan*/  Protocol ; 
 int /*<<< orphan*/  StdOut ; 
 int /*<<< orphan*/  TCP ; 
 void* TRUE ; 
 int /*<<< orphan*/  UDP ; 
 int /*<<< orphan*/  _wcsicmp (char*,int*) ; 
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
 scalar_t__ iswdigit (int) ; 
 scalar_t__ swscanf (int*,char*,int /*<<< orphan*/ *) ; 
 int towlower (int) ; 

BOOL ParseCmdline(int argc, wchar_t* argv[])
{
    LPWSTR Proto;
    WCHAR c;
    INT i;

    if ((argc == 1) || (iswdigit(*argv[1])))
        bNoOptions = TRUE;

    /* Parse command line for options we have been given. */
    for (i = 1; i < argc; i++)
    {
        if ((argc > 1) && (argv[i][0] == L'-' || argv[i][0] == L'/'))
        {
            while ((c = *++argv[i]) != L'\0')
            {
                switch (towlower(c))
                {
                    case L'a':
                        bDoShowAllCons = TRUE;
                        break;
                    case L'b':
                        bDoShowProcName = TRUE;
                        break;
                    case L'e':
                        bDoShowEthStats = TRUE;
                        break;
                    case L'n':
                        bDoShowNumbers = TRUE;
                        break;
                    case L'p':
                        bDoShowProtoCons = TRUE;
                        Proto = argv[i+1];
                        if (!_wcsicmp(L"IP", Proto))
                            Protocol = IP;
                        else if (!_wcsicmp(L"ICMP", Proto))
                            Protocol = ICMP;
                        else if (!_wcsicmp(L"TCP", Proto))
                            Protocol = TCP;
                        else if (!_wcsicmp(L"UDP", Proto))
                            Protocol = UDP;
                        else
                        {
                            ConResPuts(StdOut, IDS_USAGE);
                            return FALSE;
                        }
                        break;
                    case L'r':
                        bDoShowRouteTable = TRUE;
                        break;
                    case L's':
                        bDoShowProtoStats = TRUE;
                        break;
                    case L'o':
                        bDoShowProcessId = TRUE;
                        break;
                    case L'v':
                        // FIXME!
                        ConPuts(StdOut, L"got v\n");
                        bDoDispSeqComp = TRUE;
                        break;
                    default :
                        ConResPuts(StdOut, IDS_USAGE);
                        return FALSE;
                }
            }
        }
        else if (iswdigit(*argv[i]) != 0)
        {
            if (swscanf(argv[i], L"%lu", &Interval) != EOF)
                bLoopOutput = TRUE;
            else
                return FALSE;
        }
//        else
//        {
//            ConResPrintf(StdOut, IDS_USAGE);
//            return FALSE;
//        }
    }

    return TRUE;
}