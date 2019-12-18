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
struct priv {scalar_t__ dxgi_swapchain; } ;

/* Variables and functions */
 int /*<<< orphan*/  d3d11_swap_buffers (struct ra_ctx*) ; 
 int /*<<< orphan*/  egl_swap_buffers (struct ra_ctx*) ; 

__attribute__((used)) static void angle_swap_buffers(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    if (p->dxgi_swapchain)
        d3d11_swap_buffers(ctx);
    else
        egl_swap_buffers(ctx);
}