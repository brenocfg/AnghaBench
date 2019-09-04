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
struct priv {int /*<<< orphan*/  egl_display; int /*<<< orphan*/ * egl_context; int /*<<< orphan*/  egl_surface; scalar_t__ egl_window; } ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_NO_CONTEXT ; 
 int /*<<< orphan*/  eglDestroyContext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglDestroySurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglReleaseThread () ; 
 int /*<<< orphan*/  eglTerminate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_gl_ctx_uninit (struct ra_ctx*) ; 
 int /*<<< orphan*/  vo_wayland_uninit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_egl_window_destroy (scalar_t__) ; 

__attribute__((used)) static void wayland_egl_uninit(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;

    ra_gl_ctx_uninit(ctx);

    if (p->egl_context) {
        eglReleaseThread();
        if (p->egl_window)
            wl_egl_window_destroy(p->egl_window);
        eglDestroySurface(p->egl_display, p->egl_surface);
        eglMakeCurrent(p->egl_display, NULL, NULL, EGL_NO_CONTEXT);
        eglDestroyContext(p->egl_display, p->egl_context);
        p->egl_context = NULL;
    }
    eglTerminate(p->egl_display);

    vo_wayland_uninit(ctx->vo);
}