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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  SERVICE_STATUS ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConPrintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ControlService (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  MSG_CONTINUE_HELP ; 
 int /*<<< orphan*/  MSG_CONTINUE_SYNTAX ; 
 int /*<<< orphan*/ * OpenSCManager (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenService (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintMessageString (int) ; 
 int /*<<< orphan*/  PrintNetMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_MANAGER_ENUMERATE_SERVICE ; 
 int /*<<< orphan*/  SERVICES_ACTIVE_DATABASE ; 
 int /*<<< orphan*/  SERVICE_CONTROL_CONTINUE ; 
 int /*<<< orphan*/  SERVICE_PAUSE_CONTINUE ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  StdOut ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ *,char*) ; 

INT cmdContinue(INT argc, WCHAR **argv)
{
    SC_HANDLE hManager = NULL;
    SC_HANDLE hService = NULL;
    SERVICE_STATUS status;
    INT nError = 0;
    INT i;

    if (argc != 3)
    {
        PrintMessageString(4381);
        ConPuts(StdOut, L"\n");
        PrintNetMessage(MSG_CONTINUE_SYNTAX);
        return 1;
    }

    for (i = 2; i < argc; i++)
    {
        if (_wcsicmp(argv[i], L"/help") == 0)
        {
            PrintMessageString(4381);
            ConPuts(StdOut, L"\n");
            PrintNetMessage(MSG_CONTINUE_SYNTAX);
            PrintNetMessage(MSG_CONTINUE_HELP);
            return 1;
        }
    }

    hManager = OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ENUMERATE_SERVICE);
    if (hManager == NULL)
    {
        ConPrintf(StdErr, L"[OpenSCManager] Error: %ld\n", GetLastError());
        nError = 1;
        goto done;
    }

    hService = OpenService(hManager, argv[2], SERVICE_PAUSE_CONTINUE);
    if (hService == NULL)
    {
        ConPrintf(StdErr, L"[OpenService] Error: %ld\n", GetLastError());
        nError = 1;
        goto done;
    }

    if (!ControlService(hService, SERVICE_CONTROL_CONTINUE, &status))
    {
        ConPrintf(StdErr, L"[ControlService] Error: %ld\n", GetLastError());
        nError = 1;
    }

done:
    if (hService != NULL)
        CloseServiceHandle(hService);

    if (hManager != NULL)
        CloseServiceHandle(hManager);

    return nError;
}