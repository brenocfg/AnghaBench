#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * lpsaActions; } ;
typedef  TYPE_1__ SERVICE_FAILURE_ACTIONS ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  int /*<<< orphan*/ * LPCTSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  INT ;
typedef  scalar_t__ BOOLEAN ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ChangeServiceConfig2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OpenSCManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenService (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ParseFailureArguments (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ **,TYPE_1__*) ; 
 int /*<<< orphan*/  ReportLastError () ; 
 int /*<<< orphan*/  RtlAdjustPrivilege (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  SC_MANAGER_CONNECT ; 
 int SERVICE_CHANGE_CONFIG ; 
 int /*<<< orphan*/  SERVICE_CONFIG_FAILURE_ACTIONS ; 
 int SERVICE_START ; 
 int /*<<< orphan*/  SE_SHUTDOWN_PRIVILEGE ; 
 int /*<<< orphan*/  SetFailureUsage () ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,...) ; 

BOOL
SetFailure(
    LPCTSTR *ServiceArgs,
    INT ArgCount)
{
    SC_HANDLE hManager = NULL;
    SC_HANDLE hService = NULL;
    BOOL bResult = TRUE;
    SERVICE_FAILURE_ACTIONS FailureActions;
    LPCTSTR lpServiceName = NULL;
    BOOLEAN Old = FALSE;

    ZeroMemory(&FailureActions, sizeof(SERVICE_FAILURE_ACTIONS));

    if (!ParseFailureArguments(ServiceArgs, ArgCount, &lpServiceName, &FailureActions))
    {
        SetFailureUsage();
        return FALSE;
    }

    hManager = OpenSCManager(NULL,
                             NULL,
                             SC_MANAGER_CONNECT);
    if (hManager == NULL)
    {
        _tprintf(_T("[SC] OpenSCManager FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    hService = OpenService(hManager,
                           lpServiceName,
                           SERVICE_CHANGE_CONFIG | SERVICE_START);
    if (hService == NULL)
    {
        _tprintf(_T("[SC] OpenService FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, &Old);

    if (!ChangeServiceConfig2(hService,
                              SERVICE_CONFIG_FAILURE_ACTIONS,
                              (LPBYTE)&FailureActions))
    {
        _tprintf(_T("[SC] ChangeServiceConfig2 FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    _tprintf(_T("[SC] ChangeServiceConfig2 SUCCESS\n\n"));

done:
    RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, Old, FALSE, &Old);

    if (bResult == FALSE)
        ReportLastError();

    if (FailureActions.lpsaActions != NULL)
        HeapFree(GetProcessHeap(), 0, FailureActions.lpsaActions);

    if (hService)
        CloseServiceHandle(hService);

    if (hManager)
        CloseServiceHandle(hManager);

    return bResult;
}