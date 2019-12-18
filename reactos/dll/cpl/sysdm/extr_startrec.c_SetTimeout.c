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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_STRRECLISTEDIT ; 
 int /*<<< orphan*/  IDC_STRRECLISTUPDWN ; 
 scalar_t__ MAKELONG (short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UDM_SETPOS ; 
 int /*<<< orphan*/  UDM_SETRANGE ; 

__attribute__((used)) static VOID
SetTimeout(HWND hwndDlg, INT Timeout)
{
    if (Timeout == 0)
    {
        EnableWindow(GetDlgItem(hwndDlg, IDC_STRRECLISTUPDWN), FALSE);
        EnableWindow(GetDlgItem(hwndDlg, IDC_STRRECLISTEDIT), FALSE);
    }
    else
    {
        EnableWindow(GetDlgItem(hwndDlg, IDC_STRRECLISTUPDWN), TRUE);
        EnableWindow(GetDlgItem(hwndDlg, IDC_STRRECLISTEDIT), TRUE);
    }
    SendDlgItemMessageW(hwndDlg, IDC_STRRECLISTUPDWN, UDM_SETRANGE, (WPARAM) 0, (LPARAM) MAKELONG((short) 999, 0));
    SendDlgItemMessageW(hwndDlg, IDC_STRRECLISTUPDWN, UDM_SETPOS, (WPARAM) 0, (LPARAM) MAKELONG((short) Timeout, 0));
}