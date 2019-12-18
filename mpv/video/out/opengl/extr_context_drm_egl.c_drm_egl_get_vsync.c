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
struct vo_vsync_info {int dummy; } ;
struct ra_ctx {struct priv* priv; } ;
struct priv {struct vo_vsync_info vsync_info; } ;

/* Variables and functions */

__attribute__((used)) static void drm_egl_get_vsync(struct ra_ctx *ctx, struct vo_vsync_info *info)
{
    struct priv *p = ctx->priv;
    *info = p->vsync_info;
}