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
typedef  scalar_t__ intmax_t ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  EC_POINT_get_affine_coordinates (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BIGNUM *walk_curve(const EC_GROUP *group, EC_POINT *point, intmax_t num)
{
    BIGNUM *scalar = NULL;
    intmax_t i;

    if (!TEST_ptr(scalar = BN_new())
            || !TEST_true(EC_POINT_get_affine_coordinates(group, point, scalar,
                                                          NULL, NULL)))
        goto err;

    for (i = 0; i < num; i++) {
        if (!TEST_true(EC_POINT_mul(group, point, NULL, point, scalar, NULL))
                || !TEST_true(EC_POINT_get_affine_coordinates(group, point,
                                                              scalar,
                                                              NULL, NULL)))
            goto err;
    }
    return scalar;

err:
    BN_free(scalar);
    return NULL;
}