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
struct c2_curve_test {int /*<<< orphan*/  degree; int /*<<< orphan*/  name; int /*<<< orphan*/  cof; int /*<<< orphan*/  order; int /*<<< orphan*/  y; int /*<<< orphan*/  y_bit; int /*<<< orphan*/  x; int /*<<< orphan*/  b; int /*<<< orphan*/  a; int /*<<< orphan*/  p; } ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/ * BN_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_hex2bn (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_new () ; 
 scalar_t__ BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_rand (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_rshift1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_negative (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * BN_value_one () ; 
 int /*<<< orphan*/  EC_GF2m_simple_method () ; 
 int /*<<< orphan*/ * EC_GROUP_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_get_degree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_method_of (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EC_GROUP_set_curve (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_set_generator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_dbl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_get_affine_coordinates (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_invert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_is_at_infinity (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_is_on_curve (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_set_affine_coordinates (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_set_compressed_coordinates (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINTs_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int OSSL_NELEM (struct c2_curve_test*) ; 
 int /*<<< orphan*/  TEST_BN_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_even (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_note (char*) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ *) ; 
 struct c2_curve_test* char2_curve_tests ; 
 int /*<<< orphan*/  group_order_tests (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_output_bignum (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int char2_curve_test(int n)
{
    int r = 0;
    BN_CTX *ctx = NULL;
    BIGNUM *p = NULL, *a = NULL, *b = NULL;
    BIGNUM *x = NULL, *y = NULL, *z = NULL, *cof = NULL, *yplusone = NULL;
    EC_GROUP *group = NULL, *variable = NULL;
    EC_POINT *P = NULL, *Q = NULL, *R = NULL;
    const EC_POINT *points[3];
    const BIGNUM *scalars[3];
    struct c2_curve_test *const test = char2_curve_tests + n;

    if (!TEST_ptr(ctx = BN_CTX_new())
        || !TEST_ptr(p = BN_new())
        || !TEST_ptr(a = BN_new())
        || !TEST_ptr(b = BN_new())
        || !TEST_ptr(x = BN_new())
        || !TEST_ptr(y = BN_new())
        || !TEST_ptr(z = BN_new())
        || !TEST_ptr(yplusone = BN_new())
        || !TEST_true(BN_hex2bn(&p, test->p))
        || !TEST_true(BN_hex2bn(&a, test->a))
        || !TEST_true(BN_hex2bn(&b, test->b))
        || !TEST_true(group = EC_GROUP_new(EC_GF2m_simple_method()))
        || !TEST_true(EC_GROUP_set_curve(group, p, a, b, ctx))
        || !TEST_ptr(P = EC_POINT_new(group))
        || !TEST_ptr(Q = EC_POINT_new(group))
        || !TEST_ptr(R = EC_POINT_new(group))
        || !TEST_true(BN_hex2bn(&x, test->x))
        || !TEST_true(BN_hex2bn(&y, test->y))
        || !TEST_true(BN_add(yplusone, y, BN_value_one())))
        goto err;

/* Change test based on whether binary point compression is enabled or not. */
# ifdef OPENSSL_EC_BIN_PT_COMP
    /*
     * When (x, y) is on the curve, (x, y + 1) is, as it happens, not,
     * and therefore setting the coordinates should fail.
     */
    if (!TEST_false(EC_POINT_set_affine_coordinates(group, P, x, yplusone, ctx))
        || !TEST_true(EC_POINT_set_compressed_coordinates(group, P, x,
                                                          test->y_bit,
                                                          ctx))
        || !TEST_int_gt(EC_POINT_is_on_curve(group, P, ctx), 0)
        || !TEST_true(BN_hex2bn(&z, test->order))
        || !TEST_true(BN_hex2bn(&cof, test->cof))
        || !TEST_true(EC_GROUP_set_generator(group, P, z, cof))
        || !TEST_true(EC_POINT_get_affine_coordinates(group, P, x, y, ctx)))
        goto err;
    TEST_info("%s -- Generator", test->name);
    test_output_bignum("x", x);
    test_output_bignum("y", y);
    /* G_y value taken from the standard: */
    if (!TEST_true(BN_hex2bn(&z, test->y))
        || !TEST_BN_eq(y, z))
        goto err;
# else
    /*
     * When (x, y) is on the curve, (x, y + 1) is, as it happens, not,
     * and therefore setting the coordinates should fail.
     */
    if (!TEST_false(EC_POINT_set_affine_coordinates(group, P, x, yplusone, ctx))
        || !TEST_true(EC_POINT_set_affine_coordinates(group, P, x, y, ctx))
        || !TEST_int_gt(EC_POINT_is_on_curve(group, P, ctx), 0)
        || !TEST_true(BN_hex2bn(&z, test->order))
        || !TEST_true(BN_hex2bn(&cof, test->cof))
        || !TEST_true(EC_GROUP_set_generator(group, P, z, cof)))
        goto err;
    TEST_info("%s -- Generator:", test->name);
    test_output_bignum("x", x);
    test_output_bignum("y", y);
# endif

    if (!TEST_int_eq(EC_GROUP_get_degree(group), test->degree)
        || !group_order_tests(group)
        || !TEST_ptr(variable = EC_GROUP_new(EC_GROUP_method_of(group)))
        || !TEST_true(EC_GROUP_copy(variable, group)))
        goto err;

    /* more tests using the last curve */
    if (n == OSSL_NELEM(char2_curve_tests) - 1) {
        if (!TEST_true(EC_POINT_set_affine_coordinates(group, P, x, y, ctx))
            || !TEST_true(EC_POINT_copy(Q, P))
            || !TEST_false(EC_POINT_is_at_infinity(group, Q))
            || !TEST_true(EC_POINT_dbl(group, P, P, ctx))
            || !TEST_int_gt(EC_POINT_is_on_curve(group, P, ctx), 0)
            || !TEST_true(EC_POINT_invert(group, Q, ctx))       /* P = -2Q */
            || !TEST_true(EC_POINT_add(group, R, P, Q, ctx))
            || !TEST_true(EC_POINT_add(group, R, R, Q, ctx))
            || !TEST_true(EC_POINT_is_at_infinity(group, R))   /* R = P + 2Q */
            || !TEST_false(EC_POINT_is_at_infinity(group, Q)))
            goto err;

        points[0] = Q;
        points[1] = Q;
        points[2] = Q;

        if (!TEST_true(BN_add(y, z, BN_value_one()))
            || !TEST_BN_even(y)
            || !TEST_true(BN_rshift1(y, y)))
            goto err;
        scalars[0] = y;         /* (group order + 1)/2, so y*Q + y*Q = Q */
        scalars[1] = y;

        TEST_note("combined multiplication ...");

        /* z is still the group order */
        if (!TEST_true(EC_POINTs_mul(group, P, NULL, 2, points, scalars, ctx))
            || !TEST_true(EC_POINTs_mul(group, R, z, 2, points, scalars, ctx))
            || !TEST_int_eq(0, EC_POINT_cmp(group, P, R, ctx))
            || !TEST_int_eq(0, EC_POINT_cmp(group, R, Q, ctx)))
            goto err;

        if (!TEST_true(BN_rand(y, BN_num_bits(y), 0, 0))
            || !TEST_true(BN_add(z, z, y)))
            goto err;
        BN_set_negative(z, 1);
        scalars[0] = y;
        scalars[1] = z;         /* z = -(order + y) */

        if (!TEST_true(EC_POINTs_mul(group, P, NULL, 2, points, scalars, ctx))
            || !TEST_true(EC_POINT_is_at_infinity(group, P)))
            goto err;

        if (!TEST_true(BN_rand(x, BN_num_bits(y) - 1, 0, 0))
            || !TEST_true(BN_add(z, x, y)))
            goto err;
        BN_set_negative(z, 1);
        scalars[0] = x;
        scalars[1] = y;
        scalars[2] = z;         /* z = -(x+y) */

        if (!TEST_true(EC_POINTs_mul(group, P, NULL, 3, points, scalars, ctx))
            || !TEST_true(EC_POINT_is_at_infinity(group, P)))
            goto err;;
    }

    r = 1;
err:
    BN_CTX_free(ctx);
    BN_free(p);
    BN_free(a);
    BN_free(b);
    BN_free(x);
    BN_free(y);
    BN_free(z);
    BN_free(yplusone);
    BN_free(cof);
    EC_POINT_free(P);
    EC_POINT_free(Q);
    EC_POINT_free(R);
    EC_GROUP_free(group);
    EC_GROUP_free(variable);
    return r;
}