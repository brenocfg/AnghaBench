#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  b; int /*<<< orphan*/  a; TYPE_1__* meth; int /*<<< orphan*/ * field; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* field_decode ) (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_lshift (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_mod_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_sqr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mul_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EC_F_EC_GFP_SIMPLE_GROUP_CHECK_DISCRIMINANT ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  stub1 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ec_GFp_simple_group_check_discriminant(const EC_GROUP *group, BN_CTX *ctx)
{
    int ret = 0;
    BIGNUM *a, *b, *order, *tmp_1, *tmp_2;
    const BIGNUM *p = group->field;
    BN_CTX *new_ctx = NULL;

    if (ctx == NULL) {
        ctx = new_ctx = BN_CTX_new();
        if (ctx == NULL) {
            ECerr(EC_F_EC_GFP_SIMPLE_GROUP_CHECK_DISCRIMINANT,
                  ERR_R_MALLOC_FAILURE);
            goto err;
        }
    }
    BN_CTX_start(ctx);
    a = BN_CTX_get(ctx);
    b = BN_CTX_get(ctx);
    tmp_1 = BN_CTX_get(ctx);
    tmp_2 = BN_CTX_get(ctx);
    order = BN_CTX_get(ctx);
    if (order == NULL)
        goto err;

    if (group->meth->field_decode) {
        if (!group->meth->field_decode(group, a, group->a, ctx))
            goto err;
        if (!group->meth->field_decode(group, b, group->b, ctx))
            goto err;
    } else {
        if (!BN_copy(a, group->a))
            goto err;
        if (!BN_copy(b, group->b))
            goto err;
    }

    /*-
     * check the discriminant:
     * y^2 = x^3 + a*x + b is an elliptic curve <=> 4*a^3 + 27*b^2 != 0 (mod p)
     * 0 =< a, b < p
     */
    if (BN_is_zero(a)) {
        if (BN_is_zero(b))
            goto err;
    } else if (!BN_is_zero(b)) {
        if (!BN_mod_sqr(tmp_1, a, p, ctx))
            goto err;
        if (!BN_mod_mul(tmp_2, tmp_1, a, p, ctx))
            goto err;
        if (!BN_lshift(tmp_1, tmp_2, 2))
            goto err;
        /* tmp_1 = 4*a^3 */

        if (!BN_mod_sqr(tmp_2, b, p, ctx))
            goto err;
        if (!BN_mul_word(tmp_2, 27))
            goto err;
        /* tmp_2 = 27*b^2 */

        if (!BN_mod_add(a, tmp_1, tmp_2, p, ctx))
            goto err;
        if (BN_is_zero(a))
            goto err;
    }
    ret = 1;

 err:
    BN_CTX_end(ctx);
    BN_CTX_free(new_ctx);
    return ret;
}