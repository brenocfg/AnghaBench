#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vo {int /*<<< orphan*/  log; TYPE_1__* opts; } ;
struct ra_ctx {struct vo* vo; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  egl_display; int /*<<< orphan*/  egl_device; int /*<<< orphan*/  d3d11_device; int /*<<< orphan*/  d3d11_context; struct angle_opts* opts; } ;
struct d3d11_device_opts {int allow_warp; int force_warp; int /*<<< orphan*/  max_frame_latency; int /*<<< orphan*/  min_feature_level; int /*<<< orphan*/  max_feature_level; } ;
struct angle_opts {int d3d11_warp; int /*<<< orphan*/  d3d11_feature_level; } ;
struct TYPE_2__ {int /*<<< orphan*/  swapchain_depth; } ;
typedef  int /*<<< orphan*/  (* PFNEGLGETPLATFORMDISPLAYEXTPROC ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  (* PFNEGLCREATEDEVICEANGLEPROC ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;

/* Variables and functions */
 int /*<<< orphan*/  D3D_FEATURE_LEVEL_9_3 ; 
 int /*<<< orphan*/  EGL_D3D11_DEVICE_ANGLE ; 
 int /*<<< orphan*/  EGL_PLATFORM_DEVICE_EXT ; 
 int /*<<< orphan*/  ID3D11Device_GetImmediateContext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_FATAL (struct vo*,char*) ; 
 int /*<<< orphan*/  eglGetProcAddress (char*) ; 
 int /*<<< orphan*/  mp_d3d11_create_present_device (int /*<<< orphan*/ ,struct d3d11_device_opts*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool d3d11_device_create(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    struct vo *vo = ctx->vo;
    struct angle_opts *o = p->opts;

    struct d3d11_device_opts device_opts = {
        .allow_warp = o->d3d11_warp != 0,
        .force_warp = o->d3d11_warp == 1,
        .max_feature_level = o->d3d11_feature_level,
        .min_feature_level = D3D_FEATURE_LEVEL_9_3,
        .max_frame_latency = ctx->vo->opts->swapchain_depth,
    };
    if (!mp_d3d11_create_present_device(vo->log, &device_opts, &p->d3d11_device))
        return false;
    ID3D11Device_GetImmediateContext(p->d3d11_device, &p->d3d11_context);

    PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT =
        (PFNEGLGETPLATFORMDISPLAYEXTPROC)eglGetProcAddress("eglGetPlatformDisplayEXT");
    if (!eglGetPlatformDisplayEXT) {
        MP_FATAL(vo, "Missing EGL_EXT_platform_base\n");
        return false;
    }
    PFNEGLCREATEDEVICEANGLEPROC eglCreateDeviceANGLE =
        (PFNEGLCREATEDEVICEANGLEPROC)eglGetProcAddress("eglCreateDeviceANGLE");
    if (!eglCreateDeviceANGLE) {
        MP_FATAL(vo, "Missing EGL_EXT_platform_device\n");
        return false;
    }

    p->egl_device = eglCreateDeviceANGLE(EGL_D3D11_DEVICE_ANGLE,
        p->d3d11_device, NULL);
    if (!p->egl_device) {
        MP_FATAL(vo, "Couldn't create EGL device\n");
        return false;
    }

    p->egl_display = eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT,
        p->egl_device, NULL);
    if (!p->egl_display) {
        MP_FATAL(vo, "Couldn't get EGL display\n");
        return false;
    }

    return true;
}