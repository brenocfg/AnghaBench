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
struct priv {TYPE_1__* vo; int /*<<< orphan*/  screen_osd_res; int /*<<< orphan*/  dst_rect; int /*<<< orphan*/  src_rect; } ;
struct TYPE_2__ {int want_redraw; } ;

/* Variables and functions */
 int /*<<< orphan*/  vo_get_src_dst_rects (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void resize(struct priv *p)
{
    vo_get_src_dst_rects(p->vo, &p->src_rect, &p->dst_rect, &p->screen_osd_res);

    // It's not clear whether this is needed; maybe not.
    //vo_x11_clearwindow(p->vo, p->vo->x11->window);

    p->vo->want_redraw = true;
}