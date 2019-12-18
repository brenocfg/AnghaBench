#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ nHotItem; int /*<<< orphan*/  clrText; int /*<<< orphan*/  clrTextBk; } ;
struct TYPE_11__ {scalar_t__ iItem; int state; int /*<<< orphan*/  lParam; int /*<<< orphan*/  iSubItem; } ;
struct TYPE_9__ {scalar_t__ dwItemSpec; int /*<<< orphan*/  lItemlParam; int /*<<< orphan*/  uItemState; int /*<<< orphan*/  rc; int /*<<< orphan*/  hdc; } ;
struct TYPE_10__ {TYPE_1__ nmcd; int /*<<< orphan*/  iSubItem; int /*<<< orphan*/  clrText; int /*<<< orphan*/  clrTextBk; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_2__ NMLVCUSTOMDRAW ;
typedef  TYPE_3__ LVITEMW ;
typedef  TYPE_4__ LISTVIEW_INFO ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CDIS_FOCUS ; 
 int /*<<< orphan*/  CDIS_HOT ; 
 int /*<<< orphan*/  CDIS_SELECTED ; 
 int LVIS_FOCUSED ; 
 int LVIS_SELECTED ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 

__attribute__((used)) static void customdraw_fill(NMLVCUSTOMDRAW *lpnmlvcd, const LISTVIEW_INFO *infoPtr, HDC hdc,
			    const RECT *rcBounds, const LVITEMW *lplvItem)
{
    ZeroMemory(lpnmlvcd, sizeof(NMLVCUSTOMDRAW));
    lpnmlvcd->nmcd.hdc = hdc;
    lpnmlvcd->nmcd.rc = *rcBounds;
    lpnmlvcd->clrTextBk = infoPtr->clrTextBk;
    lpnmlvcd->clrText   = infoPtr->clrText;
    if (!lplvItem) return;
    lpnmlvcd->nmcd.dwItemSpec = lplvItem->iItem + 1;
    lpnmlvcd->iSubItem = lplvItem->iSubItem;
    if (lplvItem->state & LVIS_SELECTED) lpnmlvcd->nmcd.uItemState |= CDIS_SELECTED;
    if (lplvItem->state & LVIS_FOCUSED) lpnmlvcd->nmcd.uItemState |= CDIS_FOCUS;
    if (lplvItem->iItem == infoPtr->nHotItem) lpnmlvcd->nmcd.uItemState |= CDIS_HOT;
    lpnmlvcd->nmcd.lItemlParam = lplvItem->lParam;
}