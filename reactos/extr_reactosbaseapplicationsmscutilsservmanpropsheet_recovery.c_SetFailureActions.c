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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  cActions; } ;
typedef  TYPE_1__ SERVICE_FAILURE_ACTIONS ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  FailureActions ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CB_GETCURSEL ; 
 scalar_t__ FALSE ; 
 scalar_t__ IDC_FIRST_FAILURE ; 
 scalar_t__ IDC_SUBSEQUENT_FAILURES ; 
 scalar_t__ SendDlgItemMessageW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 

__attribute__((used)) static
VOID
SetFailureActions(
    HWND hwndDlg)
{
    SERVICE_FAILURE_ACTIONS FailureActions;
    BOOL bRestartService = FALSE;
    BOOL bRunProgram = FALSE;
    BOOL bRebootComputer = FALSE;
    INT id, index;

    ZeroMemory(&FailureActions, sizeof(FailureActions));

    /* Count the number of valid failure actions */
    for (id = IDC_FIRST_FAILURE; id <= IDC_SUBSEQUENT_FAILURES; id++)
    {
        index = SendDlgItemMessageW(hwndDlg,
                                    id,
                                    CB_GETCURSEL,
                                    0,
                                    0);
        switch (index)
        {
            case 1: /* Restart Service */
                bRestartService = TRUE;
                FailureActions.cActions++;
                break;

            case 2: /* Run Program */
                bRunProgram = TRUE;
                FailureActions.cActions++;
                break;

            case 3: /* Reboot Computer */
                bRebootComputer = TRUE;
                FailureActions.cActions++;
                break;
        }
    }

    if (bRestartService)
    {
        // IDC_RESTART_TIME
    }

    if (bRunProgram)
    {
        // IDC_RESTART_TIME
    }

    if (bRebootComputer)
    {
        // IDC_RESTART_TIME
    }


#if 0
typedef struct _SERVICE_FAILURE_ACTIONS {
  DWORD     dwResetPeriod;
  LPTSTR    lpRebootMsg;
  LPTSTR    lpCommand;
  DWORD     cActions;
  SC_ACTION *lpsaActions;
} SERVICE_FAILURE_ACTIONS, *LPSERVICE_FAILURE_ACTIONS;
#endif
}