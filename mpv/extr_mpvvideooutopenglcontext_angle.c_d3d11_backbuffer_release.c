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
struct priv {int /*<<< orphan*/  d3d11_backbuffer; scalar_t__ egl_backbuffer; int /*<<< orphan*/  egl_display; } ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_NO_CONTEXT ; 
 scalar_t__ EGL_NO_SURFACE ; 
 int /*<<< orphan*/  SAFE_RELEASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglDestroySurface (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  eglMakeCurrent (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d3d11_backbuffer_release(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;

    if (p->egl_backbuffer) {
        eglMakeCurrent(p->egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE,
                       EGL_NO_CONTEXT);
        eglDestroySurface(p->egl_display, p->egl_backbuffer);
    }
    p->egl_backbuffer = EGL_NO_SURFACE;

    SAFE_RELEASE(p->d3d11_backbuffer);
}