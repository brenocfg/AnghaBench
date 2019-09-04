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
struct vo_frame {int display_synced; } ;
struct ra_swapchain {int dummy; } ;
struct priv {TYPE_1__* ra_ctx; } ;
struct libmpv_gpu_context {struct priv* priv; } ;
struct TYPE_2__ {struct ra_swapchain* swapchain; } ;

/* Variables and functions */
 int /*<<< orphan*/  ra_gl_ctx_submit_frame (struct ra_swapchain*,struct vo_frame*) ; 

__attribute__((used)) static void done_frame(struct libmpv_gpu_context *ctx, bool ds)
{
    struct priv *p = ctx->priv;

    struct ra_swapchain *sw = p->ra_ctx->swapchain;
    struct vo_frame dummy = {.display_synced = ds};
    ra_gl_ctx_submit_frame(sw, &dummy);
}