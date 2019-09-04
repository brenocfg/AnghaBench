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
struct priv {scalar_t__ egl_display; } ;

/* Variables and functions */
 scalar_t__ EGL_NO_DISPLAY ; 
 int /*<<< orphan*/  eglTerminate (scalar_t__) ; 

__attribute__((used)) static void d3d9_device_destroy(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;

    if (p->egl_display)
        eglTerminate(p->egl_display);
    p->egl_display = EGL_NO_DISPLAY;
}