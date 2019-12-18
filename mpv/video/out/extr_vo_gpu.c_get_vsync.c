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
struct vo_vsync_info {int dummy; } ;
struct vo {struct gpu_priv* priv; } ;
struct ra_swapchain {TYPE_2__* fns; } ;
struct gpu_priv {TYPE_1__* ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_vsync ) (struct ra_swapchain*,struct vo_vsync_info*) ;} ;
struct TYPE_3__ {struct ra_swapchain* swapchain; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ra_swapchain*,struct vo_vsync_info*) ; 

__attribute__((used)) static void get_vsync(struct vo *vo, struct vo_vsync_info *info)
{
    struct gpu_priv *p = vo->priv;
    struct ra_swapchain *sw = p->ctx->swapchain;
    if (sw->fns->get_vsync)
        sw->fns->get_vsync(sw, info);
}