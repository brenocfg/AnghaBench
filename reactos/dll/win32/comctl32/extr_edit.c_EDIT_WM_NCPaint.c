#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_6__ {int left; int top; scalar_t__ bottom; scalar_t__ right; } ;
typedef  TYPE_1__ RECT ;
typedef  scalar_t__ HWND ;
typedef  scalar_t__ HTHEME ;
typedef  scalar_t__ HRGN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CombineRgn (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateRectRgn (int,int,scalar_t__,scalar_t__) ; 
 int DCX_INTERSECTRGN ; 
 int DCX_WINDOW ; 
 int /*<<< orphan*/  DefWindowProcW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawThemeBackground (scalar_t__,int /*<<< orphan*/ ,int const,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawThemeParentBackground (scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int EP_EDITTEXT ; 
 int ES_READONLY ; 
 int ETS_DISABLED ; 
 int ETS_FOCUSED ; 
 int ETS_NORMAL ; 
 int ETS_READONLY ; 
 int /*<<< orphan*/  ExcludeClipRect (int /*<<< orphan*/ ,int,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetDCEx (scalar_t__,scalar_t__,int) ; 
 scalar_t__ GetFocus () ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowDC (scalar_t__) ; 
 int GetWindowLongW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (scalar_t__,TYPE_1__*) ; 
 scalar_t__ GetWindowTheme (scalar_t__) ; 
 scalar_t__ IsThemeBackgroundPartiallyTransparent (scalar_t__,int const,int) ; 
 int /*<<< orphan*/  IsWindowEnabled (scalar_t__) ; 
 int /*<<< orphan*/  OffsetRect (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  RGN_AND ; 
 int /*<<< orphan*/  ReleaseDC (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXEDGE ; 
 int /*<<< orphan*/  SM_CYEDGE ; 
 int /*<<< orphan*/  WM_NCPAINT ; 
 int WS_EX_CLIENTEDGE ; 

__attribute__((used)) static void EDIT_WM_NCPaint(HWND hwnd, HRGN region)
{
    DWORD exStyle = GetWindowLongW(hwnd, GWL_EXSTYLE);
    HTHEME theme = GetWindowTheme(hwnd);
    HRGN cliprgn = region;

    if (theme && exStyle & WS_EX_CLIENTEDGE)
    {
        HDC dc;
        RECT r;
        int cxEdge = GetSystemMetrics(SM_CXEDGE),
            cyEdge = GetSystemMetrics(SM_CYEDGE);
        const int part = EP_EDITTEXT;
        int state = ETS_NORMAL;
        DWORD dwStyle = GetWindowLongW(hwnd, GWL_STYLE);

        if (!IsWindowEnabled(hwnd))
            state = ETS_DISABLED;
        else if (dwStyle & ES_READONLY)
            state = ETS_READONLY;
        else if (GetFocus() == hwnd)
            state = ETS_FOCUSED;

        GetWindowRect(hwnd, &r);

        /* New clipping region passed to default proc to exclude border */
        cliprgn = CreateRectRgn(r.left + cxEdge, r.top + cyEdge,
            r.right - cxEdge, r.bottom - cyEdge);
        if (region != (HRGN)1)
            CombineRgn(cliprgn, cliprgn, region, RGN_AND);
        OffsetRect(&r, -r.left, -r.top);

#ifdef __REACTOS__ /* r73789 */
        dc = GetWindowDC(hwnd);
        /* Exclude client part */
        ExcludeClipRect(dc,
                        r.left + cxEdge,
                        r.top + cyEdge,
                        r.right - cxEdge,
                        r.bottom -cyEdge);
#else
        dc = GetDCEx(hwnd, region, DCX_WINDOW|DCX_INTERSECTRGN);
        OffsetRect(&r, -r.left, -r.top);
#endif

        if (IsThemeBackgroundPartiallyTransparent(theme, part, state))
            DrawThemeParentBackground(hwnd, dc, &r);
        DrawThemeBackground(theme, dc, part, state, &r, 0);
        ReleaseDC(hwnd, dc);
    }

    /* Call default proc to get the scrollbars etc. also painted */
    DefWindowProcW (hwnd, WM_NCPAINT, (WPARAM)cliprgn, 0);
}