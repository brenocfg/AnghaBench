#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ra_ctx {TYPE_1__* vo; struct priv* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  msc; int /*<<< orphan*/  ust; } ;
struct TYPE_5__ {int last_queue_display_time; int /*<<< orphan*/  skipped_vsyncs; } ;
struct priv {int paused; TYPE_3__ vsync; TYPE_2__ vsync_info; int /*<<< orphan*/  kms; } ;
struct TYPE_4__ {int want_redraw; } ;

/* Variables and functions */
#define  VOCTRL_GET_DISPLAY_FPS 130 
#define  VOCTRL_PAUSE 129 
#define  VOCTRL_RESUME 128 
 int VO_NOTIMPL ; 
 int VO_TRUE ; 
 double kms_get_display_fps (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_egl_control(struct ra_ctx *ctx, int *events, int request,
                           void *arg)
{
    struct priv *p = ctx->priv;
    switch (request) {
    case VOCTRL_GET_DISPLAY_FPS: {
        double fps = kms_get_display_fps(p->kms);
        if (fps <= 0)
            break;
        *(double*)arg = fps;
        return VO_TRUE;
    }
    case VOCTRL_PAUSE:
        ctx->vo->want_redraw = true;
        p->paused = true;
        return VO_TRUE;
    case VOCTRL_RESUME:
        p->paused = false;
        p->vsync_info.last_queue_display_time = -1;
        p->vsync_info.skipped_vsyncs = 0;
        p->vsync.ust = 0;
        p->vsync.msc = 0;
        return VO_TRUE;
    }
    return VO_NOTIMPL;
}