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
typedef  int /*<<< orphan*/  szTemp ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  dwIdsName; } ;
struct TYPE_3__ {int /*<<< orphan*/  ColumnOrderArray; int /*<<< orphan*/ * ColumnSizeArray; scalar_t__* Columns; } ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;

/* Variables and functions */
 unsigned int COLUMN_NMAX ; 
 TYPE_2__* ColumnPresets ; 
 int /*<<< orphan*/  HDM_GETITEMCOUNT ; 
 int /*<<< orphan*/  HDM_SETORDERARRAY ; 
 int /*<<< orphan*/  InsertColumn (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LVCFMT_LEFT ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ TaskManagerSettings ; 
 int /*<<< orphan*/  UpdateColumnDataHints () ; 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/  hProcessPageHeaderCtrl ; 

void AddColumns(void)
{
    LRESULT       size;
    WCHAR         szTemp[256];
    unsigned int  n;

    for (n=0; n<COLUMN_NMAX; n++) {
        if (TaskManagerSettings.Columns[n]) {
            LoadStringW(hInst, ColumnPresets[n].dwIdsName, szTemp, sizeof(szTemp)/sizeof(WCHAR));
            InsertColumn(n, szTemp, LVCFMT_LEFT, TaskManagerSettings.ColumnSizeArray[n], -1);
        }
    }

    size = SendMessageW(hProcessPageHeaderCtrl, HDM_GETITEMCOUNT, 0, 0);
    SendMessageW(hProcessPageHeaderCtrl, HDM_SETORDERARRAY, (WPARAM) size, (LPARAM) &TaskManagerSettings.ColumnOrderArray);

    UpdateColumnDataHints();
}