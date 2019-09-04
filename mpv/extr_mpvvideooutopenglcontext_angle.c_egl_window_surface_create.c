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
struct vo {int dummy; } ;
struct ra_ctx {struct vo* vo; struct priv* priv; } ;
struct priv {int flipped; int /*<<< orphan*/  egl_context; int /*<<< orphan*/  egl_window; int /*<<< orphan*/  egl_display; int /*<<< orphan*/  egl_config; } ;
typedef  scalar_t__ EGLint ;

/* Variables and functions */
 scalar_t__ EGL_NONE ; 
 int /*<<< orphan*/  EGL_OPTIMAL_SURFACE_ORIENTATION_ANGLE ; 
 scalar_t__ EGL_SURFACE_ORIENTATION_ANGLE ; 
 scalar_t__ EGL_SURFACE_ORIENTATION_INVERT_Y_ANGLE ; 
 int /*<<< orphan*/  MP_FATAL (struct vo*,char*) ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (int /*<<< orphan*/ *,scalar_t__*,int,scalar_t__) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct vo*,char*) ; 
 int /*<<< orphan*/  eglCreateWindowSurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ eglGetConfigAttrib (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  eglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  egl_window_surface_destroy (struct ra_ctx*) ; 
 int /*<<< orphan*/  talloc_free (scalar_t__*) ; 
 int /*<<< orphan*/  vo_w32_hwnd (struct vo*) ; 

__attribute__((used)) static bool egl_window_surface_create(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    struct vo *vo = ctx->vo;

    int window_attribs_len = 0;
    EGLint *window_attribs = NULL;

    EGLint flip_val;
    if (eglGetConfigAttrib(p->egl_display, p->egl_config,
                           EGL_OPTIMAL_SURFACE_ORIENTATION_ANGLE, &flip_val))
    {
        if (flip_val == EGL_SURFACE_ORIENTATION_INVERT_Y_ANGLE) {
            MP_TARRAY_APPEND(NULL, window_attribs, window_attribs_len,
                EGL_SURFACE_ORIENTATION_ANGLE);
            MP_TARRAY_APPEND(NULL, window_attribs, window_attribs_len,
                EGL_SURFACE_ORIENTATION_INVERT_Y_ANGLE);
            p->flipped = true;
            MP_VERBOSE(vo, "Rendering flipped.\n");
        }
    }

    MP_TARRAY_APPEND(NULL, window_attribs, window_attribs_len, EGL_NONE);
    p->egl_window = eglCreateWindowSurface(p->egl_display, p->egl_config,
                                           vo_w32_hwnd(vo), window_attribs);
    talloc_free(window_attribs);
    if (!p->egl_window) {
        MP_FATAL(vo, "Could not create EGL surface!\n");
        goto fail;
    }

    eglMakeCurrent(p->egl_display, p->egl_window, p->egl_window,
                   p->egl_context);
    return true;
fail:
    egl_window_surface_destroy(ctx);
    return false;
}