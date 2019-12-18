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
typedef  int /*<<< orphan*/  const EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  const BN_CTX ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* BN_CTX_new () ; 
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* BN_new () ; 
 int /*<<< orphan*/  BN_one (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_set_negative (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* BN_value_one () ; 
 int /*<<< orphan*/  const* EC_GROUP_get0_generator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_get_order (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_GROUP_precompute_mult (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_add (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_dbl (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_invert (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_is_at_infinity (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_mul (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* EC_POINT_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINTs_mul (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_info (char*) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int group_order_tests(EC_GROUP *group)
{
    BIGNUM *n1 = NULL, *n2 = NULL, *order = NULL;
    EC_POINT *P = NULL, *Q = NULL, *R = NULL, *S = NULL;
    const EC_POINT *G = NULL;
    BN_CTX *ctx = NULL;
    int i = 0, r = 0;

    if (!TEST_ptr(n1 = BN_new())
        || !TEST_ptr(n2 = BN_new())
        || !TEST_ptr(order = BN_new())
        || !TEST_ptr(ctx = BN_CTX_new())
        || !TEST_ptr(G = EC_GROUP_get0_generator(group))
        || !TEST_ptr(P = EC_POINT_new(group))
        || !TEST_ptr(Q = EC_POINT_new(group))
        || !TEST_ptr(R = EC_POINT_new(group))
        || !TEST_ptr(S = EC_POINT_new(group)))
        goto err;

    if (!TEST_true(EC_GROUP_get_order(group, order, ctx))
        || !TEST_true(EC_POINT_mul(group, Q, order, NULL, NULL, ctx))
        || !TEST_true(EC_POINT_is_at_infinity(group, Q))
        || !TEST_true(EC_GROUP_precompute_mult(group, ctx))
        || !TEST_true(EC_POINT_mul(group, Q, order, NULL, NULL, ctx))
        || !TEST_true(EC_POINT_is_at_infinity(group, Q))
        || !TEST_true(EC_POINT_copy(P, G))
        || !TEST_true(BN_one(n1))
        || !TEST_true(EC_POINT_mul(group, Q, n1, NULL, NULL, ctx))
        || !TEST_int_eq(0, EC_POINT_cmp(group, Q, P, ctx))
        || !TEST_true(BN_sub(n1, order, n1))
        || !TEST_true(EC_POINT_mul(group, Q, n1, NULL, NULL, ctx))
        || !TEST_true(EC_POINT_invert(group, Q, ctx))
        || !TEST_int_eq(0, EC_POINT_cmp(group, Q, P, ctx)))
        goto err;

    for (i = 1; i <= 2; i++) {
        const BIGNUM *scalars[6];
        const EC_POINT *points[6];

        if (!TEST_true(BN_set_word(n1, i))
            /*
             * If i == 1, P will be the predefined generator for which
             * EC_GROUP_precompute_mult has set up precomputation.
             */
            || !TEST_true(EC_POINT_mul(group, P, n1, NULL, NULL, ctx))
            || (i == 1 && !TEST_int_eq(0, EC_POINT_cmp(group, P, G, ctx)))
            || !TEST_true(BN_one(n1))
            /* n1 = 1 - order */
            || !TEST_true(BN_sub(n1, n1, order))
            || !TEST_true(EC_POINT_mul(group, Q, NULL, P, n1, ctx))
            || !TEST_int_eq(0, EC_POINT_cmp(group, Q, P, ctx))

            /* n2 = 1 + order */
            || !TEST_true(BN_add(n2, order, BN_value_one()))
            || !TEST_true(EC_POINT_mul(group, Q, NULL, P, n2, ctx))
            || !TEST_int_eq(0, EC_POINT_cmp(group, Q, P, ctx))

            /* n2 = (1 - order) * (1 + order) = 1 - order^2 */
            || !TEST_true(BN_mul(n2, n1, n2, ctx))
            || !TEST_true(EC_POINT_mul(group, Q, NULL, P, n2, ctx))
            || !TEST_int_eq(0, EC_POINT_cmp(group, Q, P, ctx)))
            goto err;

        /* n2 = order^2 - 1 */
        BN_set_negative(n2, 0);
        if (!TEST_true(EC_POINT_mul(group, Q, NULL, P, n2, ctx))
            /* Add P to verify the result. */
            || !TEST_true(EC_POINT_add(group, Q, Q, P, ctx))
            || !TEST_true(EC_POINT_is_at_infinity(group, Q))

            /* Exercise EC_POINTs_mul, including corner cases. */
            || !TEST_false(EC_POINT_is_at_infinity(group, P)))
            goto err;

        scalars[0] = scalars[1] = BN_value_one();
        points[0]  = points[1]  = P;

        if (!TEST_true(EC_POINTs_mul(group, R, NULL, 2, points, scalars, ctx))
            || !TEST_true(EC_POINT_dbl(group, S, points[0], ctx))
            || !TEST_int_eq(0, EC_POINT_cmp(group, R, S, ctx)))
            goto err;

        scalars[0] = n1;
        points[0] = Q;          /* => infinity */
        scalars[1] = n2;
        points[1] = P;          /* => -P */
        scalars[2] = n1;
        points[2] = Q;          /* => infinity */
        scalars[3] = n2;
        points[3] = Q;          /* => infinity */
        scalars[4] = n1;
        points[4] = P;          /* => P */
        scalars[5] = n2;
        points[5] = Q;          /* => infinity */
        if (!TEST_true(EC_POINTs_mul(group, P, NULL, 6, points, scalars, ctx))
            || !TEST_true(EC_POINT_is_at_infinity(group, P)))
            goto err;
    }

    r = 1;
err:
    if (r == 0 && i != 0)
        TEST_info(i == 1 ? "allowing precomputation" :
                           "without precomputation");
    EC_POINT_free(P);
    EC_POINT_free(Q);
    EC_POINT_free(R);
    EC_POINT_free(S);
    BN_free(n1);
    BN_free(n2);
    BN_free(order);
    BN_CTX_free(ctx);
    return r;
}