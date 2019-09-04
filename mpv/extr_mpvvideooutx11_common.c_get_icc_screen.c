#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xrandr_display {int /*<<< orphan*/  rc; } ;
struct TYPE_2__ {int x0; int x1; int y0; int y1; } ;
struct vo_x11_state {int current_icc_screen; int num_displays; struct xrandr_display* displays; TYPE_1__ winrc; } ;
struct vo {struct vo_x11_state* x11; } ;

/* Variables and functions */
 scalar_t__ mp_rect_contains (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int get_icc_screen(struct vo *vo)
{
    struct vo_x11_state *x11 = vo->x11;
    int cx = x11->winrc.x0 + (x11->winrc.x1 - x11->winrc.x0)/2,
    cy = x11->winrc.y0 + (x11->winrc.y1 - x11->winrc.y0)/2;
    int screen = x11->current_icc_screen; // xinerama screen number
    for (int n = 0; n < x11->num_displays; n++) {
        struct xrandr_display *disp = &x11->displays[n];
        if (mp_rect_contains(&disp->rc, cx, cy)) {
            screen = n;
            break;
        }
    }
    return screen;
}