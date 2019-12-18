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
struct ra_ctx {TYPE_1__* vo; int /*<<< orphan*/  swapchain; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  main_fb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dheight; int /*<<< orphan*/  dwidth; } ;

/* Variables and functions */
 int /*<<< orphan*/  dxgl_reset (struct ra_ctx*) ; 
 int /*<<< orphan*/  ra_gl_ctx_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resize(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    dxgl_reset(ctx);
    ra_gl_ctx_resize(ctx->swapchain, ctx->vo->dwidth, ctx->vo->dheight, p->main_fb);
}