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
struct priv {int /*<<< orphan*/  (* Flush ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  vo_cocoa_swap_buffers (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cocoa_swap_buffers(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    vo_cocoa_swap_buffers(ctx->vo);
    p->Flush();
}