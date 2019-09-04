#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * field; TYPE_1__* meth; } ;
struct TYPE_12__ {int (* field_inv ) (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int (* field_mul ) (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int (* field_encode ) (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int (* field_decode ) (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_RAND_BOTTOM_ANY ; 
 int /*<<< orphan*/  BN_RAND_TOP_ONE ; 
 int BN_is_one (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_num_bits (int /*<<< orphan*/ *) ; 
 int BN_pseudo_rand (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_value_one () ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ EC_R_CANNOT_INVERT ; 
 scalar_t__ ERR_GET_LIB (int /*<<< orphan*/ ) ; 
 scalar_t__ ERR_GET_REASON (int /*<<< orphan*/ ) ; 
 scalar_t__ ERR_LIB_EC ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  ERR_peek_last_error () ; 
 int /*<<< orphan*/  TEST_false (int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 int stub1 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub2 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub3 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub4 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub5 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub6 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub7 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub8 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int group_field_tests(const EC_GROUP *group, BN_CTX *ctx)
{
    BIGNUM *a = NULL, *b = NULL, *c = NULL;
    int ret = 0;

    if (group->meth->field_inv == NULL || group->meth->field_mul == NULL)
        return 1;

    BN_CTX_start(ctx);
    a = BN_CTX_get(ctx);
    b = BN_CTX_get(ctx);
    if (!TEST_ptr(c = BN_CTX_get(ctx))
        /* 1/1 = 1 */
        || !TEST_true(group->meth->field_inv(group, b, BN_value_one(), ctx))
        || !TEST_true(BN_is_one(b))
        /* (1/a)*a = 1 */
        || !TEST_true(BN_pseudo_rand(a, BN_num_bits(group->field) - 1,
                                     BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ANY))
        || !TEST_true(group->meth->field_inv(group, b, a, ctx))
        || (group->meth->field_encode &&
            !TEST_true(group->meth->field_encode(group, a, a, ctx)))
        || (group->meth->field_encode &&
            !TEST_true(group->meth->field_encode(group, b, b, ctx)))
        || !TEST_true(group->meth->field_mul(group, c, a, b, ctx))
        || (group->meth->field_decode &&
            !TEST_true(group->meth->field_decode(group, c, c, ctx)))
        || !TEST_true(BN_is_one(c)))
        goto err;

    /* 1/0 = error */
    BN_zero(a);
    if (!TEST_false(group->meth->field_inv(group, b, a, ctx))
        || !TEST_true(ERR_GET_LIB(ERR_peek_last_error()) == ERR_LIB_EC)
        || !TEST_true(ERR_GET_REASON(ERR_peek_last_error()) ==
                      EC_R_CANNOT_INVERT)
        /* 1/p = error */
        || !TEST_false(group->meth->field_inv(group, b, group->field, ctx))
        || !TEST_true(ERR_GET_LIB(ERR_peek_last_error()) == ERR_LIB_EC)
        || !TEST_true(ERR_GET_REASON(ERR_peek_last_error()) ==
                      EC_R_CANNOT_INVERT))
        goto err;

    ERR_clear_error();
    ret = 1;
 err:
    BN_CTX_end(ctx);
    return ret;
}