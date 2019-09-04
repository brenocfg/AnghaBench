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
struct priv {int /*<<< orphan*/  vk; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpvk_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ra_vk_ctx_uninit (struct ra_ctx*) ; 
 int /*<<< orphan*/  vo_x11_uninit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xlib_uninit(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;

    ra_vk_ctx_uninit(ctx);
    mpvk_uninit(&p->vk);
    vo_x11_uninit(ctx->vo);
}