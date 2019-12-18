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
struct ra_ctx {int /*<<< orphan*/  swapchain; TYPE_1__* vo; } ;
struct TYPE_2__ {int dwidth; int dheight; } ;

/* Variables and functions */
 int /*<<< orphan*/  ra_gl_ctx_resize (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vo_android_surface_size (TYPE_1__*,int*,int*) ; 

__attribute__((used)) static bool android_reconfig(struct ra_ctx *ctx)
{
    int w, h;
    if (!vo_android_surface_size(ctx->vo, &w, &h))
        return false;

    ctx->vo->dwidth = w;
    ctx->vo->dheight = h;
    ra_gl_ctx_resize(ctx->swapchain, w, h, 0);
    return true;
}