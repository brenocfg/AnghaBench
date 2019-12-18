#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct TYPE_3__ {int* ColumnOrderArray; int /*<<< orphan*/ * ColumnSizeArray; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddColumns () ; 
 int COLUMN_NMAX ; 
 TYPE_2__* ColumnPresets ; 
 int /*<<< orphan*/  ColumnsDialogWndProc ; 
 scalar_t__ DialogBoxW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Header_GetItemCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDD_COLUMNS_DIALOG ; 
 scalar_t__ IDOK ; 
 int /*<<< orphan*/  ListView_DeleteColumn (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 TYPE_1__ TaskManagerSettings ; 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/  hMainWnd ; 
 int /*<<< orphan*/  hProcessPageHeaderCtrl ; 
 int /*<<< orphan*/  hProcessPageListCtrl ; 

void ProcessPage_OnViewSelectColumns(void)
{
    int  i;

    if (DialogBoxW(hInst, MAKEINTRESOURCEW(IDD_COLUMNS_DIALOG), hMainWnd, ColumnsDialogWndProc) == IDOK)
    {
        for (i=Header_GetItemCount(hProcessPageHeaderCtrl)-1; i>=0; i--)
        {
            (void)ListView_DeleteColumn(hProcessPageListCtrl, i);
        }

        for (i=0; i<COLUMN_NMAX; i++) {
            TaskManagerSettings.ColumnOrderArray[i] = i;
            TaskManagerSettings.ColumnSizeArray[i] = ColumnPresets[i].size;
        }

        AddColumns();
    }
}