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
struct ra_ctx {scalar_t__ ra; TYPE_1__* swapchain; } ;
struct priv {scalar_t__ wrapped_fb; } ;
struct TYPE_2__ {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ra_free (scalar_t__*) ; 
 int /*<<< orphan*/  ra_tex_free (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  talloc_free (TYPE_1__*) ; 

void ra_gl_ctx_uninit(struct ra_ctx *ctx)
{
    if (ctx->swapchain) {
        struct priv *p = ctx->swapchain->priv;
        if (ctx->ra && p->wrapped_fb)
            ra_tex_free(ctx->ra, &p->wrapped_fb);
        talloc_free(ctx->swapchain);
        ctx->swapchain = NULL;
    }

    ra_free(&ctx->ra);
}