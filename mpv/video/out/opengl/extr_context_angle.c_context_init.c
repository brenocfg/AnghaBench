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
struct priv {int /*<<< orphan*/  egl_config; int /*<<< orphan*/  egl_context; int /*<<< orphan*/  egl_display; } ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_EXTENSIONS ; 
 int /*<<< orphan*/  MP_DBG (struct vo*,char*,char const*) ; 
 int /*<<< orphan*/  MP_FATAL (struct vo*,char*) ; 
 int /*<<< orphan*/  context_destroy (struct ra_ctx*) ; 
 int /*<<< orphan*/  eglInitialize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* eglQueryString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpegl_create_context (struct ra_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool context_init(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    struct vo *vo = ctx->vo;

    if (!eglInitialize(p->egl_display, NULL, NULL)) {
        MP_FATAL(vo, "Couldn't initialize EGL\n");
        goto fail;
    }

    const char *exts = eglQueryString(p->egl_display, EGL_EXTENSIONS);
    if (exts)
        MP_DBG(vo, "EGL extensions: %s\n", exts);

    if (!mpegl_create_context(ctx, p->egl_display, &p->egl_context,
                              &p->egl_config))
    {
        MP_FATAL(vo, "Could not create EGL context!\n");
        goto fail;
    }

    return true;
fail:
    context_destroy(ctx);
    return false;
}