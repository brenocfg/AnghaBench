#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szTemp ;
typedef  int WPARAM ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  dwIdsName; int /*<<< orphan*/  size; } ;
struct TYPE_6__ {int* ColumnOrderArray; int /*<<< orphan*/ * ColumnSizeArray; int /*<<< orphan*/ * Columns; } ;
struct TYPE_5__ {int mask; int cchTextMax; int /*<<< orphan*/  cxy; int /*<<< orphan*/ * pszText; } ;
typedef  int LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_1__ HDITEM ;

/* Variables and functions */
 int COLUMN_NMAX ; 
 TYPE_4__* ColumnPresets ; 
 int /*<<< orphan*/  FALSE ; 
 int HDI_TEXT ; 
 int HDI_WIDTH ; 
 int /*<<< orphan*/  HDM_GETITEM ; 
 int /*<<< orphan*/  HDM_GETITEMCOUNT ; 
 int /*<<< orphan*/  HDM_GETORDERARRAY ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__ TaskManagerSettings ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/  hProcessPageHeaderCtrl ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void SaveColumnSettings(void)
{
    HDITEM        hditem;
    int           i, n;
    WCHAR         text[260];
    WCHAR         szTemp[256];
    LRESULT       size;

    /* Reset column data */
    for (i=0; i<COLUMN_NMAX; i++) {
        TaskManagerSettings.ColumnOrderArray[i] = i;
        TaskManagerSettings.Columns[i] = FALSE;
        TaskManagerSettings.ColumnSizeArray[i] = ColumnPresets[i].size;
    }

    /* Get header order */
    size = SendMessageW(hProcessPageHeaderCtrl, HDM_GETITEMCOUNT, 0, 0);
    SendMessageW(hProcessPageHeaderCtrl, HDM_GETORDERARRAY, (WPARAM) size, (LPARAM) &TaskManagerSettings.ColumnOrderArray);

    /* Get visible columns */
    for (i = 0; i < SendMessageW(hProcessPageHeaderCtrl, HDM_GETITEMCOUNT, 0, 0); i++) {
        memset(&hditem, 0, sizeof(HDITEM));

        hditem.mask = HDI_TEXT|HDI_WIDTH;
        hditem.pszText = text;
        hditem.cchTextMax = 260;

        SendMessageW(hProcessPageHeaderCtrl, HDM_GETITEM, i, (LPARAM) &hditem);

        for (n = 0; n < COLUMN_NMAX; n++) {
            LoadStringW(hInst, ColumnPresets[n].dwIdsName, szTemp, sizeof(szTemp)/sizeof(WCHAR));
            if (_wcsicmp(text, szTemp) == 0)
            {
                TaskManagerSettings.Columns[n] = TRUE;
                TaskManagerSettings.ColumnSizeArray[n] = hditem.cxy;
            }
        }
    }
}