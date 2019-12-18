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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  hProgress; int /*<<< orphan*/  hDlg; } ;
typedef  TYPE_1__* PPROGRESS_DATA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ActionThread ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_SERVCON_PROGRESS ; 
 int /*<<< orphan*/  MAKELPARAM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PBM_SETRANGE ; 
 int /*<<< orphan*/  PBM_SETSTEP ; 
 int /*<<< orphan*/  PROGRESS_RANGE ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _beginthreadex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
InitProgressDialog(HWND hDlg,
                   UINT Message,
                   WPARAM wParam,
                   LPARAM lParam)
{
    PPROGRESS_DATA ProgressData = (PPROGRESS_DATA)lParam;
    HANDLE hThread;

    ProgressData->hDlg = hDlg;

    /* Get a handle to the progress bar */
    ProgressData->hProgress = GetDlgItem(hDlg,
                                         IDC_SERVCON_PROGRESS);
    if (!ProgressData->hProgress)
        return FALSE;

    /* Set the progress bar range */
    SendMessageW(ProgressData->hProgress,
                 PBM_SETRANGE,
                 0,
                 MAKELPARAM(0, PROGRESS_RANGE));

    /* Set the progress bar step */
    SendMessageW(ProgressData->hProgress,
                 PBM_SETSTEP,
                 (WPARAM)1,
                 0);

    /* Create a thread to handle the service control */
    hThread = (HANDLE)_beginthreadex(NULL, 0, &ActionThread, ProgressData, 0, NULL);
    if (!hThread) return FALSE;

    CloseHandle(hThread);

    return TRUE;
}