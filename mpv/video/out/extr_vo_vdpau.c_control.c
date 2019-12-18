#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct vo {int want_redraw; struct vdpctx* priv; } ;
struct vdpctx {int deint; } ;
struct mp_image {int dummy; } ;

/* Variables and functions */
#define  VOCTRL_GET_PREF_DEINT 132 
#define  VOCTRL_RESET 131 
#define  VOCTRL_SCREENSHOT_WIN 130 
#define  VOCTRL_SET_EQUALIZER 129 
#define  VOCTRL_SET_PANSCAN 128 
 int VO_EVENT_EXPOSE ; 
 int VO_EVENT_RESIZE ; 
 int VO_TRUE ; 
 int /*<<< orphan*/  check_preemption (struct vo*) ; 
 int /*<<< orphan*/  checked_resize (struct vo*) ; 
 int /*<<< orphan*/  forget_frames (struct vo*,int) ; 
 struct mp_image* get_window_screenshot (struct vo*) ; 
 int /*<<< orphan*/  status_ok (struct vo*) ; 
 int /*<<< orphan*/  vo_event (struct vo*,int) ; 
 int vo_x11_control (struct vo*,int*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int control(struct vo *vo, uint32_t request, void *data)
{
    struct vdpctx *vc = vo->priv;

    check_preemption(vo);

    switch (request) {
    case VOCTRL_SET_PANSCAN:
        checked_resize(vo);
        return VO_TRUE;
    case VOCTRL_SET_EQUALIZER:
        vo->want_redraw = true;
        return true;
    case VOCTRL_RESET:
        forget_frames(vo, true);
        return true;
    case VOCTRL_SCREENSHOT_WIN:
        if (!status_ok(vo))
            return false;
        *(struct mp_image **)data = get_window_screenshot(vo);
        return true;
    case VOCTRL_GET_PREF_DEINT:
        *(int *)data = vc->deint;
        return true;
    }

    int events = 0;
    int r = vo_x11_control(vo, &events, request, data);

    if (events & VO_EVENT_RESIZE) {
        checked_resize(vo);
    } else if (events & VO_EVENT_EXPOSE) {
        vo->want_redraw = true;
    }
    vo_event(vo, events);

    return r;
}