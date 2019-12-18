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
struct ra_ctx {int /*<<< orphan*/  swapchain; TYPE_1__* vo; struct priv* priv; } ;
struct priv {TYPE_2__* fb; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_3__ {int /*<<< orphan*/  dheight; int /*<<< orphan*/  dwidth; } ;

/* Variables and functions */
 int /*<<< orphan*/  ra_gl_ctx_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool drm_egl_reconfig(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    ctx->vo->dwidth  = p->fb->width;
    ctx->vo->dheight = p->fb->height;
    ra_gl_ctx_resize(ctx->swapchain, p->fb->width, p->fb->height, 0);
    return true;
}