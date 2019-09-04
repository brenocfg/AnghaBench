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
struct priv {scalar_t__ ra_ctx; } ;
struct libmpv_gpu_context {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ra_gl_ctx_uninit (scalar_t__) ; 

__attribute__((used)) static void destroy(struct libmpv_gpu_context *ctx)
{
    struct priv *p = ctx->priv;

    if (p->ra_ctx)
        ra_gl_ctx_uninit(p->ra_ctx);
}