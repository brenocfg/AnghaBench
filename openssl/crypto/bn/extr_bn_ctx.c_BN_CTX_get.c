#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int too_many; int /*<<< orphan*/  used; int /*<<< orphan*/  flags; int /*<<< orphan*/  pool; scalar_t__ err_stack; } ;
typedef  TYPE_1__ BN_CTX ;
typedef  TYPE_2__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int /*<<< orphan*/  BN_F_BN_CTX_GET ; 
 TYPE_2__* BN_POOL_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_R_TOO_MANY_TEMPORARY_VARIABLES ; 
 int /*<<< orphan*/  BN_zero (TYPE_2__*) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTXDBG (char*,TYPE_1__*) ; 

BIGNUM *BN_CTX_get(BN_CTX *ctx)
{
    BIGNUM *ret;

    CTXDBG("ENTER BN_CTX_get()", ctx);
    if (ctx->err_stack || ctx->too_many)
        return NULL;
    if ((ret = BN_POOL_get(&ctx->pool, ctx->flags)) == NULL) {
        /*
         * Setting too_many prevents repeated "get" attempts from cluttering
         * the error stack.
         */
        ctx->too_many = 1;
        BNerr(BN_F_BN_CTX_GET, BN_R_TOO_MANY_TEMPORARY_VARIABLES);
        return NULL;
    }
    /* OK, make sure the returned bignum is "zero" */
    BN_zero(ret);
    /* clear BN_FLG_CONSTTIME if leaked from previous frames */
    ret->flags &= (~BN_FLG_CONSTTIME);
    ctx->used++;
    CTXDBG("LEAVE BN_CTX_get()", ctx);
    return ret;
}