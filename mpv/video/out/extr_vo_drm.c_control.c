#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct vo {int want_redraw; int /*<<< orphan*/  params; int /*<<< orphan*/  config_ok; struct priv* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  msc; int /*<<< orphan*/  ust; } ;
struct TYPE_3__ {int last_queue_display_time; int /*<<< orphan*/  skipped_vsyncs; } ;
struct priv {int paused; TYPE_2__ vsync; TYPE_1__ vsync_info; int /*<<< orphan*/  kms; int /*<<< orphan*/  cur_frame; } ;
struct mp_image {int dummy; } ;

/* Variables and functions */
#define  VOCTRL_GET_DISPLAY_FPS 132 
#define  VOCTRL_PAUSE 131 
#define  VOCTRL_RESUME 130 
#define  VOCTRL_SCREENSHOT_WIN 129 
#define  VOCTRL_SET_PANSCAN 128 
 int VO_NOTIMPL ; 
 int VO_TRUE ; 
 double kms_get_display_fps (int /*<<< orphan*/ ) ; 
 struct mp_image* mp_image_new_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reconfig (struct vo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int control(struct vo *vo, uint32_t request, void *arg)
{
    struct priv *p = vo->priv;
    switch (request) {
    case VOCTRL_SCREENSHOT_WIN:
        *(struct mp_image**)arg = mp_image_new_copy(p->cur_frame);
        return VO_TRUE;
    case VOCTRL_SET_PANSCAN:
        if (vo->config_ok)
            reconfig(vo, vo->params);
        return VO_TRUE;
    case VOCTRL_GET_DISPLAY_FPS: {
        double fps = kms_get_display_fps(p->kms);
        if (fps <= 0)
            break;
        *(double*)arg = fps;
        return VO_TRUE;
    }
    case VOCTRL_PAUSE:
        vo->want_redraw = true;
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