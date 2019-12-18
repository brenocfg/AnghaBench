#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ clrBk; unsigned int numParts; int /*<<< orphan*/  Notify; int /*<<< orphan*/  Self; int /*<<< orphan*/ * parts; int /*<<< orphan*/  part0; scalar_t__ simple; scalar_t__ hDefaultFont; scalar_t__ hFont; } ;
typedef  TYPE_1__ STATUS_INFO ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HTHEME ;
typedef  scalar_t__ HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;

/* Variables and functions */
 scalar_t__ CLR_DEFAULT ; 
 int /*<<< orphan*/  COLOR_3DFACE ; 
 int /*<<< orphan*/  CreateSolidBrush (scalar_t__) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawThemeBackground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetSysColorBrush (int /*<<< orphan*/ ) ; 
 int GetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowTheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsWindowVisible (int /*<<< orphan*/ ) ; 
 int SBARS_SIZEGRIP ; 
 int /*<<< orphan*/  STATUSBAR_DrawSizeGrip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUSBAR_RefreshPart (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  STATUSBAR_SetPartBounds (TYPE_1__*) ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int WS_MAXIMIZE ; 

__attribute__((used)) static LRESULT
STATUSBAR_Refresh (STATUS_INFO *infoPtr, HDC hdc)
{
    RECT   rect;
    HBRUSH hbrBk;
    HFONT  hOldFont;
    HTHEME theme;

    TRACE("\n");
    if (!IsWindowVisible(infoPtr->Self))
        return 0;

    STATUSBAR_SetPartBounds(infoPtr);

    GetClientRect (infoPtr->Self, &rect);

    if ((theme = GetWindowTheme (infoPtr->Self)))
    {
        DrawThemeBackground(theme, hdc, 0, 0, &rect, NULL);
    }
    else
    {
        if (infoPtr->clrBk != CLR_DEFAULT)
            hbrBk = CreateSolidBrush (infoPtr->clrBk);
        else
            hbrBk = GetSysColorBrush (COLOR_3DFACE);
        FillRect(hdc, &rect, hbrBk);
        if (infoPtr->clrBk != CLR_DEFAULT)
            DeleteObject (hbrBk);
    }

    hOldFont = SelectObject (hdc, infoPtr->hFont ? infoPtr->hFont : infoPtr->hDefaultFont);

    if (infoPtr->simple) {
	STATUSBAR_RefreshPart (infoPtr, hdc, &infoPtr->part0, 0);
    } else {
        unsigned int i;

	for (i = 0; i < infoPtr->numParts; i++) {
	    STATUSBAR_RefreshPart (infoPtr, hdc, &infoPtr->parts[i], i);
	}
    }

    SelectObject (hdc, hOldFont);

    if ((GetWindowLongW (infoPtr->Self, GWL_STYLE) & SBARS_SIZEGRIP)
            && !(GetWindowLongW (infoPtr->Notify, GWL_STYLE) & WS_MAXIMIZE))
	    STATUSBAR_DrawSizeGrip (theme, hdc, &rect);

    return 0;
}