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
struct vo_frame {int /*<<< orphan*/  still; } ;
struct ra_swapchain {struct ra_ctx* ctx; } ;
struct ra_ctx {struct priv* priv; } ;
struct priv {int /*<<< orphan*/  still; } ;

/* Variables and functions */
 int ra_gl_ctx_submit_frame (struct ra_swapchain*,struct vo_frame const*) ; 

__attribute__((used)) static bool drm_egl_submit_frame(struct ra_swapchain *sw, const struct vo_frame *frame)
{
    struct ra_ctx *ctx = sw->ctx;
    struct priv *p = ctx->priv;

    p->still = frame->still;

    return ra_gl_ctx_submit_frame(sw, frame);
}