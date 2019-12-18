#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int Z_is_one; int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
typedef  TYPE_1__ EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_set_negative (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* BN_value_one () ; 
 int /*<<< orphan*/  EC_F_EC_GF2M_SIMPLE_POINT_SET_AFFINE_COORDINATES ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 

int ec_GF2m_simple_point_set_affine_coordinates(const EC_GROUP *group,
                                                EC_POINT *point,
                                                const BIGNUM *x,
                                                const BIGNUM *y, BN_CTX *ctx)
{
    int ret = 0;
    if (x == NULL || y == NULL) {
        ECerr(EC_F_EC_GF2M_SIMPLE_POINT_SET_AFFINE_COORDINATES,
              ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }

    if (!BN_copy(point->X, x))
        goto err;
    BN_set_negative(point->X, 0);
    if (!BN_copy(point->Y, y))
        goto err;
    BN_set_negative(point->Y, 0);
    if (!BN_copy(point->Z, BN_value_one()))
        goto err;
    BN_set_negative(point->Z, 0);
    point->Z_is_one = 1;
    ret = 1;

 err:
    return ret;
}