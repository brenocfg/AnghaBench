#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_10__ {int /*<<< orphan*/  clr3dShadow; } ;
struct TYPE_7__ {int uItemState; int /*<<< orphan*/  hdc; } ;
struct TYPE_9__ {int nHLStringBkMode; int /*<<< orphan*/  clrText; int /*<<< orphan*/  clrMark; int /*<<< orphan*/  clrTextHighlight; int /*<<< orphan*/  clrBtnHighlight; TYPE_1__ nmcd; } ;
struct TYPE_8__ {scalar_t__ nMaxTextRows; int /*<<< orphan*/  dwDTFlags; int /*<<< orphan*/  hFont; int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_2__ TOOLBAR_INFO ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_3__ NMTBCUSTOMDRAW ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ HTHEME ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int CDIS_CHECKED ; 
 int CDIS_DISABLED ; 
 int CDIS_HOT ; 
 int CDIS_INDETERMINATE ; 
 int CDIS_MARKED ; 
 int CDIS_SELECTED ; 
 int DTT_GRAYED ; 
 int /*<<< orphan*/  DrawTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawThemeText (scalar_t__,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ GetWindowTheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OffsetRect (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SetBkMode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TBCDRF_HILITEHOTTRACK ; 
 int TBCDRF_NOMARK ; 
 int TP_BUTTON ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TS_DISABLED ; 
 int TS_HOT ; 
 int TS_HOTCHECKED ; 
 int TS_NORMAL ; 
 int TS_PRESSED ; 
 TYPE_4__ comctl32_color ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
TOOLBAR_DrawString (const TOOLBAR_INFO *infoPtr, RECT *rcText, LPCWSTR lpText,
                    const NMTBCUSTOMDRAW *tbcd, DWORD dwItemCDFlag)
{
    HDC hdc = tbcd->nmcd.hdc;
    HFONT  hOldFont = 0;
    COLORREF clrOld = 0;
    COLORREF clrOldBk = 0;
    int oldBkMode = 0;
    UINT state = tbcd->nmcd.uItemState;
#ifdef __REACTOS__
    HTHEME theme = GetWindowTheme (infoPtr->hwndSelf);
#endif

    /* draw text */
    if (lpText && infoPtr->nMaxTextRows > 0) {
        TRACE("string=%s rect=(%s)\n", debugstr_w(lpText),
              wine_dbgstr_rect(rcText));

	hOldFont = SelectObject (hdc, infoPtr->hFont);
#ifdef __REACTOS__
    if (theme)
    {
        DWORD dwDTFlags2 = 0;
        int partId = TP_BUTTON;
        int stateId = TS_NORMAL;

        if (state & CDIS_DISABLED)
        {
            stateId = TS_DISABLED;
            dwDTFlags2 = DTT_GRAYED;
        }
        else if (state & CDIS_SELECTED)
            stateId = TS_PRESSED;
        else if (state & CDIS_CHECKED)
            stateId = (state & CDIS_HOT) ? TS_HOTCHECKED : TS_HOT;
        else if (state & CDIS_HOT)
            stateId = TS_HOT;

        DrawThemeText(theme, hdc, partId, stateId, lpText, -1, infoPtr->dwDTFlags, dwDTFlags2, rcText);
        SelectObject (hdc, hOldFont);
        return;
    }
#endif

	if ((state & CDIS_HOT) && (dwItemCDFlag & TBCDRF_HILITEHOTTRACK )) {
	    clrOld = SetTextColor (hdc, tbcd->clrTextHighlight);
	}
	else if (state & CDIS_DISABLED) {
	    clrOld = SetTextColor (hdc, tbcd->clrBtnHighlight);
	    OffsetRect (rcText, 1, 1);
	    DrawTextW (hdc, lpText, -1, rcText, infoPtr->dwDTFlags);
	    SetTextColor (hdc, comctl32_color.clr3dShadow);
	    OffsetRect (rcText, -1, -1);
	}
	else if (state & CDIS_INDETERMINATE) {
	    clrOld = SetTextColor (hdc, comctl32_color.clr3dShadow);
	}
	else if ((state & CDIS_MARKED) && !(dwItemCDFlag & TBCDRF_NOMARK)) {
	    clrOld = SetTextColor (hdc, tbcd->clrTextHighlight);
	    clrOldBk = SetBkColor (hdc, tbcd->clrMark);
	    oldBkMode = SetBkMode (hdc, tbcd->nHLStringBkMode);
	}
	else {
	    clrOld = SetTextColor (hdc, tbcd->clrText);
	}

	DrawTextW (hdc, lpText, -1, rcText, infoPtr->dwDTFlags);
	SetTextColor (hdc, clrOld);
	if ((state & CDIS_MARKED) && !(dwItemCDFlag & TBCDRF_NOMARK))
	{
	    SetBkColor (hdc, clrOldBk);
	    SetBkMode (hdc, oldBkMode);
	}
	SelectObject (hdc, hOldFont);
    }
}