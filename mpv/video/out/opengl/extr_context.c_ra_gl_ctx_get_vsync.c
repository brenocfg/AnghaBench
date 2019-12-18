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
struct vo_vsync_info {int dummy; } ;
struct ra_swapchain {int /*<<< orphan*/  ctx; struct priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_vsync ) (int /*<<< orphan*/ ,struct vo_vsync_info*) ;} ;
struct priv {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct vo_vsync_info*) ; 

__attribute__((used)) static void ra_gl_ctx_get_vsync(struct ra_swapchain *sw,
                                struct vo_vsync_info *info)
{
    struct priv *p = sw->priv;
    if (p->params.get_vsync)
        p->params.get_vsync(sw->ctx, info);
}