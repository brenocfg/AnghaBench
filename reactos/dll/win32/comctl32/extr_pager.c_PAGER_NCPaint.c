#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_4__ {int dwStyle; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  BRbtnState; int /*<<< orphan*/  clrBk; int /*<<< orphan*/  TLbtnState; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ PAGER_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ HRGN ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int DCX_USESTYLE ; 
 int DCX_WINDOW ; 
 int /*<<< orphan*/  DefWindowProcW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDCEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PAGER_DrawButton (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGER_GetButtonRects (TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PGS_HORZ ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_NCPAINT ; 
 int WS_MINIMIZE ; 

__attribute__((used)) static LRESULT
PAGER_NCPaint (const PAGER_INFO* infoPtr, HRGN hRgn)
{
    RECT rcBottomRight, rcTopLeft;
    HDC hdc;

    if (infoPtr->dwStyle & WS_MINIMIZE)
        return 0;

    DefWindowProcW (infoPtr->hwndSelf, WM_NCPAINT, (WPARAM)hRgn, 0);

    if (!(hdc = GetDCEx (infoPtr->hwndSelf, 0, DCX_USESTYLE | DCX_WINDOW)))
        return 0;

    PAGER_GetButtonRects(infoPtr, &rcTopLeft, &rcBottomRight, FALSE);

    PAGER_DrawButton(hdc, infoPtr->clrBk, rcTopLeft,
                     infoPtr->dwStyle & PGS_HORZ, TRUE, infoPtr->TLbtnState);
    PAGER_DrawButton(hdc, infoPtr->clrBk, rcBottomRight,
                     infoPtr->dwStyle & PGS_HORZ, FALSE, infoPtr->BRbtnState);

    ReleaseDC( infoPtr->hwndSelf, hdc );
    return 0;
}