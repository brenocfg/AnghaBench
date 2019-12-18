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
struct ra_ctx {int /*<<< orphan*/  vo; } ;

/* Variables and functions */
 int /*<<< orphan*/  ra_vk_ctx_resize (struct ra_ctx*,int,int) ; 
 int /*<<< orphan*/  vo_android_surface_size (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static bool android_reconfig(struct ra_ctx *ctx)
{
    int w, h;
    if (!vo_android_surface_size(ctx->vo, &w, &h))
        return false;

    ra_vk_ctx_resize(ctx, w, h);
    return true;
}