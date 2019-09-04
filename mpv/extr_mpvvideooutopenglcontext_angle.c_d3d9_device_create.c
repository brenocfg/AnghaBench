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
struct priv {scalar_t__ egl_display; } ;
typedef  scalar_t__ (* PFNEGLGETPLATFORMDISPLAYEXTPROC ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  EGLint ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_DEFAULT_DISPLAY ; 
 int /*<<< orphan*/  EGL_NONE ; 
 scalar_t__ EGL_NO_DISPLAY ; 
 int /*<<< orphan*/  EGL_PLATFORM_ANGLE_ANGLE ; 
 int /*<<< orphan*/  EGL_PLATFORM_ANGLE_DEVICE_TYPE_ANGLE ; 
 int /*<<< orphan*/  EGL_PLATFORM_ANGLE_DEVICE_TYPE_HARDWARE_ANGLE ; 
 int /*<<< orphan*/  EGL_PLATFORM_ANGLE_TYPE_ANGLE ; 
 int /*<<< orphan*/  EGL_PLATFORM_ANGLE_TYPE_D3D9_ANGLE ; 
 int /*<<< orphan*/  MP_FATAL (struct vo*,char*) ; 
 int /*<<< orphan*/  eglGetProcAddress (char*) ; 

__attribute__((used)) static bool d3d9_device_create(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    struct vo *vo = ctx->vo;

    PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT =
        (PFNEGLGETPLATFORMDISPLAYEXTPROC)eglGetProcAddress("eglGetPlatformDisplayEXT");
    if (!eglGetPlatformDisplayEXT) {
        MP_FATAL(vo, "Missing EGL_EXT_platform_base\n");
        return false;
    }

    EGLint display_attributes[] = {
        EGL_PLATFORM_ANGLE_TYPE_ANGLE,
            EGL_PLATFORM_ANGLE_TYPE_D3D9_ANGLE,
        EGL_PLATFORM_ANGLE_DEVICE_TYPE_ANGLE,
            EGL_PLATFORM_ANGLE_DEVICE_TYPE_HARDWARE_ANGLE,
        EGL_NONE,
    };
    p->egl_display = eglGetPlatformDisplayEXT(EGL_PLATFORM_ANGLE_ANGLE,
        EGL_DEFAULT_DISPLAY, display_attributes);
    if (p->egl_display == EGL_NO_DISPLAY) {
        MP_FATAL(vo, "Couldn't get display\n");
        return false;
    }

    return true;
}