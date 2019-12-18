#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ra_ctx {int /*<<< orphan*/  vo; struct priv* priv; } ;
struct TYPE_7__ {int /*<<< orphan*/  render_fd; } ;
struct TYPE_6__ {int /*<<< orphan*/  context; int /*<<< orphan*/  display; int /*<<< orphan*/  surface; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; int /*<<< orphan*/  surface; scalar_t__ num_bos; } ;
struct priv {TYPE_4__* kms; TYPE_3__ drm_params; TYPE_2__ egl; TYPE_1__ gbm; int /*<<< orphan*/  vt_switcher; scalar_t__ vt_switcher_active; } ;
struct drm_atomic_context {int /*<<< orphan*/  request; } ;
struct TYPE_8__ {int /*<<< orphan*/  fd; struct drm_atomic_context* atomic_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_NO_CONTEXT ; 
 int /*<<< orphan*/  EGL_NO_SURFACE ; 
 int /*<<< orphan*/  MP_ERR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crtc_release (struct ra_ctx*) ; 
 int drmModeAtomicCommit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drmModeAtomicFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglDestroyContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglDestroySurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglTerminate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gbm_device_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gbm_surface_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kms_destroy (TYPE_4__*) ; 
 int /*<<< orphan*/  ra_gl_ctx_uninit (struct ra_ctx*) ; 
 int /*<<< orphan*/  swapchain_step (struct ra_ctx*) ; 
 int /*<<< orphan*/  vt_switcher_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drm_egl_uninit(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    struct drm_atomic_context *atomic_ctx = p->kms->atomic_context;

    if (atomic_ctx) {
        int ret = drmModeAtomicCommit(p->kms->fd, atomic_ctx->request, 0, NULL);
        if (ret)
            MP_ERR(ctx->vo, "Failed to commit atomic request (%d)\n", ret);
        drmModeAtomicFree(atomic_ctx->request);
    }

    ra_gl_ctx_uninit(ctx);

    crtc_release(ctx);
    if (p->vt_switcher_active)
        vt_switcher_destroy(&p->vt_switcher);

    // According to GBM documentation all BO:s must be released before
    // gbm_surface_destroy can be called on the surface.
    while (p->gbm.num_bos) {
        swapchain_step(ctx);
    }

    eglMakeCurrent(p->egl.display, EGL_NO_SURFACE, EGL_NO_SURFACE,
                   EGL_NO_CONTEXT);
    eglDestroyContext(p->egl.display, p->egl.context);
    eglDestroySurface(p->egl.display, p->egl.surface);
    gbm_surface_destroy(p->gbm.surface);
    eglTerminate(p->egl.display);
    gbm_device_destroy(p->gbm.device);
    p->egl.context = EGL_NO_CONTEXT;
    eglDestroyContext(p->egl.display, p->egl.context);

    close(p->drm_params.render_fd);

    if (p->kms) {
        kms_destroy(p->kms);
        p->kms = 0;
    }
}