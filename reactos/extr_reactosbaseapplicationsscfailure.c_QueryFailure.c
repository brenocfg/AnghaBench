#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t cActions; TYPE_1__* lpsaActions; scalar_t__ lpCommand; scalar_t__ lpRebootMsg; int /*<<< orphan*/  dwResetPeriod; } ;
struct TYPE_5__ {int Type; int /*<<< orphan*/  Delay; } ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  TYPE_2__* LPSERVICE_FAILURE_ACTIONS ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  size_t INT ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * OpenSCManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenService (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QueryServiceConfig2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  ReportLastError () ; 
#define  SC_ACTION_NONE 131 
#define  SC_ACTION_REBOOT 130 
#define  SC_ACTION_RESTART 129 
#define  SC_ACTION_RUN_COMMAND 128 
 int /*<<< orphan*/  SC_MANAGER_CONNECT ; 
 int /*<<< orphan*/  SERVICE_CONFIG_FAILURE_ACTIONS ; 
 int /*<<< orphan*/  SERVICE_QUERY_CONFIG ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 scalar_t__ _T (char*) ; 
 int /*<<< orphan*/  _tprintf (scalar_t__,...) ; 

BOOL QueryFailure(LPCTSTR ServiceName)
{
    SC_HANDLE hManager = NULL;
    SC_HANDLE hService = NULL;
    BOOL bResult = TRUE;
    DWORD cbBytesNeeded = 0;
    LPSERVICE_FAILURE_ACTIONS pServiceFailure = NULL;
    INT i;

#ifdef SCDBG
    _tprintf(_T("service to show failure action - %s\n\n"), ServiceName);
#endif

    hManager = OpenSCManager(NULL,
                             NULL,
                             SC_MANAGER_CONNECT);
    if (hManager == NULL)
    {
        bResult = FALSE;
        goto done;
    }

    hService = OpenService(hManager, ServiceName, SERVICE_QUERY_CONFIG);
    if (hService == NULL)
    {
        bResult = FALSE;
        goto done;
    }

    if (!QueryServiceConfig2(hService,
                             SERVICE_CONFIG_FAILURE_ACTIONS,
                             NULL,
                             0,
                             &cbBytesNeeded))
    {
        if (cbBytesNeeded == 0)
        {
            bResult = FALSE;
            goto done;
        }
    }

    pServiceFailure = HeapAlloc(GetProcessHeap(), 0, cbBytesNeeded);
    if (pServiceFailure == NULL)
    {
        SetLastError(ERROR_OUTOFMEMORY);
        bResult = FALSE;
        goto done;
    }

    if (!QueryServiceConfig2(hService,
                             SERVICE_CONFIG_FAILURE_ACTIONS,
                             (LPBYTE)pServiceFailure,
                             cbBytesNeeded,
                             &cbBytesNeeded))
    {
        bResult = FALSE;
        goto done;
    }

    _tprintf(_T("SERVICE_NAME: %s\n"), ServiceName);
    _tprintf(_T("        RESET_PERIOD       : %lu seconds\n"), pServiceFailure->dwResetPeriod);
    _tprintf(_T("        REBOOT_MESSAGE     : %s\n"), (pServiceFailure->lpRebootMsg) ? pServiceFailure->lpRebootMsg : _T(""));
    _tprintf(_T("        COMMAND_LINE       : %s\n"), (pServiceFailure->lpCommand) ? pServiceFailure->lpCommand : _T(""));
    _tprintf(_T("        FAILURE_ACTIONS    : "));
    for (i = 0; i < pServiceFailure->cActions; i++)
    {
        if (i != 0)
            _tprintf(_T("                             "));
        switch (pServiceFailure->lpsaActions[i].Type)
        {
            case SC_ACTION_NONE:
                continue;

            case SC_ACTION_RESTART:
                _tprintf(_T("RESTART -- Delay = %lu milliseconds.\n"), pServiceFailure->lpsaActions[i].Delay);
                break;

            case SC_ACTION_REBOOT:
                _tprintf(_T("REBOOT -- Delay = %lu milliseconds.\n"), pServiceFailure->lpsaActions[i].Delay);
                break;

            case SC_ACTION_RUN_COMMAND:
                _tprintf(_T("RUN_COMMAND -- Delay = %lu milliseconds.\n"), pServiceFailure->lpsaActions[i].Delay);
                break;

            default:
                _tprintf(_T("\n"));
                break;
        }
    }

done:
    if (bResult == FALSE)
        ReportLastError();

    if (pServiceFailure != NULL)
        HeapFree(GetProcessHeap(), 0, pServiceFailure);

    if (hService)
        CloseServiceHandle(hService);

    if (hManager)
        CloseServiceHandle(hManager);

    return bResult;
}