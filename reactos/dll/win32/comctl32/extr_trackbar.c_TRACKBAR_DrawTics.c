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
struct TYPE_8__ {int member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_10__ {int /*<<< orphan*/  lopnColor; int /*<<< orphan*/  member_2; TYPE_1__ member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {int dwStyle; unsigned int uNumTics; int /*<<< orphan*/  lSelMax; int /*<<< orphan*/  lSelMin; int /*<<< orphan*/  lRangeMax; int /*<<< orphan*/  lRangeMin; int /*<<< orphan*/ * tics; int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_2__ TRACKBAR_INFO ;
typedef  TYPE_3__ LOGPEN ;
typedef  scalar_t__ HTHEME ;
typedef  scalar_t__ HPEN ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_3DDKSHADOW ; 
 scalar_t__ CreatePenIndirect (TYPE_3__*) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetThemeColor (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GetWindowTheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PS_SOLID ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int TBS_ENABLESELRANGE ; 
 int TBS_VERT ; 
 int TIC_EDGE ; 
 int TIC_SELECTIONMARKMAX ; 
 int TIC_SELECTIONMARKMIN ; 
 int TKP_TICS ; 
 int TKP_TICSVERT ; 
 int /*<<< orphan*/  TMT_COLOR ; 
 int /*<<< orphan*/  TRACKBAR_DrawTic (TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ TRACKBAR_HasSelection (TYPE_2__ const*) ; 
 int /*<<< orphan*/  TSS_NORMAL ; 

__attribute__((used)) static void
TRACKBAR_DrawTics (const TRACKBAR_INFO *infoPtr, HDC hdc)
{
    unsigned int i;
    int ticFlags = infoPtr->dwStyle & 0x0f;
    LOGPEN ticPen = { PS_SOLID, {1, 0}, GetSysColor (COLOR_3DDKSHADOW) };
    HPEN hOldPen, hTicPen;
    HTHEME theme = GetWindowTheme (infoPtr->hwndSelf);
    
    if (theme)
    {
        int part = (infoPtr->dwStyle & TBS_VERT) ? TKP_TICSVERT : TKP_TICS;
        GetThemeColor (theme, part, TSS_NORMAL, TMT_COLOR, &ticPen.lopnColor);
    }
    /* create the pen to draw the tics with */
    hTicPen = CreatePenIndirect(&ticPen);
    hOldPen = hTicPen ? SelectObject(hdc, hTicPen) : 0;

    /* actually draw the tics */
    for (i=0; i<infoPtr->uNumTics; i++)
        TRACKBAR_DrawTic (infoPtr, hdc, infoPtr->tics[i], ticFlags);

    TRACKBAR_DrawTic (infoPtr, hdc, infoPtr->lRangeMin, ticFlags | TIC_EDGE);
    TRACKBAR_DrawTic (infoPtr, hdc, infoPtr->lRangeMax, ticFlags | TIC_EDGE);

    if ((infoPtr->dwStyle & TBS_ENABLESELRANGE) && TRACKBAR_HasSelection(infoPtr)) {
        TRACKBAR_DrawTic (infoPtr, hdc, infoPtr->lSelMin,
                          ticFlags | TIC_SELECTIONMARKMIN);
        TRACKBAR_DrawTic (infoPtr, hdc, infoPtr->lSelMax,
                          ticFlags | TIC_SELECTIONMARKMAX);
    }
    
    /* clean up the pen, if we created one */
    if (hTicPen) {
	SelectObject(hdc, hOldPen);
	DeleteObject(hTicPen);
    }
}