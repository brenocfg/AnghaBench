#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct voctrl_performance_data {int dummy; } ;
struct vo_frame {int dummy; } ;
struct vo {int want_redraw; struct gpu_priv* priv; } ;
struct gpu_priv {int events; TYPE_2__* ctx; int /*<<< orphan*/  renderer; } ;
struct TYPE_5__ {TYPE_1__* fns; } ;
struct TYPE_4__ {int (* control ) (TYPE_2__*,int*,int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  (* reconfig ) (TYPE_2__*) ;} ;

/* Variables and functions */
#define  VOCTRL_EXTERNAL_RESIZE 136 
#define  VOCTRL_LOAD_HWDEC_API 135 
#define  VOCTRL_PAUSE 134 
#define  VOCTRL_PERFORMANCE_DATA 133 
#define  VOCTRL_RESET 132 
#define  VOCTRL_SCREENSHOT 131 
#define  VOCTRL_SET_EQUALIZER 130 
#define  VOCTRL_SET_PANSCAN 129 
#define  VOCTRL_UPDATE_RENDER_OPTS 128 
 int VO_EVENT_AMBIENT_LIGHTING_CHANGED ; 
 int VO_EVENT_EXPOSE ; 
 int VO_EVENT_ICC_PROFILE_CHANGED ; 
 int VO_EVENT_RESIZE ; 
 int VO_TRUE ; 
 int /*<<< orphan*/  get_and_update_ambient_lighting (struct gpu_priv*) ; 
 int /*<<< orphan*/  get_and_update_icc_profile (struct gpu_priv*) ; 
 int /*<<< orphan*/  gl_video_configure_queue (int /*<<< orphan*/ ,struct vo*) ; 
 int /*<<< orphan*/  gl_video_perfdata (int /*<<< orphan*/ ,struct voctrl_performance_data*) ; 
 int /*<<< orphan*/  gl_video_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_video_screenshot (int /*<<< orphan*/ ,struct vo_frame*,void*) ; 
 int /*<<< orphan*/  gl_video_showing_interpolated_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_hwdec_api (struct vo*) ; 
 int /*<<< orphan*/  resize (struct vo*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int stub2 (TYPE_2__*,int*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  talloc_free (struct vo_frame*) ; 
 int /*<<< orphan*/  vo_event (struct vo*,int) ; 
 struct vo_frame* vo_get_current_vo_frame (struct vo*) ; 

__attribute__((used)) static int control(struct vo *vo, uint32_t request, void *data)
{
    struct gpu_priv *p = vo->priv;

    switch (request) {
    case VOCTRL_SET_PANSCAN:
        resize(vo);
        return VO_TRUE;
    case VOCTRL_SET_EQUALIZER:
        vo->want_redraw = true;
        return VO_TRUE;
    case VOCTRL_SCREENSHOT: {
        struct vo_frame *frame = vo_get_current_vo_frame(vo);
        if (frame)
            gl_video_screenshot(p->renderer, frame, data);
        talloc_free(frame);
        return true;
    }
    case VOCTRL_LOAD_HWDEC_API:
        request_hwdec_api(vo);
        return true;
    case VOCTRL_UPDATE_RENDER_OPTS: {
        gl_video_configure_queue(p->renderer, vo);
        get_and_update_icc_profile(p);
        vo->want_redraw = true;
        return true;
    }
    case VOCTRL_RESET:
        gl_video_reset(p->renderer);
        return true;
    case VOCTRL_PAUSE:
        if (gl_video_showing_interpolated_frame(p->renderer))
            vo->want_redraw = true;
        return true;
    case VOCTRL_PERFORMANCE_DATA:
        gl_video_perfdata(p->renderer, (struct voctrl_performance_data *)data);
        return true;
    case VOCTRL_EXTERNAL_RESIZE:
        p->ctx->fns->reconfig(p->ctx);
        resize(vo);
        return true;
    }

    int events = 0;
    int r = p->ctx->fns->control(p->ctx, &events, request, data);
    if (events & VO_EVENT_ICC_PROFILE_CHANGED) {
        get_and_update_icc_profile(p);
        vo->want_redraw = true;
    }
    if (events & VO_EVENT_AMBIENT_LIGHTING_CHANGED) {
        get_and_update_ambient_lighting(p);
        vo->want_redraw = true;
    }
    events |= p->events;
    p->events = 0;
    if (events & VO_EVENT_RESIZE)
        resize(vo);
    if (events & VO_EVENT_EXPOSE)
        vo->want_redraw = true;
    vo_event(vo, events);

    return r;
}