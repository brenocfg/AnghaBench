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
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_hex2bn (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_new_by_curve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_POINT_dbl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_get_affine_coordinates (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_set_Jprojective_coordinates_GFp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NID_secp521r1 ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int underflow_test(void)
{
    BN_CTX *ctx = NULL;
    EC_GROUP *grp = NULL;
    EC_POINT *P = NULL, *Q = NULL, *R = NULL;
    BIGNUM *x1 = NULL, *y1 = NULL, *z1 = NULL, *x2 = NULL, *y2 = NULL;
    BIGNUM *k = NULL;
    int testresult = 0;
    const char *x1str =
        "1534f0077fffffe87e9adcfe000000000000000000003e05a21d2400002e031b1f4"
        "b80000c6fafa4f3c1288798d624a247b5e2ffffffffffffffefe099241900004";
    const char *p521m1 =
        "1ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
        "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffe";

    ctx = BN_CTX_new();
    if (!TEST_ptr(ctx))
        return 0;

    BN_CTX_start(ctx);
    x1 = BN_CTX_get(ctx);
    y1 = BN_CTX_get(ctx);
    z1 = BN_CTX_get(ctx);
    x2 = BN_CTX_get(ctx);
    y2 = BN_CTX_get(ctx);
    k = BN_CTX_get(ctx);
    if (!TEST_ptr(k))
        goto err;

    grp = EC_GROUP_new_by_curve_name(NID_secp521r1);
    P = EC_POINT_new(grp);
    Q = EC_POINT_new(grp);
    R = EC_POINT_new(grp);
    if (!TEST_ptr(grp) || !TEST_ptr(P) || !TEST_ptr(Q) || !TEST_ptr(R))
        goto err;

    if (!TEST_int_gt(BN_hex2bn(&x1, x1str), 0)
            || !TEST_int_gt(BN_hex2bn(&y1, p521m1), 0)
            || !TEST_int_gt(BN_hex2bn(&z1, p521m1), 0)
            || !TEST_int_gt(BN_hex2bn(&k, "02"), 0)
            || !TEST_true(EC_POINT_set_Jprojective_coordinates_GFp(grp, P, x1,
                                                                   y1, z1, ctx))
            || !TEST_true(EC_POINT_mul(grp, Q, NULL, P, k, ctx))
            || !TEST_true(EC_POINT_get_affine_coordinates(grp, Q, x1, y1, ctx))
            || !TEST_true(EC_POINT_dbl(grp, R, P, ctx))
            || !TEST_true(EC_POINT_get_affine_coordinates(grp, R, x2, y2, ctx)))
        goto err;

    if (!TEST_int_eq(BN_cmp(x1, x2), 0)
            || !TEST_int_eq(BN_cmp(y1, y2), 0))
        goto err;

    testresult = 1;

 err:
    BN_CTX_end(ctx);
    EC_POINT_free(P);
    EC_POINT_free(Q);
    EC_POINT_free(R);
    EC_GROUP_free(grp);
    BN_CTX_free(ctx);

    return testresult;
}