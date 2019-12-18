#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  self; } ;
struct TYPE_8__ {int left; int top; scalar_t__ bottom; scalar_t__ right; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ LB_DESCR ;
typedef  int /*<<< orphan*/  HTHEME ;
typedef  int /*<<< orphan*/  HRGN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CombineRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateRectRgn (int,int,scalar_t__,scalar_t__) ; 
 int DCX_INTERSECTRGN ; 
 int DCX_WINDOW ; 
 int /*<<< orphan*/  DrawThemeBackground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawThemeParentBackground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ExcludeClipRect (int /*<<< orphan*/ ,int,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int /*<<< orphan*/  GetDCEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowDC (int /*<<< orphan*/ ) ; 
 int GetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetWindowTheme (int /*<<< orphan*/ ) ; 
 scalar_t__ IsThemeBackgroundPartiallyTransparent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OffsetRect (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  RGN_AND ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXEDGE ; 
 int /*<<< orphan*/  SM_CYEDGE ; 
 int WS_EX_CLIENTEDGE ; 

__attribute__((used)) static void LISTBOX_NCPaint( LB_DESCR *descr, HRGN region )
{
    DWORD exstyle = GetWindowLongW( descr->self, GWL_EXSTYLE);
    HTHEME theme = GetWindowTheme( descr->self );
    HRGN cliprgn = region;
    int cxEdge, cyEdge;
    HDC hdc;
    RECT r;

    if (!theme || !(exstyle & WS_EX_CLIENTEDGE))
        return;

    cxEdge = GetSystemMetrics(SM_CXEDGE),
    cyEdge = GetSystemMetrics(SM_CYEDGE);

    GetWindowRect(descr->self, &r);

    /* New clipping region passed to default proc to exclude border */
    cliprgn = CreateRectRgn(r.left + cxEdge, r.top + cyEdge,
        r.right - cxEdge, r.bottom - cyEdge);
    if (region != (HRGN)1)
        CombineRgn(cliprgn, cliprgn, region, RGN_AND);
    OffsetRect(&r, -r.left, -r.top);

#ifdef __REACTOS__ /* r73789 */
    hdc = GetWindowDC(descr->self);
    /* Exclude client part */
    ExcludeClipRect(hdc,
                    r.left + cxEdge,
                    r.top + cyEdge,
                    r.right - cxEdge,
                    r.bottom -cyEdge);
#else
    hdc = GetDCEx(descr->self, region, DCX_WINDOW|DCX_INTERSECTRGN);
    OffsetRect(&r, -r.left, -r.top);
#endif

    if (IsThemeBackgroundPartiallyTransparent (theme, 0, 0))
        DrawThemeParentBackground(descr->self, hdc, &r);
    DrawThemeBackground (theme, hdc, 0, 0, &r, 0);
    ReleaseDC(descr->self, hdc);
}