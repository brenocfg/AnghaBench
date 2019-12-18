#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_10__ {int /*<<< orphan*/  lParamNM; int /*<<< orphan*/  rc; int /*<<< orphan*/  lParam; int /*<<< orphan*/  wID; scalar_t__ uBand; } ;
struct TYPE_9__ {int /*<<< orphan*/  rcChevron; int /*<<< orphan*/  fDraw; int /*<<< orphan*/  lParam; int /*<<< orphan*/  wID; } ;
struct TYPE_8__ {scalar_t__ uNumBands; int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  TYPE_2__ REBAR_BAND ;
typedef  TYPE_3__ NMREBARCHEVRON ;
typedef  int /*<<< orphan*/  NMHDR ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;

/* Variables and functions */
 int /*<<< orphan*/  DRAW_CHEVRONPUSHED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBN_CHEVRONPUSHED ; 
 int RDW_ERASE ; 
 int RDW_INVALIDATE ; 
 int RDW_UPDATENOW ; 
 TYPE_2__* REBAR_GetBand (TYPE_1__ const*,scalar_t__) ; 
 int /*<<< orphan*/  REBAR_Notify (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedrawWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
REBAR_PushChevron(const REBAR_INFO *infoPtr, UINT uBand, LPARAM lParam)
{
    if (uBand < infoPtr->uNumBands)
    {
        NMREBARCHEVRON nmrbc;
        REBAR_BAND *lpBand = REBAR_GetBand(infoPtr, uBand);

        TRACE("Pressed chevron on band %u\n", uBand);

        /* redraw chevron in pushed state */
        lpBand->fDraw |= DRAW_CHEVRONPUSHED;
        RedrawWindow(infoPtr->hwndSelf, &lpBand->rcChevron,0,
          RDW_ERASE|RDW_INVALIDATE|RDW_UPDATENOW);

        /* notify app so it can display a popup menu or whatever */
        nmrbc.uBand = uBand;
        nmrbc.wID = lpBand->wID;
        nmrbc.lParam = lpBand->lParam;
        nmrbc.rc = lpBand->rcChevron;
        nmrbc.lParamNM = lParam;
        REBAR_Notify((NMHDR*)&nmrbc, infoPtr, RBN_CHEVRONPUSHED);

        /* redraw chevron in previous state */
        lpBand->fDraw &= ~DRAW_CHEVRONPUSHED;
        InvalidateRect(infoPtr->hwndSelf, &lpBand->rcChevron, TRUE);

        return TRUE;
    }
    return FALSE;
}