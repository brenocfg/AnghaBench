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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BM_GETCHECK ; 
 scalar_t__ BST_CHECKED ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_AUTOSYNC ; 
 int /*<<< orphan*/  IDC_NEXTSYNC ; 
 int /*<<< orphan*/  IDC_SERVERLIST ; 
 int /*<<< orphan*/  IDC_SERVERTEXT ; 
 int /*<<< orphan*/  IDC_SUCSYNC ; 
 int /*<<< orphan*/  IDC_UPDATEBUTTON ; 
 scalar_t__ SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static VOID
EnableDialogText(HWND hwnd)
{
    BOOL bChecked;
    UINT uCheck;

    uCheck = (UINT)SendDlgItemMessageW(hwnd, IDC_AUTOSYNC, BM_GETCHECK, 0, 0);
    bChecked = (uCheck == BST_CHECKED) ? TRUE : FALSE;

    EnableWindow(GetDlgItem(hwnd, IDC_SERVERTEXT), bChecked);
    EnableWindow(GetDlgItem(hwnd, IDC_SERVERLIST), bChecked);
    EnableWindow(GetDlgItem(hwnd, IDC_UPDATEBUTTON), bChecked);
    EnableWindow(GetDlgItem(hwnd, IDC_SUCSYNC), bChecked);
    EnableWindow(GetDlgItem(hwnd, IDC_NEXTSYNC), bChecked);
}