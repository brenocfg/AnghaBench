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
struct ra_ctx {TYPE_3__* swapchain; TYPE_2__* ra; } ;
struct priv {int /*<<< orphan*/  swapchain; struct mpvk_ctx* vk; } ;
struct mpvk_ctx {int /*<<< orphan*/  vulkan; int /*<<< orphan*/ * gpu; } ;
struct TYPE_6__ {struct priv* priv; } ;
struct TYPE_5__ {TYPE_1__* fns; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* destroy ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TA_FREEP (TYPE_3__**) ; 
 int /*<<< orphan*/  pl_gpu_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pl_swapchain_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pl_vulkan_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void ra_vk_ctx_uninit(struct ra_ctx *ctx)
{
    if (!ctx->swapchain)
        return;

    struct priv *p = ctx->swapchain->priv;
    struct mpvk_ctx *vk = p->vk;

    if (ctx->ra) {
        pl_gpu_finish(vk->gpu);
        pl_swapchain_destroy(&p->swapchain);
        ctx->ra->fns->destroy(ctx->ra);
        ctx->ra = NULL;
    }

    vk->gpu = NULL;
    pl_vulkan_destroy(&vk->vulkan);
    TA_FREEP(&ctx->swapchain);
}