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
struct priv {int /*<<< orphan*/  d3d11_device; scalar_t__ egl_device; scalar_t__ egl_display; } ;
typedef  int /*<<< orphan*/  (* PFNEGLRELEASEDEVICEANGLEPROC ) (scalar_t__) ;

/* Variables and functions */
 scalar_t__ EGL_NO_DISPLAY ; 
 int /*<<< orphan*/  SAFE_RELEASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglGetProcAddress (char*) ; 
 int /*<<< orphan*/  eglTerminate (scalar_t__) ; 

__attribute__((used)) static void d3d11_device_destroy(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;

    PFNEGLRELEASEDEVICEANGLEPROC eglReleaseDeviceANGLE =
        (PFNEGLRELEASEDEVICEANGLEPROC)eglGetProcAddress("eglReleaseDeviceANGLE");

    if (p->egl_display)
        eglTerminate(p->egl_display);
    p->egl_display = EGL_NO_DISPLAY;

    if (p->egl_device && eglReleaseDeviceANGLE)
        eglReleaseDeviceANGLE(p->egl_device);
    p->egl_device = 0;

    SAFE_RELEASE(p->d3d11_device);
}