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
 int egl_create_context (struct ra_ctx*) ; 
 int /*<<< orphan*/  vo_wayland_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vo_wayland_uninit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool wayland_egl_init(struct ra_ctx *ctx)
{
    if (!vo_wayland_init(ctx->vo)) {
        vo_wayland_uninit(ctx->vo);
        return false;
    }

    return egl_create_context(ctx);
}