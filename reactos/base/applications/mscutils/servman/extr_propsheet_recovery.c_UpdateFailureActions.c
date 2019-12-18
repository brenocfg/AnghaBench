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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PRECOVERYDATA ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CB_GETCURSEL ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ IDC_ADD_FAILCOUNT ; 
 scalar_t__ IDC_FIRST_FAILURE ; 
 scalar_t__ IDC_RESTART_OPTIONS ; 
 scalar_t__ IDC_RESTART_TEXT1 ; 
 scalar_t__ IDC_RESTART_TEXT2 ; 
 scalar_t__ IDC_RUN_GROUPBOX ; 
 scalar_t__ IDC_SUBSEQUENT_FAILURES ; 
 scalar_t__ SendDlgItemMessageW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
VOID
UpdateFailureActions(
    HWND hwndDlg,
    PRECOVERYDATA pRecoveryData)
{
    INT id, index;
    BOOL bRestartService = FALSE;
    BOOL bRunProgram = FALSE;
    BOOL bRebootComputer = FALSE;

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
                break;

            case 2: /* Run Program */
                bRunProgram = TRUE;
                break;

            case 3: /* Reboot Computer */
                bRebootComputer = TRUE;
                break;
        }
    }

    for (id = IDC_RESTART_TEXT1; id <= IDC_RESTART_TEXT2; id++)
         EnableWindow(GetDlgItem(hwndDlg, id), bRestartService);

    for (id = IDC_RUN_GROUPBOX; id <= IDC_ADD_FAILCOUNT; id++)
         EnableWindow(GetDlgItem(hwndDlg, id), bRunProgram);

    EnableWindow(GetDlgItem(hwndDlg, IDC_RESTART_OPTIONS), bRebootComputer);
}