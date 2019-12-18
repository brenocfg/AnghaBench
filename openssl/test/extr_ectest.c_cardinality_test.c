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
struct TYPE_2__ {int nid; } ;
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
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_lshift (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_value_one () ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_get0_generator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_get0_order (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_get_cofactor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_get_curve (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_method_of (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EC_GROUP_new_by_curve_name (int) ; 
 int /*<<< orphan*/  EC_GROUP_set_curve (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_set_generator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_get_affine_coordinates (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_set_affine_coordinates (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_nid2sn (int) ; 
 int /*<<< orphan*/  TEST_BN_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 TYPE_1__* curves ; 

__attribute__((used)) static int cardinality_test(int n)
{
    int ret = 0;
    int nid = curves[n].nid;
    BN_CTX *ctx = NULL;
    EC_GROUP *g1 = NULL, *g2 = NULL;
    EC_POINT *g2_gen = NULL;
    BIGNUM *g1_p = NULL, *g1_a = NULL, *g1_b = NULL, *g1_x = NULL, *g1_y = NULL,
           *g1_order = NULL, *g1_cf = NULL, *g2_cf = NULL;

    TEST_info("Curve %s cardinality test", OBJ_nid2sn(nid));

    if (!TEST_ptr(ctx = BN_CTX_new())
        || !TEST_ptr(g1 = EC_GROUP_new_by_curve_name(nid))
        || !TEST_ptr(g2 = EC_GROUP_new(EC_GROUP_method_of(g1)))) {
        EC_GROUP_free(g1);
        EC_GROUP_free(g2);
        BN_CTX_free(ctx);
        return 0;
    }

    BN_CTX_start(ctx);
    g1_p = BN_CTX_get(ctx);
    g1_a = BN_CTX_get(ctx);
    g1_b = BN_CTX_get(ctx);
    g1_x = BN_CTX_get(ctx);
    g1_y = BN_CTX_get(ctx);
    g1_order = BN_CTX_get(ctx);
    g1_cf = BN_CTX_get(ctx);

    if (!TEST_ptr(g2_cf = BN_CTX_get(ctx))
        /* pull out the explicit curve parameters */
        || !TEST_true(EC_GROUP_get_curve(g1, g1_p, g1_a, g1_b, ctx))
        || !TEST_true(EC_POINT_get_affine_coordinates(g1,
                      EC_GROUP_get0_generator(g1), g1_x, g1_y, ctx))
        || !TEST_true(BN_copy(g1_order, EC_GROUP_get0_order(g1)))
        || !TEST_true(EC_GROUP_get_cofactor(g1, g1_cf, ctx))
        /* construct g2 manually with g1 parameters */
        || !TEST_true(EC_GROUP_set_curve(g2, g1_p, g1_a, g1_b, ctx))
        || !TEST_ptr(g2_gen = EC_POINT_new(g2))
        || !TEST_true(EC_POINT_set_affine_coordinates(g2, g2_gen, g1_x, g1_y, ctx))
        /* pass NULL cofactor: lib should compute it */
        || !TEST_true(EC_GROUP_set_generator(g2, g2_gen, g1_order, NULL))
        || !TEST_true(EC_GROUP_get_cofactor(g2, g2_cf, ctx))
        || !TEST_BN_eq(g1_cf, g2_cf)
        /* pass zero cofactor: lib should compute it */
        || !TEST_true(BN_set_word(g2_cf, 0))
        || !TEST_true(EC_GROUP_set_generator(g2, g2_gen, g1_order, g2_cf))
        || !TEST_true(EC_GROUP_get_cofactor(g2, g2_cf, ctx))
        || !TEST_BN_eq(g1_cf, g2_cf)
        /* negative test for invalid cofactor */
        || !TEST_true(BN_set_word(g2_cf, 0))
        || !TEST_true(BN_sub(g2_cf, g2_cf, BN_value_one()))
        || !TEST_false(EC_GROUP_set_generator(g2, g2_gen, g1_order, g2_cf))
        /* negative test for NULL order */
        || !TEST_false(EC_GROUP_set_generator(g2, g2_gen, NULL, NULL))
        /* negative test for zero order */
        || !TEST_true(BN_set_word(g1_order, 0))
        || !TEST_false(EC_GROUP_set_generator(g2, g2_gen, g1_order, NULL))
        /* negative test for negative order */
        || !TEST_true(BN_set_word(g2_cf, 0))
        || !TEST_true(BN_sub(g2_cf, g2_cf, BN_value_one()))
        || !TEST_false(EC_GROUP_set_generator(g2, g2_gen, g1_order, NULL))
        /* negative test for too large order */
        || !TEST_true(BN_lshift(g1_order, g1_p, 2))
        || !TEST_false(EC_GROUP_set_generator(g2, g2_gen, g1_order, NULL)))
        goto err;
    ret = 1;
 err:
    EC_POINT_free(g2_gen);
    EC_GROUP_free(g1);
    EC_GROUP_free(g2);
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    return ret;
}