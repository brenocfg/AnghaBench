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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_CBX_STARTUP_ITEM ; 
 int /*<<< orphan*/  IDC_CBX_SYSTEM_INI ; 
 int /*<<< orphan*/  IDC_CBX_SYSTEM_SERVICE ; 

VOID
EnableCheckboxControls(HWND hDlg, BOOL bEnable)
{
    EnableWindow(GetDlgItem(hDlg, IDC_CBX_SYSTEM_INI), bEnable);
    EnableWindow(GetDlgItem(hDlg, IDC_CBX_SYSTEM_SERVICE), bEnable);
    EnableWindow(GetDlgItem(hDlg, IDC_CBX_STARTUP_ITEM), bEnable);
}