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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConPrintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ControlService (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  MSG_STOP_HELP ; 
 int /*<<< orphan*/  MSG_STOP_SYNTAX ; 
 int /*<<< orphan*/ * OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenServiceW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintMessageString (int) ; 
 int /*<<< orphan*/  PrintNetMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_MANAGER_ENUMERATE_SERVICE ; 
 int /*<<< orphan*/  SERVICES_ACTIVE_DATABASE ; 
 int /*<<< orphan*/  SERVICE_CONTROL_STOP ; 
 int /*<<< orphan*/  SERVICE_STOP ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  StdOut ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ *,char*) ; 

INT cmdStop(INT argc, WCHAR **argv)
{
    SC_HANDLE hManager = NULL;
    SC_HANDLE hService = NULL;
    SERVICE_STATUS ServiceStatus;
    DWORD dwError = ERROR_SUCCESS;
    INT nError = 0;
    INT i;

    if (argc != 3)
    {
        PrintMessageString(4381);
        ConPuts(StdOut, L"\n");
        PrintNetMessage(MSG_STOP_SYNTAX);
        return 1;
    }

    for (i = 2; i < argc; i++)
    {
        if (_wcsicmp(argv[i], L"/help") == 0)
        {
            PrintMessageString(4381);
            ConPuts(StdOut, L"\n");
            PrintNetMessage(MSG_STOP_SYNTAX);
            PrintNetMessage(MSG_STOP_HELP);
            return 1;
        }
    }

    hManager = OpenSCManagerW(NULL,
                              SERVICES_ACTIVE_DATABASE,
                              SC_MANAGER_ENUMERATE_SERVICE);
    if (hManager == NULL)
    {
        dwError = GetLastError();
        nError = 1;
        goto done;
    }

    hService = OpenServiceW(hManager,
                            argv[2],
                            SERVICE_STOP);
    if (hService == NULL)
    {
        dwError = GetLastError();
        nError = 1;
        goto done;
    }

    if (!ControlService(hService, SERVICE_CONTROL_STOP, &ServiceStatus))
    {
        dwError = GetLastError();
        nError = 1;
        goto done;
    }

done:
    if (hService != NULL)
        CloseServiceHandle(hService);

    if (hManager != NULL)
        CloseServiceHandle(hManager);

    if (dwError != ERROR_SUCCESS)
    {
        /* FIXME: Print proper error message */
        ConPrintf(StdErr, L"Error: %lu\n", dwError);
    }

    return nError;
}