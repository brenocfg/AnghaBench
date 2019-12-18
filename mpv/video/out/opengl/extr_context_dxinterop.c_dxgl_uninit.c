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
 int /*<<< orphan*/  DwmEnableMMCSS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  d3d_destroy (struct ra_ctx*) ; 
 int /*<<< orphan*/  d3d_size_dependent_destroy (struct ra_ctx*) ; 
 int /*<<< orphan*/  os_ctx_destroy (struct ra_ctx*) ; 
 int /*<<< orphan*/  pump_message_loop () ; 
 int /*<<< orphan*/  ra_gl_ctx_uninit (struct ra_ctx*) ; 
 int /*<<< orphan*/  vo_w32_uninit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dxgl_uninit(struct ra_ctx *ctx)
{
    ra_gl_ctx_uninit(ctx);
    d3d_size_dependent_destroy(ctx);
    d3d_destroy(ctx);
    os_ctx_destroy(ctx);
    vo_w32_uninit(ctx->vo);
    DwmEnableMMCSS(FALSE);
    pump_message_loop();
}