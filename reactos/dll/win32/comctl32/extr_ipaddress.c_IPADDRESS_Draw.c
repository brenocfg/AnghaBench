#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_17__ {scalar_t__ clrGrayText; scalar_t__ clr3dFace; scalar_t__ clrWindowText; scalar_t__ clrWindow; } ;
struct TYPE_16__ {scalar_t__ Self; TYPE_1__* Part; scalar_t__ Enabled; } ;
struct TYPE_15__ {int /*<<< orphan*/  left; int /*<<< orphan*/  right; } ;
struct TYPE_14__ {int /*<<< orphan*/  EditHwnd; } ;
typedef  TYPE_2__ RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_3__ IPADDRESS_INFO ;
typedef  scalar_t__ HTHEME ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int DWORD ;
typedef  scalar_t__ COLORREF ;

/* Variables and functions */
 int BF_ADJUST ; 
 int BF_RECT ; 
 int /*<<< orphan*/  CloseThemeData (scalar_t__) ; 
 int DT_BOTTOM ; 
 int DT_CENTER ; 
 int DT_SINGLELINE ; 
 int /*<<< orphan*/  DrawEdge (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DrawTextW (int /*<<< orphan*/ ,char const*,int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  DrawThemeBackground (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawThemeParentBackground (scalar_t__,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  DrawThemeText (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*,int,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  EDGE_SUNKEN ; 
 int /*<<< orphan*/  EP_EDITTEXT ; 
 int ES_READONLY ; 
 int ETS_DISABLED ; 
 int ETS_FOCUSED ; 
 int ETS_NORMAL ; 
 int ETS_READONLY ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetClientRect (scalar_t__,TYPE_2__*) ; 
 scalar_t__ GetFocus () ; 
 int /*<<< orphan*/  GetThemeColor (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int GetWindowLongW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ IsThemeBackgroundPartiallyTransparent (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ OpenThemeData (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TMT_FILLCOLOR ; 
 int /*<<< orphan*/  TMT_TEXTCOLOR ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  WC_EDITW ; 
 TYPE_4__ comctl32_color ; 

__attribute__((used)) static LRESULT IPADDRESS_Draw (const IPADDRESS_INFO *infoPtr, HDC hdc)
{
    static const WCHAR dotW[] = { '.', 0 };
    RECT rect, rcPart;
    COLORREF bgCol, fgCol;
    HTHEME theme;
    int i, state = ETS_NORMAL;

    TRACE("\n");

    GetClientRect (infoPtr->Self, &rect);

    theme = OpenThemeData(infoPtr->Self, WC_EDITW);

    if (theme) {
        DWORD dwStyle = GetWindowLongW (infoPtr->Self, GWL_STYLE);

        if (!infoPtr->Enabled)
            state = ETS_DISABLED;
        else if (dwStyle & ES_READONLY)
            state = ETS_READONLY;
        else if (GetFocus() == infoPtr->Self)
            state = ETS_FOCUSED;

        GetThemeColor(theme, EP_EDITTEXT, state, TMT_FILLCOLOR, &bgCol);
        GetThemeColor(theme, EP_EDITTEXT, state, TMT_TEXTCOLOR, &fgCol);

        if (IsThemeBackgroundPartiallyTransparent (theme, EP_EDITTEXT, state))
            DrawThemeParentBackground(infoPtr->Self, hdc, &rect);
        DrawThemeBackground (theme, hdc, EP_EDITTEXT, state, &rect, 0);
    } else {
        if (infoPtr->Enabled) {
            bgCol = comctl32_color.clrWindow;
            fgCol = comctl32_color.clrWindowText;
        } else {
            bgCol = comctl32_color.clr3dFace;
            fgCol = comctl32_color.clrGrayText;
        }

        FillRect (hdc, &rect, (HBRUSH)(DWORD_PTR)(bgCol+1));
        DrawEdge (hdc, &rect, EDGE_SUNKEN, BF_RECT | BF_ADJUST);
    }
    
    SetBkColor  (hdc, bgCol);
    SetTextColor(hdc, fgCol);

    for (i = 0; i < 3; i++) {
        GetWindowRect (infoPtr->Part[i].EditHwnd, &rcPart);
        MapWindowPoints( 0, infoPtr->Self, (POINT *)&rcPart, 2 );
        rect.left = rcPart.right;
        GetWindowRect (infoPtr->Part[i+1].EditHwnd, &rcPart);
        MapWindowPoints( 0, infoPtr->Self, (POINT *)&rcPart, 2 );
        rect.right = rcPart.left;

        if (theme)
            DrawThemeText(theme, hdc, EP_EDITTEXT, state, dotW, 1, DT_SINGLELINE | DT_CENTER | DT_BOTTOM, 0, &rect);
        else
            DrawTextW(hdc, dotW, 1, &rect, DT_SINGLELINE | DT_CENTER | DT_BOTTOM);
    }

    if (theme)
        CloseThemeData(theme);

    return 0;
}