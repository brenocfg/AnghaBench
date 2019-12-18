#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {int /*<<< orphan*/  idFrom; int /*<<< orphan*/  code; int /*<<< orphan*/  hwndFrom; } ;
struct TYPE_10__ {int /*<<< orphan*/  rc; int /*<<< orphan*/  hdc; TYPE_1__ hdr; } ;
struct TYPE_13__ {TYPE_2__ nmcd; int /*<<< orphan*/  uDrawFlags; } ;
struct TYPE_12__ {int nCurrentTool; TYPE_3__* tools; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_11__ {int /*<<< orphan*/  uId; } ;
typedef  TYPE_3__ TTTOOL_INFO ;
typedef  TYPE_4__ TOOLTIPS_INFO ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_5__ NMTTCUSTOMDRAW ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  NM_CUSTOMDRAW ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_5__*,int) ; 

__attribute__((used)) static void
TOOLTIPS_customdraw_fill(const TOOLTIPS_INFO *infoPtr, NMTTCUSTOMDRAW *lpnmttcd,
                         HDC hdc, const RECT *rcBounds, UINT uFlags)
{
    ZeroMemory(lpnmttcd, sizeof(NMTTCUSTOMDRAW));
    lpnmttcd->uDrawFlags = uFlags;
    lpnmttcd->nmcd.hdr.hwndFrom = infoPtr->hwndSelf;
    lpnmttcd->nmcd.hdr.code     = NM_CUSTOMDRAW;
    if (infoPtr->nCurrentTool != -1) {
        TTTOOL_INFO *toolPtr = &infoPtr->tools[infoPtr->nCurrentTool];
        lpnmttcd->nmcd.hdr.idFrom = toolPtr->uId;
    }
    lpnmttcd->nmcd.hdc = hdc;
    lpnmttcd->nmcd.rc = *rcBounds;
    /* FIXME - dwItemSpec, uItemState, lItemlParam */
}