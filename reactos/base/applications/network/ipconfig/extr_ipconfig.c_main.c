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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DisplayDns () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FlushDns () ; 
 int /*<<< orphan*/  GetModuleHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  ProcessHeap ; 
 int /*<<< orphan*/  Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Renew (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShowInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Usage () ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tcsicmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tcslen (char*) ; 
 int /*<<< orphan*/  _tcsnicmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hInstance ; 

int main(int argc, char *argv[])
{
    BOOL DoUsage=FALSE;
    BOOL DoAll=FALSE;
    BOOL DoRelease=FALSE;
    BOOL DoRenew=FALSE;
    BOOL DoFlushdns=FALSE;
    BOOL DoRegisterdns=FALSE;
    BOOL DoDisplaydns=FALSE;
    BOOL DoShowclassid=FALSE;
    BOOL DoSetclassid=FALSE;

    hInstance = GetModuleHandle(NULL);
    ProcessHeap = GetProcessHeap();

    /* Parse command line for options we have been given. */
    if ((argc > 1) && (argv[1][0]=='/' || argv[1][0]=='-'))
    {
        if (!_tcsicmp(&argv[1][1], _T("?")))
        {
            DoUsage = TRUE;
        }
        else if (!_tcsnicmp(&argv[1][1], _T("ALL"), _tcslen(&argv[1][1])))
        {
           DoAll = TRUE;
        }
        else if (!_tcsnicmp(&argv[1][1], _T("RELEASE"), _tcslen(&argv[1][1])))
        {
            DoRelease = TRUE;
        }
        else if (!_tcsnicmp(&argv[1][1], _T("RENEW"), _tcslen(&argv[1][1])))
        {
            DoRenew = TRUE;
        }
        else if (!_tcsnicmp(&argv[1][1], _T("FLUSHDNS"), _tcslen(&argv[1][1])))
        {
            DoFlushdns = TRUE;
        }
        else if (!_tcsnicmp(&argv[1][1], _T("FLUSHREGISTERDNS"), _tcslen(&argv[1][1])))
        {
            DoRegisterdns = TRUE;
        }
        else if (!_tcsnicmp(&argv[1][1], _T("DISPLAYDNS"), _tcslen(&argv[1][1])))
        {
            DoDisplaydns = TRUE;
        }
        else if (!_tcsnicmp(&argv[1][1], _T("SHOWCLASSID"), _tcslen(&argv[1][1])))
        {
            DoShowclassid = TRUE;
        }
        else if (!_tcsnicmp(&argv[1][1], _T("SETCLASSID"), _tcslen(&argv[1][1])))
        {
            DoSetclassid = TRUE;
        }
    }

    switch (argc)
    {
        case 1:  /* Default behaviour if no options are given*/
            ShowInfo(FALSE);
            break;
        case 2:  /* Process all the options that take no parameters */
            if (DoUsage)
                Usage();
            else if (DoAll)
                ShowInfo(TRUE);
            else if (DoRelease)
                Release(NULL);
            else if (DoRenew)
                Renew(NULL);
            else if (DoFlushdns)
                FlushDns();
            else if (DoRegisterdns)
                _tprintf(_T("\nSorry /registerdns is not implemented yet\n"));
            else if (DoDisplaydns)
                DisplayDns();
            else
                Usage();
            break;
        case 3: /* Process all the options that can have 1 parameter */
            if (DoRelease)
                _tprintf(_T("\nSorry /release [adapter] is not implemented yet\n"));
                //Release(argv[2]);
            else if (DoRenew)
                _tprintf(_T("\nSorry /renew [adapter] is not implemented yet\n"));
            else if (DoShowclassid)
                _tprintf(_T("\nSorry /showclassid adapter is not implemented yet\n"));
            else if (DoSetclassid)
                _tprintf(_T("\nSorry /setclassid adapter is not implemented yet\n"));
            else
                Usage();
            break;
        case 4:  /* Process all the options that can have 2 parameters */
            if (DoSetclassid)
                _tprintf(_T("\nSorry /setclassid adapter [classid]is not implemented yet\n"));
            else
                Usage();
            break;
        default:
            Usage();
    }

    return 0;
}