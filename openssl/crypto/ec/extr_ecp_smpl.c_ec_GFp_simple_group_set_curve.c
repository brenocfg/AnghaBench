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
struct TYPE_7__ {int a_is_minus3; int /*<<< orphan*/  const* field; int /*<<< orphan*/  const* b; TYPE_1__* meth; int /*<<< orphan*/  const* a; int /*<<< orphan*/  libctx; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* field_encode ) (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new_ex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_add_word (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_is_odd (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_nnmod (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_set_negative (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_F_EC_GFP_SIMPLE_GROUP_SET_CURVE ; 
 int /*<<< orphan*/  EC_R_INVALID_FIELD ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int ec_GFp_simple_group_set_curve(EC_GROUP *group,
                                  const BIGNUM *p, const BIGNUM *a,
                                  const BIGNUM *b, BN_CTX *ctx)
{
    int ret = 0;
    BN_CTX *new_ctx = NULL;
    BIGNUM *tmp_a;

    /* p must be a prime > 3 */
    if (BN_num_bits(p) <= 2 || !BN_is_odd(p)) {
        ECerr(EC_F_EC_GFP_SIMPLE_GROUP_SET_CURVE, EC_R_INVALID_FIELD);
        return 0;
    }

    if (ctx == NULL) {
        ctx = new_ctx = BN_CTX_new_ex(group->libctx);
        if (ctx == NULL)
            return 0;
    }

    BN_CTX_start(ctx);
    tmp_a = BN_CTX_get(ctx);
    if (tmp_a == NULL)
        goto err;

    /* group->field */
    if (!BN_copy(group->field, p))
        goto err;
    BN_set_negative(group->field, 0);

    /* group->a */
    if (!BN_nnmod(tmp_a, a, p, ctx))
        goto err;
    if (group->meth->field_encode) {
        if (!group->meth->field_encode(group, group->a, tmp_a, ctx))
            goto err;
    } else if (!BN_copy(group->a, tmp_a))
        goto err;

    /* group->b */
    if (!BN_nnmod(group->b, b, p, ctx))
        goto err;
    if (group->meth->field_encode)
        if (!group->meth->field_encode(group, group->b, group->b, ctx))
            goto err;

    /* group->a_is_minus3 */
    if (!BN_add_word(tmp_a, 3))
        goto err;
    group->a_is_minus3 = (0 == BN_cmp(tmp_a, group->field));

    ret = 1;

 err:
    BN_CTX_end(ctx);
    BN_CTX_free(new_ctx);
    return ret;
}