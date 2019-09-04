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
struct ra_ctx {struct priv* priv; } ;
struct priv {double display_fps; int /*<<< orphan*/  reload_display; } ;
struct mp_image {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_WARN (struct ra_ctx*,char*) ; 
#define  VOCTRL_CHECK_EVENTS 131 
#define  VOCTRL_FULLSCREEN 130 
#define  VOCTRL_GET_DISPLAY_FPS 129 
#define  VOCTRL_SCREENSHOT_WIN 128 
 int VO_NOTIMPL ; 
 int VO_TRUE ; 
 int /*<<< orphan*/  atomic_fetch_and (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recreate_dispmanx (struct ra_ctx*) ; 
 struct mp_image* take_screenshot (struct ra_ctx*) ; 

__attribute__((used)) static int rpi_control(struct ra_ctx *ctx, int *events, int request, void *arg)
{
    struct priv *p = ctx->priv;

    switch (request) {
    case VOCTRL_SCREENSHOT_WIN:
        *(struct mp_image **)arg = take_screenshot(ctx);
        return VO_TRUE;
    case VOCTRL_FULLSCREEN:
        recreate_dispmanx(ctx);
        return VO_TRUE;
    case VOCTRL_CHECK_EVENTS:
        if (atomic_fetch_and(&p->reload_display, 0)) {
            MP_WARN(ctx, "Recovering from display mode switch...\n");
            recreate_dispmanx(ctx);
        }
        return VO_TRUE;
    case VOCTRL_GET_DISPLAY_FPS:
        *(double *)arg = p->display_fps;
        return VO_TRUE;
    }

    return VO_NOTIMPL;
}