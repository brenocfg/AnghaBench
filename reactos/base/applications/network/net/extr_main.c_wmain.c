#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int (* func ) (int,int /*<<< orphan*/ **) ;scalar_t__ name; } ;
typedef  TYPE_1__* PCOMMAND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConInitStdStreams () ; 
 int /*<<< orphan*/  ConPrintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetSystemDirectoryW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LoadLibrary (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSG_NET_SYNTAX ; 
 int /*<<< orphan*/  PrintMessageString (int) ; 
 int /*<<< orphan*/  PrintNetMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  StdOut ; 
 scalar_t__ TRUE ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* cmds ; 
 int /*<<< orphan*/ * hModuleNetMsg ; 
 int stub1 (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  wcscat (int /*<<< orphan*/ *,char*) ; 

int wmain(int argc, WCHAR **argv)
{
    WCHAR szDllBuffer[MAX_PATH];
    PCOMMAND cmdptr;
    int nResult = 0;
    BOOL bRun = FALSE;

    /* Initialize the Console Standard Streams */
    ConInitStdStreams();

    /* Load netmsg.dll */
    GetSystemDirectoryW(szDllBuffer, ARRAYSIZE(szDllBuffer));
    wcscat(szDllBuffer, L"\\netmsg.dll");

    hModuleNetMsg = LoadLibrary(szDllBuffer);
    if (hModuleNetMsg == NULL)
    {
        ConPrintf(StdErr, L"Failed to load netmsg.dll\n");
        return 1;
    }

    if (argc < 2)
    {
        nResult = 1;
        goto done;
    }

    /* Scan the command table */
    for (cmdptr = cmds; cmdptr->name; cmdptr++)
    {
        if (_wcsicmp(argv[1], cmdptr->name) == 0)
        {
            nResult = cmdptr->func(argc, argv);
            bRun = TRUE;
            break;
        }
    }

done:
    if (bRun == FALSE)
    {
        PrintMessageString(4381);
        ConPuts(StdOut, L"\n");
        PrintNetMessage(MSG_NET_SYNTAX);
    }

    if (hModuleNetMsg != NULL)
        FreeLibrary(hModuleNetMsg);

    return nResult;
}