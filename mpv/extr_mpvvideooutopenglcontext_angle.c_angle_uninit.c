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
struct ra_ctx {int /*<<< orphan*/  vo; struct priv* priv; } ;
struct priv {scalar_t__ d3d11_device; scalar_t__ dxgi_swapchain; } ;

/* Variables and functions */
 int /*<<< orphan*/  DwmEnableMMCSS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  context_destroy (struct ra_ctx*) ; 
 int /*<<< orphan*/  d3d11_device_destroy (struct ra_ctx*) ; 
 int /*<<< orphan*/  d3d11_swapchain_surface_destroy (struct ra_ctx*) ; 
 int /*<<< orphan*/  d3d9_device_destroy (struct ra_ctx*) ; 
 int /*<<< orphan*/  egl_window_surface_destroy (struct ra_ctx*) ; 
 int /*<<< orphan*/  ra_gl_ctx_uninit (struct ra_ctx*) ; 
 int /*<<< orphan*/  vo_w32_uninit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void angle_uninit(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;

    ra_gl_ctx_uninit(ctx);

    DwmEnableMMCSS(FALSE);

    // Uninit the EGL surface implementation that is being used. Note: This may
    // result in the *_destroy function being called twice since it is also
    // called when the surface create function fails. This is fine because the
    // *_destroy functions are idempotent.
    if (p->dxgi_swapchain)
        d3d11_swapchain_surface_destroy(ctx);
    else
        egl_window_surface_destroy(ctx);

    context_destroy(ctx);

    // Uninit the EGL device implementation that is being used
    if (p->d3d11_device)
        d3d11_device_destroy(ctx);
    else
        d3d9_device_destroy(ctx);

    vo_w32_uninit(ctx->vo);
}