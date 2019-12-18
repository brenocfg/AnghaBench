#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ hwndFrom; int /*<<< orphan*/  idFrom; int /*<<< orphan*/  code; } ;
struct TYPE_14__ {scalar_t__ hwndSelf; scalar_t__ TLbtnState; scalar_t__ BRbtnState; int dwStyle; int /*<<< orphan*/  hwndNotify; void* bCapture; int /*<<< orphan*/  clrBk; } ;
struct TYPE_13__ {scalar_t__ y; scalar_t__ x; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ POINT ;
typedef  TYPE_2__ PAGER_INFO ;
typedef  TYPE_3__ NMHDR ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ClientToScreen (scalar_t__,TYPE_1__*) ; 
 void* FALSE ; 
 int /*<<< orphan*/  GWLP_ID ; 
 scalar_t__ GetCapture () ; 
 int /*<<< orphan*/  GetWindowDC (scalar_t__) ; 
 int /*<<< orphan*/  GetWindowLongPtrW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ IsWindow (scalar_t__) ; 
 int /*<<< orphan*/  KillTimer (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*,int) ; 
 int /*<<< orphan*/  NM_RELEASEDCAPTURE ; 
 int /*<<< orphan*/  PAGER_DrawButton (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,scalar_t__) ; 
 int /*<<< orphan*/  PAGER_GetButtonRects (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ PAGER_HitTest (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ PGB_BOTTOMORRIGHT ; 
 scalar_t__ PGB_TOPORLEFT ; 
 scalar_t__ PGF_GRAYED ; 
 scalar_t__ PGF_HOT ; 
 void* PGF_INVISIBLE ; 
 scalar_t__ PGF_NORMAL ; 
 int PGS_AUTOSCROLL ; 
 int PGS_HORZ ; 
 scalar_t__ PtInRect (int /*<<< orphan*/ *,TYPE_1__) ; 
 int RDW_FRAME ; 
 int RDW_INVALIDATE ; 
 int /*<<< orphan*/  RedrawWindow (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ReleaseCapture () ; 
 int /*<<< orphan*/  ReleaseDC (scalar_t__,int /*<<< orphan*/ ) ; 
 int SWP_FRAMECHANGED ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOMOVE ; 
 int SWP_NOSIZE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCapture (scalar_t__) ; 
 int /*<<< orphan*/  SetTimer (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowPos (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TIMERID1 ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,...) ; 
 void* TRUE ; 
 int /*<<< orphan*/  WM_NOTIFY ; 
 scalar_t__ WindowFromPoint (TYPE_1__) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static LRESULT
PAGER_MouseMove (PAGER_INFO* infoPtr, INT keys, INT x, INT y)
{
    POINT clpt, pt;
    RECT wnrect;
    BOOL topLeft = FALSE;
    INT btnstate = 0;
    INT hit;
    HDC hdc;

    pt.x = x;
    pt.y = y;

    TRACE("[%p] to (%d,%d)\n", infoPtr->hwndSelf, x, y);
    ClientToScreen(infoPtr->hwndSelf, &pt);
    GetWindowRect(infoPtr->hwndSelf, &wnrect);
    if (PtInRect(&wnrect, pt)) {
	RECT topleft, bottomright, *rect = NULL;

	PAGER_GetButtonRects(infoPtr, &topleft, &bottomright, FALSE);

	clpt = pt;
	MapWindowPoints(0, infoPtr->hwndSelf, &clpt, 1);
	hit = PAGER_HitTest(infoPtr, &clpt);
	if ((hit == PGB_TOPORLEFT) && (infoPtr->TLbtnState == PGF_NORMAL))
	{
	    topLeft = TRUE;
	    rect = &topleft;
	    infoPtr->TLbtnState = PGF_HOT;
	    btnstate = infoPtr->TLbtnState;
	}
	else if ((hit == PGB_BOTTOMORRIGHT) && (infoPtr->BRbtnState == PGF_NORMAL))
	{
	    topLeft = FALSE;
	    rect = &bottomright;
	    infoPtr->BRbtnState = PGF_HOT;
	    btnstate = infoPtr->BRbtnState;
	}

	/* If in one of the buttons the capture and draw buttons */
	if (rect)
	{
            TRACE("[%p] draw btn (%s), Capture %s, style %08x\n",
                  infoPtr->hwndSelf, wine_dbgstr_rect(rect),
		  (infoPtr->bCapture) ? "TRUE" : "FALSE",
		  infoPtr->dwStyle);
	    if (!infoPtr->bCapture)
	    {
	        TRACE("[%p] SetCapture\n", infoPtr->hwndSelf);
	        SetCapture(infoPtr->hwndSelf);
	        infoPtr->bCapture = TRUE;
	    }
	    if (infoPtr->dwStyle & PGS_AUTOSCROLL)
		SetTimer(infoPtr->hwndSelf, TIMERID1, 0x3e, 0);
	    hdc = GetWindowDC(infoPtr->hwndSelf);
	    /* OffsetRect(wnrect, 0 | 1, 0 | 1) */
	    PAGER_DrawButton(hdc, infoPtr->clrBk, *rect,
			     infoPtr->dwStyle & PGS_HORZ, topLeft, btnstate);
	    ReleaseDC(infoPtr->hwndSelf, hdc);
	    return 0;
	}
    }

    /* If we think we are captured, then do release */
    if (infoPtr->bCapture && (WindowFromPoint(pt) != infoPtr->hwndSelf))
    {
    	NMHDR nmhdr;

        infoPtr->bCapture = FALSE;

        if (GetCapture() == infoPtr->hwndSelf)
        {
            ReleaseCapture();

            if (infoPtr->TLbtnState == PGF_GRAYED)
            {
                infoPtr->TLbtnState = PGF_INVISIBLE;
                SetWindowPos(infoPtr->hwndSelf, 0, 0, 0, 0, 0,
                             SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE |
                             SWP_NOZORDER | SWP_NOACTIVATE);
            }
            else if (infoPtr->TLbtnState == PGF_HOT)
            {
        	infoPtr->TLbtnState = PGF_NORMAL;
        	/* FIXME: just invalidate button rect */
                RedrawWindow(infoPtr->hwndSelf, NULL, NULL, RDW_FRAME | RDW_INVALIDATE);
            }

            if (infoPtr->BRbtnState == PGF_GRAYED)
            {
                infoPtr->BRbtnState = PGF_INVISIBLE;
                SetWindowPos(infoPtr->hwndSelf, 0, 0, 0, 0, 0,
                             SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE |
                             SWP_NOZORDER | SWP_NOACTIVATE);
            }
            else if (infoPtr->BRbtnState == PGF_HOT)
            {
        	infoPtr->BRbtnState = PGF_NORMAL;
        	/* FIXME: just invalidate button rect */
                RedrawWindow(infoPtr->hwndSelf, NULL, NULL, RDW_FRAME | RDW_INVALIDATE);
            }

            /* Notify parent of released mouse capture */
        	memset(&nmhdr, 0, sizeof(NMHDR));
        	nmhdr.hwndFrom = infoPtr->hwndSelf;
        	nmhdr.idFrom   = GetWindowLongPtrW(infoPtr->hwndSelf, GWLP_ID);
        	nmhdr.code = NM_RELEASEDCAPTURE;
		SendMessageW(infoPtr->hwndNotify, WM_NOTIFY, nmhdr.idFrom, (LPARAM)&nmhdr);
        }
        if (IsWindow(infoPtr->hwndSelf))
            KillTimer(infoPtr->hwndSelf, TIMERID1);
    }
    return 0;
}