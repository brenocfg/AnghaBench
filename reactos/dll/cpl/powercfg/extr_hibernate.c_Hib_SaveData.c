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
typedef  int /*<<< orphan*/  bHibernate ;
typedef  int /*<<< orphan*/  INT_PTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ BST_CHECKED ; 
 scalar_t__ CallNtPowerInformation (int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Hib_InitDialog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_HIBERNATEFILE ; 
 scalar_t__ IsDlgButtonChecked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  SystemReserveHiberFile ; 
 int /*<<< orphan*/  TRUE ; 

INT_PTR
Hib_SaveData(HWND hwndDlg)
{
    BOOLEAN bHibernate;

    bHibernate = (BOOLEAN)(IsDlgButtonChecked(hwndDlg, IDC_HIBERNATEFILE) == BST_CHECKED);

    if (CallNtPowerInformation(SystemReserveHiberFile, &bHibernate, sizeof(bHibernate), NULL, 0) == STATUS_SUCCESS)
    {
        Hib_InitDialog(hwndDlg);
        return TRUE;
    }

    return FALSE;
}