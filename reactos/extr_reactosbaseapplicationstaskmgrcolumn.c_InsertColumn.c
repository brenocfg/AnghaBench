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
struct TYPE_3__ {int mask; int fmt; int cx; int iSubItem; scalar_t__ pszText; } ;
typedef  TYPE_1__ LVCOLUMN ;
typedef  scalar_t__ LPWSTR ;
typedef  scalar_t__ LPCWSTR ;

/* Variables and functions */
 int LVCF_FMT ; 
 int LVCF_SUBITEM ; 
 int LVCF_TEXT ; 
 int LVCF_WIDTH ; 
 int ListView_InsertColumn (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  hProcessPageListCtrl ; 

__attribute__((used)) static int InsertColumn(int nCol, LPCWSTR lpszColumnHeading, int nFormat, int nWidth, int nSubItem)
{
    LVCOLUMN  column;

    column.mask = LVCF_TEXT|LVCF_FMT;
    column.pszText = (LPWSTR)lpszColumnHeading;
    column.fmt = nFormat;

    if (nWidth != -1)
    {
        column.mask |= LVCF_WIDTH;
        column.cx = nWidth;
    }

    if (nSubItem != -1)
    {
        column.mask |= LVCF_SUBITEM;
        column.iSubItem = nSubItem;
    }

    return ListView_InsertColumn(hProcessPageListCtrl, nCol, &column);
}