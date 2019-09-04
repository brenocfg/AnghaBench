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
struct priv {int /*<<< orphan*/  hdc; scalar_t__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  DwmEnableMMCSS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  destroy_gl ; 
 int /*<<< orphan*/  ra_gl_ctx_uninit (struct ra_ctx*) ; 
 int /*<<< orphan*/  vo_w32_run_on_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ra_ctx*) ; 
 int /*<<< orphan*/  vo_w32_uninit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wgl_uninit(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    ra_gl_ctx_uninit(ctx);
    if (p->context)
        wglMakeCurrent(p->hdc, 0);
    vo_w32_run_on_thread(ctx->vo, destroy_gl, ctx);

    DwmEnableMMCSS(FALSE);
    vo_w32_uninit(ctx->vo);
}