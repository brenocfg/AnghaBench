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
struct priv {int /*<<< orphan*/  egl_display; scalar_t__ egl_context; } ;

/* Variables and functions */
 scalar_t__ EGL_NO_CONTEXT ; 
 int /*<<< orphan*/  EGL_NO_DISPLAY ; 
 int /*<<< orphan*/  destroy_dispmanx (struct ra_ctx*) ; 
 int /*<<< orphan*/  eglDestroyContext (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  eglReleaseThread () ; 
 int /*<<< orphan*/  ra_gl_ctx_uninit (struct ra_ctx*) ; 
 int /*<<< orphan*/  tv_callback ; 
 int /*<<< orphan*/  vc_tv_unregister_callback_full (int /*<<< orphan*/ ,struct ra_ctx*) ; 

__attribute__((used)) static void rpi_uninit(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    ra_gl_ctx_uninit(ctx);

    vc_tv_unregister_callback_full(tv_callback, ctx);

    destroy_dispmanx(ctx);

    if (p->egl_context)
        eglDestroyContext(p->egl_display, p->egl_context);
    p->egl_context = EGL_NO_CONTEXT;
    eglReleaseThread();
    p->egl_display = EGL_NO_DISPLAY;
}