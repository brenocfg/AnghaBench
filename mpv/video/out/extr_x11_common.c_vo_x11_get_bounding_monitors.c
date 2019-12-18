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
struct vo_x11_state {int /*<<< orphan*/  display; } ;
struct TYPE_4__ {scalar_t__ y_org; scalar_t__ height; scalar_t__ x_org; scalar_t__ width; } ;
typedef  TYPE_1__ XineramaScreenInfo ;

/* Variables and functions */
 int /*<<< orphan*/  XFree (TYPE_1__*) ; 
 TYPE_1__* XineramaQueryScreens (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void vo_x11_get_bounding_monitors(struct vo_x11_state *x11, long b[4])
{
    //top  bottom left   right
    b[0] = b[1] = b[2] = b[3] = 0;
    int num_screens = 0;
    XineramaScreenInfo *screens = XineramaQueryScreens(x11->display, &num_screens);
    if (!screens)
        return;
    for (int n = 0; n < num_screens; n++) {
        XineramaScreenInfo *s = &screens[n];
        if (s->y_org < screens[b[0]].y_org)
            b[0] = n;
        if (s->y_org + s->height > screens[b[1]].y_org + screens[b[1]].height)
            b[1] = n;
        if (s->x_org < screens[b[2]].x_org)
            b[2] = n;
        if (s->x_org + s->width > screens[b[3]].x_org + screens[b[3]].width)
            b[3] = n;
    }
    XFree(screens);
}