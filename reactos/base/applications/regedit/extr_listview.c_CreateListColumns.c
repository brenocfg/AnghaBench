#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int mask; int iSubItem; int cx; int /*<<< orphan*/  fmt; int /*<<< orphan*/ * pszText; } ;
typedef  TYPE_1__ LVCOLUMN ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  COUNT_OF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IDS_LIST_COLUMN_FIRST ; 
 int LVCF_FMT ; 
 int LVCF_SUBITEM ; 
 int LVCF_TEXT ; 
 int LVCF_WIDTH ; 
 int ListView_InsertColumn (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_LIST_COLUMNS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * column_alignment ; 
 int* default_column_widths ; 
 int /*<<< orphan*/  hInst ; 

__attribute__((used)) static BOOL CreateListColumns(HWND hWndListView, INT cxTotal)
{
    WCHAR szText[50];
    int index;
    LVCOLUMN lvC;

    /* Create columns. */
    lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvC.pszText = szText;

    /* Load the column labels from the resource file. */
    for (index = 0; index < MAX_LIST_COLUMNS; index++)
    {
        lvC.iSubItem = index;
        lvC.cx = (cxTotal * default_column_widths[index]) / 100;
        lvC.fmt = column_alignment[index];
        LoadStringW(hInst, IDS_LIST_COLUMN_FIRST + index, szText, COUNT_OF(szText));
        if (ListView_InsertColumn(hWndListView, index, &lvC) == -1) return FALSE;
    }
    return TRUE;
}