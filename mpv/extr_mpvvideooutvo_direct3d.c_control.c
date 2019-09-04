#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct vo {int want_redraw; TYPE_2__* priv; } ;
struct mp_image {int dummy; } ;
struct TYPE_8__ {TYPE_1__* vo; } ;
typedef  TYPE_2__ d3d_priv ;
struct TYPE_7__ {int want_redraw; } ;

/* Variables and functions */
#define  VOCTRL_REDRAW_FRAME 130 
#define  VOCTRL_SCREENSHOT_WIN 129 
#define  VOCTRL_SET_PANSCAN 128 
 int VO_EVENT_EXPOSE ; 
 int VO_EVENT_RESIZE ; 
 int VO_TRUE ; 
 int /*<<< orphan*/  calc_fs_rect (TYPE_2__*) ; 
 int /*<<< orphan*/  d3d_draw_frame (TYPE_2__*) ; 
 struct mp_image* get_window_screenshot (TYPE_2__*) ; 
 int /*<<< orphan*/  resize_d3d (TYPE_2__*) ; 
 int /*<<< orphan*/  vo_event (struct vo*,int) ; 
 int vo_w32_control (struct vo*,int*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int control(struct vo *vo, uint32_t request, void *data)
{
    d3d_priv *priv = vo->priv;

    switch (request) {
    case VOCTRL_REDRAW_FRAME:
        d3d_draw_frame(priv);
        return VO_TRUE;
    case VOCTRL_SET_PANSCAN:
        calc_fs_rect(priv);
        priv->vo->want_redraw = true;
        return VO_TRUE;
    case VOCTRL_SCREENSHOT_WIN:
        *(struct mp_image **)data = get_window_screenshot(priv);
        return VO_TRUE;
    }

    int events = 0;
    int r = vo_w32_control(vo, &events, request, data);

    if (events & VO_EVENT_RESIZE)
        resize_d3d(priv);

    if (events & VO_EVENT_EXPOSE)
        vo->want_redraw = true;

    vo_event(vo, events);

    return r;
}