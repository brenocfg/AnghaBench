#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int iRow; scalar_t__ cxEffective; int /*<<< orphan*/  cx; int /*<<< orphan*/  cxMinBand; } ;
struct TYPE_12__ {int dwStyle; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  TYPE_2__ REBAR_BAND ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int,int,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int RBS_VARHEIGHT ; 
 TYPE_2__* REBAR_FindBandToGrow (TYPE_1__ const*,int,int) ; 
 TYPE_2__* REBAR_GetBand (TYPE_1__ const*,int) ; 
 int REBAR_SetBandsHeight (TYPE_1__ const*,int,int,int) ; 
 int /*<<< orphan*/  REBAR_SetRowRectsX (TYPE_1__ const*,int,int) ; 
 int REBAR_ShrinkBandsRTL (TYPE_1__ const*,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ SEP_WIDTH ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 scalar_t__ max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int next_visible (TYPE_1__ const*,int) ; 

__attribute__((used)) static void REBAR_LayoutRow(const REBAR_INFO *infoPtr, int iBeginBand, int iEndBand, int cx, int *piRow, int *pyPos)
{
    REBAR_BAND *lpBand;
    int i, extra;
    int width = 0;

    TRACE("Adjusting row [%d;%d). Width: %d\n", iBeginBand, iEndBand, cx);
    for (i = iBeginBand; i < iEndBand; i++)
        REBAR_GetBand(infoPtr, i)->iRow = *piRow;

    /* compute the extra space */
    for (i = iBeginBand; i < iEndBand; i = next_visible(infoPtr, i))
    {
        lpBand = REBAR_GetBand(infoPtr, i);
        if (i > iBeginBand)
            width += SEP_WIDTH;
        lpBand->cxEffective = max(lpBand->cxMinBand, lpBand->cx);
        width += lpBand->cxEffective;
    }

    extra = cx - width;
    TRACE("Extra space: %d\n", extra);
    if (extra < 0) {
        int ret = REBAR_ShrinkBandsRTL(infoPtr, iBeginBand, iEndBand, -extra, FALSE);
        if (ret > 0 && next_visible(infoPtr, iBeginBand) != iEndBand)  /* one band may be longer than expected... */
            ERR("Error layouting row %d - couldn't shrink for %d pixels (%d total shrink)\n", *piRow, ret, -extra);
    } else
    if (extra > 0) {
        lpBand = REBAR_FindBandToGrow(infoPtr, iBeginBand, iEndBand);
        lpBand->cxEffective += extra;
    }

    REBAR_SetRowRectsX(infoPtr, iBeginBand, iEndBand);
    if (infoPtr->dwStyle & RBS_VARHEIGHT)
    {
        if (*piRow > 0)
            *pyPos += SEP_WIDTH;
        *pyPos = REBAR_SetBandsHeight(infoPtr, iBeginBand, iEndBand, *pyPos);
    }
    (*piRow)++;
}