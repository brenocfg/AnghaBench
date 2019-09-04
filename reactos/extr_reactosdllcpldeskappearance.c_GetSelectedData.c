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
typedef  int /*<<< orphan*/ * PVOID ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ CB_ERR ; 
 int /*<<< orphan*/  CB_GETCURSEL ; 
 int /*<<< orphan*/  CB_GETITEMDATA ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PVOID
GetSelectedData(HWND hwndDlg, int nIDDlgItem)
{
    HWND hwndCombo;
    INT sel;

    hwndCombo = GetDlgItem(hwndDlg, nIDDlgItem);
    sel = SendMessage(hwndCombo, CB_GETCURSEL, 0, 0);
    if (sel == CB_ERR)
        return NULL;
    return (PVOID)SendMessage(hwndCombo, CB_GETITEMDATA, (WPARAM)sel, 0);
}