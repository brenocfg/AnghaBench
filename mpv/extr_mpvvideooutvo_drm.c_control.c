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
typedef  int uint32_t ;
struct vo {int /*<<< orphan*/  params; int /*<<< orphan*/  config_ok; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  kms; int /*<<< orphan*/  last_input; int /*<<< orphan*/  cur_frame; } ;
struct mp_image {int dummy; } ;

/* Variables and functions */
#define  VOCTRL_GET_DISPLAY_FPS 131 
#define  VOCTRL_REDRAW_FRAME 130 
#define  VOCTRL_SCREENSHOT_WIN 129 
#define  VOCTRL_SET_PANSCAN 128 
 int VO_NOTIMPL ; 
 int VO_TRUE ; 
 int /*<<< orphan*/  draw_image (struct vo*,int /*<<< orphan*/ ) ; 
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
    case VOCTRL_REDRAW_FRAME:
        draw_image(vo, p->last_input);
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
    }
    return VO_NOTIMPL;
}