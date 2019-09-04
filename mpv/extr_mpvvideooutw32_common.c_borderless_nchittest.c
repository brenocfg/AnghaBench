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
struct vo_w32_state {int /*<<< orphan*/  windowrc; int /*<<< orphan*/  window; } ;
struct TYPE_3__ {int member_0; int member_1; int y; int x; } ;
typedef  TYPE_1__ POINT ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTBOTTOM ; 
 int /*<<< orphan*/  HTBOTTOMLEFT ; 
 int /*<<< orphan*/  HTBOTTOMRIGHT ; 
 int /*<<< orphan*/  HTCLIENT ; 
 int /*<<< orphan*/  HTLEFT ; 
 int /*<<< orphan*/  HTRIGHT ; 
 int /*<<< orphan*/  HTTOP ; 
 int /*<<< orphan*/  HTTOPLEFT ; 
 int /*<<< orphan*/  HTTOPRIGHT ; 
 scalar_t__ IsMaximized (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXBORDER ; 
 int /*<<< orphan*/  SM_CXFRAME ; 
 int /*<<< orphan*/  SM_CXPADDEDBORDER ; 
 int /*<<< orphan*/  ScreenToClient (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int rect_h (int /*<<< orphan*/ ) ; 
 int rect_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT borderless_nchittest(struct vo_w32_state *w32, int x, int y)
{
    if (IsMaximized(w32->window))
        return HTCLIENT;

    POINT mouse = { x, y };
    ScreenToClient(w32->window, &mouse);

    // The horizontal frame should be the same size as the vertical frame,
    // since the NONCLIENTMETRICS structure does not distinguish between them
    int frame_size = GetSystemMetrics(SM_CXFRAME) +
                     GetSystemMetrics(SM_CXPADDEDBORDER);
    // The diagonal size handles are slightly wider than the side borders
    int diagonal_width = frame_size * 2 + GetSystemMetrics(SM_CXBORDER);

    // Hit-test top border
    if (mouse.y < frame_size) {
        if (mouse.x < diagonal_width)
            return HTTOPLEFT;
        if (mouse.x >= rect_w(w32->windowrc) - diagonal_width)
            return HTTOPRIGHT;
        return HTTOP;
    }

    // Hit-test bottom border
    if (mouse.y >= rect_h(w32->windowrc) - frame_size) {
        if (mouse.x < diagonal_width)
            return HTBOTTOMLEFT;
        if (mouse.x >= rect_w(w32->windowrc) - diagonal_width)
            return HTBOTTOMRIGHT;
        return HTBOTTOM;
    }

    // Hit-test side borders
    if (mouse.x < frame_size)
        return HTLEFT;
    if (mouse.x >= rect_w(w32->windowrc) - frame_size)
        return HTRIGHT;
    return HTCLIENT;
}