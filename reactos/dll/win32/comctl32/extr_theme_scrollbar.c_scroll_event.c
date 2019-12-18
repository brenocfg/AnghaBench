#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tme ;
typedef  enum SCROLL_HITTEST { ____Placeholder_SCROLL_HITTEST } SCROLL_HITTEST ;
typedef  int UINT ;
struct TYPE_3__ {int cbSize; int dwFlags; scalar_t__ hwndTrack; } ;
typedef  TYPE_1__ TRACKMOUSEEVENT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HTHEME ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_STYLE ; 
 int GetWindowLongW (scalar_t__,int /*<<< orphan*/ ) ; 
 int SBS_SIZEBOX ; 
 int SBS_SIZEGRIP ; 
 int SCROLL_NOWHERE ; 
 int TME_LEAVE ; 
 int TME_QUERY ; 
 int /*<<< orphan*/  TrackMouseEvent (TYPE_1__*) ; 
#define  WM_MOUSELEAVE 129 
#define  WM_MOUSEMOVE 128 
 int hit_test (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redraw_part (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int tracking_hot_part ; 
 scalar_t__ tracking_win ; 

__attribute__((used)) static void scroll_event(HWND hwnd, HTHEME theme, UINT msg, POINT pt)
{
    enum SCROLL_HITTEST hittest;
    TRACKMOUSEEVENT tme;

    if (GetWindowLongW(hwnd, GWL_STYLE) & (SBS_SIZEGRIP | SBS_SIZEBOX))
        return;

    hittest = hit_test(hwnd, theme, pt);

    switch (msg)
    {
        case WM_MOUSEMOVE:
            hittest = hit_test(hwnd, theme, pt);
            tracking_win = hwnd;
            break;

        case WM_MOUSELEAVE:
            if (tracking_win == hwnd) {
                hittest = SCROLL_NOWHERE;
            }
            break;
    }

    tme.cbSize = sizeof(tme);
    tme.dwFlags = TME_QUERY;
    TrackMouseEvent(&tme);

    if (!(tme.dwFlags & TME_LEAVE) || tme.hwndTrack != hwnd) {
        tme.dwFlags = TME_LEAVE;
        tme.hwndTrack = hwnd;
        TrackMouseEvent(&tme);
    }

    if (tracking_win != hwnd && msg == WM_MOUSELEAVE) {
        redraw_part(hwnd, theme, SCROLL_NOWHERE);
        return;
    }

    if (tracking_win == hwnd && hittest != tracking_hot_part) {
        enum SCROLL_HITTEST oldhotpart = tracking_hot_part;

        tracking_hot_part = hittest;

        if (hittest != SCROLL_NOWHERE)
            redraw_part(hwnd, theme, hittest);
        else
            tracking_win = 0;

        if (oldhotpart != SCROLL_NOWHERE)
            redraw_part(hwnd, theme, oldhotpart);
    }
}