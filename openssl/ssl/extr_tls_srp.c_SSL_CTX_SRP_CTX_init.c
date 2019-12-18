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
struct TYPE_2__ {int /*<<< orphan*/  strength; } ;
struct ssl_ctx_st {TYPE_1__ srp_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SRP_MINIMAL_N ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int SSL_CTX_SRP_CTX_init(struct ssl_ctx_st *ctx)
{
    if (ctx == NULL)
        return 0;

    memset(&ctx->srp_ctx, 0, sizeof(ctx->srp_ctx));
    ctx->srp_ctx.strength = SRP_MINIMAL_N;

    return 1;
}