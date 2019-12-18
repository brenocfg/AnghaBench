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
struct TYPE_4__ {scalar_t__ dwServiceFlags; scalar_t__ dwProcessId; } ;
typedef  int /*<<< orphan*/  Status ;
typedef  TYPE_1__ SERVICE_STATUS_PROCESS ;
typedef  int /*<<< orphan*/  SERVICE_STATUS ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  int LPCTSTR ;
typedef  scalar_t__ INT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ControlService (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CopyMemory (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int GetLastError () ; 
 int /*<<< orphan*/ * OpenSCManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenService (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  PrintService (int,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportLastError () ; 
 int /*<<< orphan*/  SC_MANAGER_CONNECT ; 
#define  SERVICE_CONTROL_CONTINUE 136 
#define  SERVICE_CONTROL_INTERROGATE 135 
#define  SERVICE_CONTROL_NETBINDADD 134 
#define  SERVICE_CONTROL_NETBINDDISABLE 133 
#define  SERVICE_CONTROL_NETBINDENABLE 132 
#define  SERVICE_CONTROL_NETBINDREMOVE 131 
#define  SERVICE_CONTROL_PARAMCHANGE 130 
#define  SERVICE_CONTROL_PAUSE 129 
#define  SERVICE_CONTROL_STOP 128 
 int SERVICE_INTERROGATE ; 
 int SERVICE_PAUSE_CONTINUE ; 
 int SERVICE_STOP ; 
 int SERVICE_USER_DEFINED_CONTROL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,...) ; 

BOOL
Control(DWORD Control,
        LPCTSTR ServiceName,
        LPCTSTR *Args,
        INT ArgCount)
{
    SC_HANDLE hSCManager = NULL;
    SC_HANDLE hService = NULL;
    SERVICE_STATUS Status;
    DWORD dwDesiredAccess = 0;
    BOOL bResult = TRUE;
    SERVICE_STATUS_PROCESS StatusEx;

#ifdef SCDBG
    LPCTSTR *TmpArgs = Args;
    INT TmpCnt = ArgCount;
    _tprintf(_T("service to control - %s\n"), ServiceName);
    _tprintf(_T("command - %lu\n"), Control);
    _tprintf(_T("Arguments:\n"));
    while (TmpCnt)
    {
        _tprintf(_T("  %s\n"), *TmpArgs);
        TmpArgs++;
        TmpCnt--;
    }
    _tprintf(_T("\n"));
#endif /* SCDBG */

    switch (Control)
    {
        case SERVICE_CONTROL_STOP:
            dwDesiredAccess = SERVICE_STOP;
            break;

        case SERVICE_CONTROL_PAUSE:
        case SERVICE_CONTROL_CONTINUE:
        case SERVICE_CONTROL_PARAMCHANGE:
        case SERVICE_CONTROL_NETBINDADD:
        case SERVICE_CONTROL_NETBINDREMOVE:
        case SERVICE_CONTROL_NETBINDENABLE:
        case SERVICE_CONTROL_NETBINDDISABLE:
            dwDesiredAccess = SERVICE_PAUSE_CONTINUE;
            break;

        case SERVICE_CONTROL_INTERROGATE:
            dwDesiredAccess = SERVICE_INTERROGATE;
            break;

        default:
            if (Control >= 128 && Control <= 255)
                dwDesiredAccess = SERVICE_USER_DEFINED_CONTROL;
            else
                dwDesiredAccess = 0;
            break;
    }

    hSCManager = OpenSCManager(NULL,
                               NULL,
                               SC_MANAGER_CONNECT);
    if (hSCManager == NULL)
    {
        _tprintf(_T("[SC] OpenSCManager FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    hService = OpenService(hSCManager,
                           ServiceName,
                           dwDesiredAccess);
    if (hService == NULL)
    {
        _tprintf(_T("[SC] OpenService FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    if (!ControlService(hService,
                        Control,
                        &Status))
    {
        _tprintf(_T("[SC] ControlService FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    /* FIXME: lazy hack ;) */
    CopyMemory(&StatusEx, &Status, sizeof(Status));
    StatusEx.dwProcessId = 0;
    StatusEx.dwServiceFlags = 0;

    PrintService(ServiceName,
                 NULL,
                 &StatusEx,
                 FALSE);

done:
    if (!bResult)
        ReportLastError();

    if (hService)
        CloseServiceHandle(hService);

    if (hSCManager)
        CloseServiceHandle(hSCManager);

    return bResult;
}