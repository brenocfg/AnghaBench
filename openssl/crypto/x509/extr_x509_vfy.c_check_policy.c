#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int (* verify_cb ) (int,TYPE_2__*) ;int /*<<< orphan*/ * current_cert; TYPE_1__* param; void* error; int /*<<< orphan*/  chain; scalar_t__ bare_ta_signed; int /*<<< orphan*/  explicit_policy; int /*<<< orphan*/  tree; scalar_t__ parent; } ;
typedef  TYPE_2__ X509_STORE_CTX ;
struct TYPE_12__ {int ex_flags; } ;
typedef  TYPE_3__ X509 ;
struct TYPE_10__ {int flags; int /*<<< orphan*/  policies; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int EXFLAG_INVALID_POLICY ; 
 int /*<<< orphan*/  X509_F_CHECK_POLICY ; 
 int X509_PCY_TREE_FAILURE ; 
 int X509_PCY_TREE_INTERNAL ; 
 int X509_PCY_TREE_INVALID ; 
 int X509_PCY_TREE_VALID ; 
 int /*<<< orphan*/  X509_V_ERR_INVALID_POLICY_EXTENSION ; 
 void* X509_V_ERR_NO_EXPLICIT_POLICY ; 
 void* X509_V_ERR_OUT_OF_MEM ; 
 int X509_V_FLAG_NOTIFY_POLICY ; 
 int X509_policy_check (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sk_X509_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* sk_X509_value (int /*<<< orphan*/ ,int) ; 
 int stub1 (int,TYPE_2__*) ; 
 int stub2 (int,TYPE_2__*) ; 
 int /*<<< orphan*/  verify_cb_cert (TYPE_2__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_policy(X509_STORE_CTX *ctx)
{
    int ret;

    if (ctx->parent)
        return 1;
    /*
     * With DANE, the trust anchor might be a bare public key, not a
     * certificate!  In that case our chain does not have the trust anchor
     * certificate as a top-most element.  This comports well with RFC5280
     * chain verification, since there too, the trust anchor is not part of the
     * chain to be verified.  In particular, X509_policy_check() does not look
     * at the TA cert, but assumes that it is present as the top-most chain
     * element.  We therefore temporarily push a NULL cert onto the chain if it
     * was verified via a bare public key, and pop it off right after the
     * X509_policy_check() call.
     */
    if (ctx->bare_ta_signed && !sk_X509_push(ctx->chain, NULL)) {
        X509err(X509_F_CHECK_POLICY, ERR_R_MALLOC_FAILURE);
        ctx->error = X509_V_ERR_OUT_OF_MEM;
        return 0;
    }
    ret = X509_policy_check(&ctx->tree, &ctx->explicit_policy, ctx->chain,
                            ctx->param->policies, ctx->param->flags);
    if (ctx->bare_ta_signed)
        sk_X509_pop(ctx->chain);

    if (ret == X509_PCY_TREE_INTERNAL) {
        X509err(X509_F_CHECK_POLICY, ERR_R_MALLOC_FAILURE);
        ctx->error = X509_V_ERR_OUT_OF_MEM;
        return 0;
    }
    /* Invalid or inconsistent extensions */
    if (ret == X509_PCY_TREE_INVALID) {
        int i;

        /* Locate certificates with bad extensions and notify callback. */
        for (i = 1; i < sk_X509_num(ctx->chain); i++) {
            X509 *x = sk_X509_value(ctx->chain, i);

            if (!(x->ex_flags & EXFLAG_INVALID_POLICY))
                continue;
            if (!verify_cb_cert(ctx, x, i,
                                X509_V_ERR_INVALID_POLICY_EXTENSION))
                return 0;
        }
        return 1;
    }
    if (ret == X509_PCY_TREE_FAILURE) {
        ctx->current_cert = NULL;
        ctx->error = X509_V_ERR_NO_EXPLICIT_POLICY;
        return ctx->verify_cb(0, ctx);
    }
    if (ret != X509_PCY_TREE_VALID) {
        X509err(X509_F_CHECK_POLICY, ERR_R_INTERNAL_ERROR);
        return 0;
    }

    if (ctx->param->flags & X509_V_FLAG_NOTIFY_POLICY) {
        ctx->current_cert = NULL;
        /*
         * Verification errors need to be "sticky", a callback may have allowed
         * an SSL handshake to continue despite an error, and we must then
         * remain in an error state.  Therefore, we MUST NOT clear earlier
         * verification errors by setting the error to X509_V_OK.
         */
        if (!ctx->verify_cb(2, ctx))
            return 0;
    }

    return 1;
}