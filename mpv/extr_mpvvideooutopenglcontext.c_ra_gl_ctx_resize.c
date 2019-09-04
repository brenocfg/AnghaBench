#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ra_swapchain {TYPE_2__* ctx; struct priv* priv; } ;
struct priv {int main_fb; TYPE_3__* wrapped_fb; } ;
struct TYPE_5__ {int w; int h; } ;
struct TYPE_7__ {TYPE_1__ params; } ;
struct TYPE_6__ {int /*<<< orphan*/  ra; } ;

/* Variables and functions */
 TYPE_3__* ra_create_wrapped_fb (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ra_tex_free (int /*<<< orphan*/ ,TYPE_3__**) ; 

void ra_gl_ctx_resize(struct ra_swapchain *sw, int w, int h, int fbo)
{
    struct priv *p = sw->priv;
    if (p->main_fb == fbo && p->wrapped_fb && p->wrapped_fb->params.w == w
        && p->wrapped_fb->params.h == h)
        return;

    if (p->wrapped_fb)
        ra_tex_free(sw->ctx->ra, &p->wrapped_fb);

    p->main_fb = fbo;
    p->wrapped_fb = ra_create_wrapped_fb(sw->ctx->ra, fbo, w, h);
}