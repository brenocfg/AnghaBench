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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_hex2bn (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_new_curve_GFp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_set_generator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_set_affine_coordinates (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static EC_GROUP *create_EC_group(const char *p_hex, const char *a_hex,
                                 const char *b_hex, const char *x_hex,
                                 const char *y_hex, const char *order_hex,
                                 const char *cof_hex)
{
    BIGNUM *p = NULL;
    BIGNUM *a = NULL;
    BIGNUM *b = NULL;
    BIGNUM *g_x = NULL;
    BIGNUM *g_y = NULL;
    BIGNUM *order = NULL;
    BIGNUM *cof = NULL;
    EC_POINT *generator = NULL;
    EC_GROUP *group = NULL;
    int ok = 0;

    if (!TEST_true(BN_hex2bn(&p, p_hex))
            || !TEST_true(BN_hex2bn(&a, a_hex))
            || !TEST_true(BN_hex2bn(&b, b_hex)))
        goto done;

    group = EC_GROUP_new_curve_GFp(p, a, b, NULL);
    if (!TEST_ptr(group))
        goto done;

    generator = EC_POINT_new(group);
    if (!TEST_ptr(generator))
        goto done;

    if (!TEST_true(BN_hex2bn(&g_x, x_hex))
            || !TEST_true(BN_hex2bn(&g_y, y_hex))
            || !TEST_true(EC_POINT_set_affine_coordinates(group, generator, g_x,
                                                          g_y, NULL)))
        goto done;

    if (!TEST_true(BN_hex2bn(&order, order_hex))
            || !TEST_true(BN_hex2bn(&cof, cof_hex))
            || !TEST_true(EC_GROUP_set_generator(group, generator, order, cof)))
        goto done;

    ok = 1;
done:
    BN_free(p);
    BN_free(a);
    BN_free(b);
    BN_free(g_x);
    BN_free(g_y);
    EC_POINT_free(generator);
    BN_free(order);
    BN_free(cof);
    if (!ok) {
        EC_GROUP_free(group);
        group = NULL;
    }

    return group;
}