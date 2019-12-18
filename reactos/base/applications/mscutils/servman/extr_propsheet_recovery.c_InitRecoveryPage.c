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
typedef  scalar_t__ LPWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ AllocAndLoadString (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IDC_FIRST_FAILURE ; 
 int /*<<< orphan*/  IDC_RESET_TIME ; 
 scalar_t__ IDC_RESTART_OPTIONS ; 
 scalar_t__ IDC_RESTART_TEXT1 ; 
 int /*<<< orphan*/  IDC_RESTART_TIME ; 
 int /*<<< orphan*/  IDC_SECOND_FAILURE ; 
 int /*<<< orphan*/  IDC_SUBSEQUENT_FAILURES ; 
 scalar_t__ IDS_NO_ACTION ; 
 scalar_t__ IDS_RESTART_COMPUTER ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  hInstance ; 

__attribute__((used)) static
VOID
InitRecoveryPage(
    HWND hwndDlg)
{
    LPWSTR lpAction;
    INT id;

    for (id = IDS_NO_ACTION; id <= IDS_RESTART_COMPUTER; id++)
    {
        if (AllocAndLoadString(&lpAction,
                               hInstance,
                               id))
        {
            SendDlgItemMessageW(hwndDlg,
                                IDC_FIRST_FAILURE,
                                CB_ADDSTRING,
                                0,
                                (LPARAM)lpAction);

            SendDlgItemMessageW(hwndDlg,
                                IDC_SECOND_FAILURE,
                                CB_ADDSTRING,
                                0,
                                (LPARAM)lpAction);

            SendDlgItemMessageW(hwndDlg,
                                IDC_SUBSEQUENT_FAILURES,
                                CB_ADDSTRING,
                                0,
                                (LPARAM)lpAction);

            LocalFree(lpAction);
        }
    }

    SendDlgItemMessageW(hwndDlg,
                        IDC_FIRST_FAILURE,
                        CB_SETCURSEL,
                        0,
                        0);

    SendDlgItemMessageW(hwndDlg,
                        IDC_SECOND_FAILURE,
                        CB_SETCURSEL,
                        0,
                        0);

    SendDlgItemMessageW(hwndDlg,
                        IDC_SUBSEQUENT_FAILURES,
                        CB_SETCURSEL,
                        0,
                        0);

    SendDlgItemMessageW(hwndDlg,
                        IDC_RESET_TIME,
                        WM_SETTEXT,
                        0,
                        (LPARAM)L"0");

    SendDlgItemMessageW(hwndDlg,
                        IDC_RESTART_TIME,
                        WM_SETTEXT,
                        0,
                        (LPARAM)L"1");

    for (id = IDC_RESTART_TEXT1; id <= IDC_RESTART_OPTIONS; id++)
        EnableWindow(GetDlgItem(hwndDlg, id), FALSE);
}