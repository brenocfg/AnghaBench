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
struct nistp_test_params {int /*<<< orphan*/  d; int /*<<< orphan*/  degree; int /*<<< orphan*/  order; int /*<<< orphan*/  Gy; int /*<<< orphan*/  Gx; int /*<<< orphan*/  Qy; int /*<<< orphan*/  Qx; int /*<<< orphan*/  b; int /*<<< orphan*/  a; int /*<<< orphan*/  p; int /*<<< orphan*/  (* meth ) () ;} ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_check_prime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_hex2bn (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_rshift (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_value_one () ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int EC_GROUP_get_degree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_have_precompute_mult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_GROUP_precompute_mult (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_set_curve (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_set_generator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_POINT_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_dbl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_invert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_set_affine_coordinates (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_note (char*,...) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int group_order_tests (int /*<<< orphan*/ *) ; 
 struct nistp_test_params* nistp_tests_params ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int nistp_single_test(int idx)
{
    const struct nistp_test_params *test = nistp_tests_params + idx;
    BN_CTX *ctx = NULL;
    BIGNUM *p = NULL, *a = NULL, *b = NULL, *x = NULL, *y = NULL;
    BIGNUM *n = NULL, *m = NULL, *order = NULL, *yplusone = NULL;
    EC_GROUP *NISTP = NULL;
    EC_POINT *G = NULL, *P = NULL, *Q = NULL, *Q_CHECK = NULL;
    int r = 0;

    TEST_note("NIST curve P-%d (optimised implementation):",
              test->degree);
    if (!TEST_ptr(ctx = BN_CTX_new())
        || !TEST_ptr(p = BN_new())
        || !TEST_ptr(a = BN_new())
        || !TEST_ptr(b = BN_new())
        || !TEST_ptr(x = BN_new())
        || !TEST_ptr(y = BN_new())
        || !TEST_ptr(m = BN_new())
        || !TEST_ptr(n = BN_new())
        || !TEST_ptr(order = BN_new())
        || !TEST_ptr(yplusone = BN_new())

        || !TEST_ptr(NISTP = EC_GROUP_new(test->meth()))
        || !TEST_true(BN_hex2bn(&p, test->p))
        || !TEST_int_eq(1, BN_check_prime(p, ctx, NULL))
        || !TEST_true(BN_hex2bn(&a, test->a))
        || !TEST_true(BN_hex2bn(&b, test->b))
        || !TEST_true(EC_GROUP_set_curve(NISTP, p, a, b, ctx))
        || !TEST_ptr(G = EC_POINT_new(NISTP))
        || !TEST_ptr(P = EC_POINT_new(NISTP))
        || !TEST_ptr(Q = EC_POINT_new(NISTP))
        || !TEST_ptr(Q_CHECK = EC_POINT_new(NISTP))
        || !TEST_true(BN_hex2bn(&x, test->Qx))
        || !TEST_true(BN_hex2bn(&y, test->Qy))
        || !TEST_true(BN_add(yplusone, y, BN_value_one()))
    /*
     * When (x, y) is on the curve, (x, y + 1) is, as it happens, not,
     * and therefore setting the coordinates should fail.
     */
        || !TEST_false(EC_POINT_set_affine_coordinates(NISTP, Q_CHECK, x,
                                                       yplusone, ctx))
        || !TEST_true(EC_POINT_set_affine_coordinates(NISTP, Q_CHECK, x, y,
                                                      ctx))
        || !TEST_true(BN_hex2bn(&x, test->Gx))
        || !TEST_true(BN_hex2bn(&y, test->Gy))
        || !TEST_true(EC_POINT_set_affine_coordinates(NISTP, G, x, y, ctx))
        || !TEST_true(BN_hex2bn(&order, test->order))
        || !TEST_true(EC_GROUP_set_generator(NISTP, G, order, BN_value_one()))
        || !TEST_int_eq(EC_GROUP_get_degree(NISTP), test->degree))
        goto err;

    TEST_note("NIST test vectors ... ");
    if (!TEST_true(BN_hex2bn(&n, test->d)))
        goto err;
    /* fixed point multiplication */
    EC_POINT_mul(NISTP, Q, n, NULL, NULL, ctx);
    if (!TEST_int_eq(0, EC_POINT_cmp(NISTP, Q, Q_CHECK, ctx)))
        goto err;
    /* random point multiplication */
    EC_POINT_mul(NISTP, Q, NULL, G, n, ctx);
    if (!TEST_int_eq(0, EC_POINT_cmp(NISTP, Q, Q_CHECK, ctx))

        /* set generator to P = 2*G, where G is the standard generator */
        || !TEST_true(EC_POINT_dbl(NISTP, P, G, ctx))
        || !TEST_true(EC_GROUP_set_generator(NISTP, P, order, BN_value_one()))
        /* set the scalar to m=n/2, where n is the NIST test scalar */
        || !TEST_true(BN_rshift(m, n, 1)))
        goto err;

    /* test the non-standard generator */
    /* fixed point multiplication */
    EC_POINT_mul(NISTP, Q, m, NULL, NULL, ctx);
    if (!TEST_int_eq(0, EC_POINT_cmp(NISTP, Q, Q_CHECK, ctx)))
        goto err;
    /* random point multiplication */
    EC_POINT_mul(NISTP, Q, NULL, P, m, ctx);
    if (!TEST_int_eq(0, EC_POINT_cmp(NISTP, Q, Q_CHECK, ctx))

    /*
     * We have not performed precomputation so have_precompute mult should be
     * false
     */
        || !TEST_false(EC_GROUP_have_precompute_mult(NISTP))

    /* now repeat all tests with precomputation */
        || !TEST_true(EC_GROUP_precompute_mult(NISTP, ctx))
        || !TEST_true(EC_GROUP_have_precompute_mult(NISTP)))
        goto err;

    /* fixed point multiplication */
    EC_POINT_mul(NISTP, Q, m, NULL, NULL, ctx);
    if (!TEST_int_eq(0, EC_POINT_cmp(NISTP, Q, Q_CHECK, ctx)))
        goto err;
    /* random point multiplication */
    EC_POINT_mul(NISTP, Q, NULL, P, m, ctx);
    if (!TEST_int_eq(0, EC_POINT_cmp(NISTP, Q, Q_CHECK, ctx))

    /* reset generator */
        || !TEST_true(EC_GROUP_set_generator(NISTP, G, order, BN_value_one())))
        goto err;
    /* fixed point multiplication */
    EC_POINT_mul(NISTP, Q, n, NULL, NULL, ctx);
    if (!TEST_int_eq(0, EC_POINT_cmp(NISTP, Q, Q_CHECK, ctx)))
        goto err;
    /* random point multiplication */
    EC_POINT_mul(NISTP, Q, NULL, G, n, ctx);
    if (!TEST_int_eq(0, EC_POINT_cmp(NISTP, Q, Q_CHECK, ctx)))
        goto err;

    /* regression test for felem_neg bug */
    if (!TEST_true(BN_set_word(m, 32))
        || !TEST_true(BN_set_word(n, 31))
        || !TEST_true(EC_POINT_copy(P, G))
        || !TEST_true(EC_POINT_invert(NISTP, P, ctx))
        || !TEST_true(EC_POINT_mul(NISTP, Q, m, P, n, ctx))
        || !TEST_int_eq(0, EC_POINT_cmp(NISTP, Q, G, ctx)))
      goto err;

    r = group_order_tests(NISTP);
err:
    EC_GROUP_free(NISTP);
    EC_POINT_free(G);
    EC_POINT_free(P);
    EC_POINT_free(Q);
    EC_POINT_free(Q_CHECK);
    BN_free(n);
    BN_free(m);
    BN_free(p);
    BN_free(a);
    BN_free(b);
    BN_free(x);
    BN_free(y);
    BN_free(order);
    BN_free(yplusone);
    BN_CTX_free(ctx);
    return r;
}