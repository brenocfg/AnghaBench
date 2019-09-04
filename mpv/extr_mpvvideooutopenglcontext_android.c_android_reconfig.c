#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ra_ctx {int /*<<< orphan*/  swapchain; TYPE_2__* vo; int /*<<< orphan*/  global; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  egl_surface; int /*<<< orphan*/  egl_display; } ;
struct TYPE_3__ {int w; int h; } ;
struct android_opts {TYPE_1__ surface_size; } ;
struct TYPE_4__ {int dwidth; int dheight; } ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_HEIGHT ; 
 int /*<<< orphan*/  EGL_WIDTH ; 
 int /*<<< orphan*/  MP_FATAL (struct ra_ctx*,char*) ; 
 int /*<<< orphan*/  android_conf ; 
 int /*<<< orphan*/  eglQuerySurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct android_opts* mp_get_config_group (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ra_gl_ctx_resize (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool android_reconfig(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    void *tmp = talloc_new(NULL);
    struct android_opts *opts = mp_get_config_group(tmp, ctx->global, &android_conf);
    int w = opts->surface_size.w, h = opts->surface_size.h;

    if (!w)
        eglQuerySurface(p->egl_display, p->egl_surface, EGL_WIDTH, &w);
    if (!h)
        eglQuerySurface(p->egl_display, p->egl_surface, EGL_HEIGHT, &h);

    if (!w || !h) {
        MP_FATAL(ctx, "Failed to get height and width!\n");
        return false;
    }

    ctx->vo->dwidth = w;
    ctx->vo->dheight = h;
    ra_gl_ctx_resize(ctx->swapchain, w, h, 0);

    talloc_free(tmp);
    return true;
}