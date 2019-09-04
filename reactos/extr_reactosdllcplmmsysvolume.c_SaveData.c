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
typedef  int /*<<< orphan*/  HWND ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ BST_CHECKED ; 
 int /*<<< orphan*/  IDC_ICON_IN_TASKBAR ; 
 scalar_t__ IsDlgButtonChecked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSystrayVolumeIconState (int) ; 

VOID
SaveData(HWND hwndDlg)
{
    BOOL bShowIcon;

    bShowIcon = (IsDlgButtonChecked(hwndDlg, IDC_ICON_IN_TASKBAR) == BST_CHECKED);

    SetSystrayVolumeIconState(bShowIcon);
}