#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int fStyle; scalar_t__ iRow; scalar_t__ cxMinBand; scalar_t__ cxEffective; scalar_t__ cx; } ;
struct TYPE_15__ {scalar_t__ uNumBands; int dwStyle; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  TYPE_2__ REBAR_BAND ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int CCS_VERT ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int RBBS_HIDDEN ; 
 int /*<<< orphan*/  REBAR_CalcHorzBand (TYPE_1__ const*,int,int) ; 
 int /*<<< orphan*/  REBAR_CalcVertBand (TYPE_1__ const*,int,int) ; 
 TYPE_2__* REBAR_GetBand (TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  REBAR_MaximizeBand (TYPE_1__ const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REBAR_MoveChildWindows (TYPE_1__ const*,int,int) ; 
 int /*<<< orphan*/  REBAR_SetRowRectsX (TYPE_1__ const*,int,int) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 int get_row_begin_for_band (TYPE_1__ const*,scalar_t__) ; 
 int get_row_end_for_band (TYPE_1__ const*,scalar_t__) ; 
 int next_visible (TYPE_1__ const*,scalar_t__) ; 
 int prev_visible (TYPE_1__ const*,scalar_t__) ; 

__attribute__((used)) static LRESULT
REBAR_MinimizeBand (const REBAR_INFO *infoPtr, INT iBand)
{
    REBAR_BAND *lpBand;
    int iPrev, iRowBegin, iRowEnd;

    /* A "minimize" band is equivalent to "dragging" the gripper
     * of than band to the right till the band is only the size
     * of the cxHeader.
     */

    /* Validate */
    if (infoPtr->uNumBands == 0 || iBand < 0 || iBand >= infoPtr->uNumBands) {
	/* error !!! */
	ERR("Illegal MinimizeBand, requested=%d, current band count=%d\n",
	      iBand, infoPtr->uNumBands);
      	return FALSE;
    }

    /* compute amount of movement and validate */
    lpBand = REBAR_GetBand(infoPtr, iBand);

    if (lpBand->fStyle & RBBS_HIDDEN)
    {
        /* Windows is buggy and creates a hole/overlap */
        WARN("Ignoring minimize request on a hidden band (%d)\n", iBand);
        return FALSE;
    }

    iPrev = prev_visible(infoPtr, iBand);
    /* if first band in row */
    if (iPrev < 0 || REBAR_GetBand(infoPtr, iPrev)->iRow != lpBand->iRow) {
        int iNext = next_visible(infoPtr, iBand);
        if (iNext < infoPtr->uNumBands && REBAR_GetBand(infoPtr, iNext)->iRow == lpBand->iRow) {
            TRACE("(%d): Minimizing the first band in row is by maximizing the second\n", iBand);
            REBAR_MaximizeBand(infoPtr, iNext, FALSE);
        }
        else
            TRACE("(%d): Only one band in row - nothing to do\n", iBand);
        return TRUE;
    }

    REBAR_GetBand(infoPtr, iPrev)->cxEffective += lpBand->cxEffective - lpBand->cxMinBand;
    REBAR_GetBand(infoPtr, iPrev)->cx = REBAR_GetBand(infoPtr, iPrev)->cxEffective;
    lpBand->cx = lpBand->cxEffective = lpBand->cxMinBand;

    iRowBegin = get_row_begin_for_band(infoPtr, iBand);
    iRowEnd = get_row_end_for_band(infoPtr, iBand);
    REBAR_SetRowRectsX(infoPtr, iRowBegin, iRowEnd);

    if (infoPtr->dwStyle & CCS_VERT)
        REBAR_CalcVertBand(infoPtr, iRowBegin, iRowEnd);
    else
        REBAR_CalcHorzBand(infoPtr, iRowBegin, iRowEnd);
    REBAR_MoveChildWindows(infoPtr, iRowBegin, iRowEnd);
    return FALSE;
}