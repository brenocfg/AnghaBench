#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int dwImageRunCount; int /*<<< orphan*/  dwProcessId; int /*<<< orphan*/  hProcess; int /*<<< orphan*/  pszImagePath; int /*<<< orphan*/ * hToken; } ;
struct TYPE_15__ {int dwServiceType; } ;
struct TYPE_17__ {TYPE_9__* lpImage; int /*<<< orphan*/  lpServiceName; TYPE_1__ Status; } ;
struct TYPE_16__ {int cb; char* lpDesktop; int /*<<< orphan*/  hThread; int /*<<< orphan*/  dwProcessId; int /*<<< orphan*/  hProcess; int /*<<< orphan*/  dwThreadId; int /*<<< orphan*/  dwFlags; } ;
typedef  int /*<<< orphan*/  StartupInfo ;
typedef  TYPE_2__ STARTUPINFOW ;
typedef  int /*<<< orphan*/  ProcessInformation ;
typedef  TYPE_3__* PSERVICE ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int CREATE_SUSPENDED ; 
 int CREATE_UNICODE_ENVIRONMENT ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateEnvironmentBlock (int /*<<< orphan*/ **,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ CreateProcessAsUserW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ CreateProcessW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int DETACHED_PROCESS ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_3__*,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  DestroyEnvironmentBlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ ImpersonateLoggedOnUser (int /*<<< orphan*/ *) ; 
 scalar_t__ NoInteractiveServices ; 
 int /*<<< orphan*/  ResumeThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RevertToSelf () ; 
 int SERVICE_INTERACTIVE_PROCESS ; 
 int /*<<< orphan*/  STARTF_INHERITDESKTOP ; 
 int /*<<< orphan*/  ScmIsSecurityService (TYPE_9__*) ; 
 scalar_t__ ScmSendStartCommand (TYPE_3__*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ ScmWaitForServiceConnect (TYPE_3__*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 

__attribute__((used)) static DWORD
ScmStartUserModeService(PSERVICE Service,
                        DWORD argc,
                        LPWSTR* argv)
{
    PROCESS_INFORMATION ProcessInformation;
    STARTUPINFOW StartupInfo;
    LPVOID lpEnvironment;
    BOOL Result;
    DWORD dwError = ERROR_SUCCESS;

    DPRINT("ScmStartUserModeService(%p)\n", Service);

    /* If the image is already running ... */
    if (Service->lpImage->dwImageRunCount > 1)
    {
        /* ... just send a start command */
        return ScmSendStartCommand(Service, argc, argv);
    }

    /* Otherwise start its process */
    ZeroMemory(&StartupInfo, sizeof(StartupInfo));
    StartupInfo.cb = sizeof(StartupInfo);
    ZeroMemory(&ProcessInformation, sizeof(ProcessInformation));

    if (Service->lpImage->hToken)
    {
        /* User token: Run the service under the user account */

        if (!CreateEnvironmentBlock(&lpEnvironment, Service->lpImage->hToken, FALSE))
        {
            /* We failed, run the service with the current environment */
            DPRINT1("CreateEnvironmentBlock() failed with error %d; service '%S' will run with the current environment.\n",
                    GetLastError(), Service->lpServiceName);
            lpEnvironment = NULL;
        }

        /* Impersonate the new user */
        Result = ImpersonateLoggedOnUser(Service->lpImage->hToken);
        if (Result)
        {
            /* Launch the process in the user's logon session */
            Result = CreateProcessAsUserW(Service->lpImage->hToken,
                                          NULL,
                                          Service->lpImage->pszImagePath,
                                          NULL,
                                          NULL,
                                          FALSE,
                                          CREATE_UNICODE_ENVIRONMENT | DETACHED_PROCESS | CREATE_SUSPENDED,
                                          lpEnvironment,
                                          NULL,
                                          &StartupInfo,
                                          &ProcessInformation);
            if (!Result)
                dwError = GetLastError();

            /* Revert the impersonation */
            RevertToSelf();
        }
        else
        {
            dwError = GetLastError();
            DPRINT1("ImpersonateLoggedOnUser() failed with error %d\n", dwError);
        }
    }
    else
    {
        /* No user token: Run the service under the LocalSystem account */

        if (!CreateEnvironmentBlock(&lpEnvironment, NULL, TRUE))
        {
            /* We failed, run the service with the current environment */
            DPRINT1("CreateEnvironmentBlock() failed with error %d; service '%S' will run with the current environment.\n",
                    GetLastError(), Service->lpServiceName);
            lpEnvironment = NULL;
        }

        /* Use the interactive desktop if the service is interactive */
        if ((NoInteractiveServices == 0) &&
            (Service->Status.dwServiceType & SERVICE_INTERACTIVE_PROCESS))
        {
            StartupInfo.dwFlags |= STARTF_INHERITDESKTOP;
            StartupInfo.lpDesktop = L"WinSta0\\Default";
        }

        if (!ScmIsSecurityService(Service->lpImage))
        {
            Result = CreateProcessW(NULL,
                                    Service->lpImage->pszImagePath,
                                    NULL,
                                    NULL,
                                    FALSE,
                                    CREATE_UNICODE_ENVIRONMENT | DETACHED_PROCESS | CREATE_SUSPENDED,
                                    lpEnvironment,
                                    NULL,
                                    &StartupInfo,
                                    &ProcessInformation);
            if (!Result)
                dwError = GetLastError();
        }
        else
        {
            Result = TRUE;
            dwError = ERROR_SUCCESS;
        }
    }

    if (lpEnvironment)
        DestroyEnvironmentBlock(lpEnvironment);

    if (!Result)
    {
        DPRINT1("Starting '%S' failed with error %d\n",
                Service->lpServiceName, dwError);
        return dwError;
    }

    DPRINT("Process Id: %lu  Handle %p\n",
           ProcessInformation.dwProcessId,
           ProcessInformation.hProcess);
    DPRINT("Thread Id: %lu  Handle %p\n",
           ProcessInformation.dwThreadId,
           ProcessInformation.hThread);

    /* Get the process handle and ID */
    Service->lpImage->hProcess = ProcessInformation.hProcess;
    Service->lpImage->dwProcessId = ProcessInformation.dwProcessId;

    /* Resume the main thread and close its handle */
    ResumeThread(ProcessInformation.hThread);
    CloseHandle(ProcessInformation.hThread);

    /* Connect control pipe */
    dwError = ScmWaitForServiceConnect(Service);
    if (dwError != ERROR_SUCCESS)
    {
        DPRINT1("Connecting control pipe failed! (Error %lu)\n", dwError);
        Service->lpImage->dwProcessId = 0;
        return dwError;
    }

    /* Send the start command */
    return ScmSendStartCommand(Service, argc, argv);
}