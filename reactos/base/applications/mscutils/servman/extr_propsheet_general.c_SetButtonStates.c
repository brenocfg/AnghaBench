#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ UINT ;
struct TYPE_11__ {scalar_t__ dwStartType; } ;
struct TYPE_10__ {int /*<<< orphan*/  Info; TYPE_2__* pService; } ;
struct TYPE_8__ {scalar_t__ dwControlsAccepted; scalar_t__ dwCurrentState; } ;
struct TYPE_9__ {int /*<<< orphan*/  lpServiceName; TYPE_1__ ServiceStatusProcess; } ;
typedef  TYPE_3__* PSERVICEPROPSHEET ;
typedef  TYPE_4__* LPQUERY_SERVICE_CONFIG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int) ; 
 int FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_4__* GetServiceConfig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ IDC_PAUSE ; 
 scalar_t__ IDC_RESUME ; 
 scalar_t__ IDC_START ; 
 scalar_t__ IDC_START_PARAM ; 
 scalar_t__ IDC_STOP ; 
 scalar_t__ SERVICE_ACCEPT_PAUSE_CONTINUE ; 
 scalar_t__ SERVICE_ACCEPT_STOP ; 
 scalar_t__ SERVICE_DISABLED ; 
 scalar_t__ SERVICE_RUNNING ; 
 scalar_t__ SERVICE_STOPPED ; 
 int /*<<< orphan*/  SetMenuAndButtonStates (int /*<<< orphan*/ ) ; 
 int TRUE ; 

__attribute__((used)) static VOID
SetButtonStates(PSERVICEPROPSHEET dlgInfo,
                HWND hwndDlg)
{
    HWND hButton;
    LPQUERY_SERVICE_CONFIG lpServiceConfig;
    DWORD Flags, State;
    UINT i;

    Flags = dlgInfo->pService->ServiceStatusProcess.dwControlsAccepted;
    State = dlgInfo->pService->ServiceStatusProcess.dwCurrentState;

    for (i = IDC_START; i <= IDC_RESUME; i++)
    {
        hButton = GetDlgItem(hwndDlg, i);
        EnableWindow (hButton, FALSE);
    }

    lpServiceConfig = GetServiceConfig(dlgInfo->pService->lpServiceName);
    if (State == SERVICE_STOPPED &&
        lpServiceConfig && lpServiceConfig->dwStartType != SERVICE_DISABLED)
    {
        hButton = GetDlgItem(hwndDlg, IDC_START);
        EnableWindow (hButton, TRUE);
    }
    else if ( (Flags & SERVICE_ACCEPT_STOP) && (State == SERVICE_RUNNING) )
    {
        hButton = GetDlgItem(hwndDlg, IDC_STOP);
        EnableWindow (hButton, TRUE);
    }
    else if ( (Flags & SERVICE_ACCEPT_PAUSE_CONTINUE) && (State == SERVICE_RUNNING) )
    {
        hButton = GetDlgItem(hwndDlg, IDC_PAUSE);
        EnableWindow (hButton, TRUE);
    }

    hButton = GetDlgItem(hwndDlg, IDC_START_PARAM);
    EnableWindow(hButton, (State == SERVICE_STOPPED && lpServiceConfig && lpServiceConfig->dwStartType != SERVICE_DISABLED));

    if (lpServiceConfig)
        HeapFree(GetProcessHeap(), 0, lpServiceConfig);

    /* set the main toolbar */
    SetMenuAndButtonStates(dlgInfo->Info);
}