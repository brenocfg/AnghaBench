#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ra_ctx {TYPE_2__* ra; int /*<<< orphan*/  vo; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  device; int /*<<< orphan*/  swapchain; int /*<<< orphan*/  backbuffer; } ;
struct TYPE_5__ {TYPE_1__* fns; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* destroy ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SAFE_RELEASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_tex_free (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  vo_w32_uninit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d3d11_uninit(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;

    if (ctx->ra)
        ra_tex_free(ctx->ra, &p->backbuffer);
    SAFE_RELEASE(p->swapchain);
    vo_w32_uninit(ctx->vo);
    SAFE_RELEASE(p->device);

    // Destory the RA last to prevent objects we hold from showing up in D3D's
    // leak checker
    if (ctx->ra)
        ctx->ra->fns->destroy(ctx->ra);
}