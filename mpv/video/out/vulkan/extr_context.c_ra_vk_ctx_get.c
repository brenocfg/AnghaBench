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
struct ra_ctx {TYPE_1__* swapchain; } ;
struct priv {struct mpvk_ctx* vk; } ;
struct mpvk_ctx {int dummy; } ;
struct TYPE_2__ {struct priv* priv; int /*<<< orphan*/ * fns; } ;

/* Variables and functions */
 int /*<<< orphan*/  vulkan_swapchain ; 

struct mpvk_ctx *ra_vk_ctx_get(struct ra_ctx *ctx)
{
    if (ctx->swapchain->fns != &vulkan_swapchain)
        return NULL;

    struct priv *p = ctx->swapchain->priv;
    return p->vk;
}