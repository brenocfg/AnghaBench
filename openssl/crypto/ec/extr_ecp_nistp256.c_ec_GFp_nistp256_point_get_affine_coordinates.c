#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  smallfelem ;
typedef  int /*<<< orphan*/  longfelem ;
typedef  int /*<<< orphan*/  felem ;
struct TYPE_4__ {int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
typedef  TYPE_1__ EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_to_felem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_F_EC_GFP_NISTP256_POINT_GET_AFFINE_COORDINATES ; 
 scalar_t__ EC_POINT_is_at_infinity (int /*<<< orphan*/  const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  EC_R_POINT_AT_INFINITY ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  felem_contract (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  felem_inv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  felem_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  felem_reduce (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  felem_square (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smallfelem_to_BN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ec_GFp_nistp256_point_get_affine_coordinates(const EC_GROUP *group,
                                                 const EC_POINT *point,
                                                 BIGNUM *x, BIGNUM *y,
                                                 BN_CTX *ctx)
{
    felem z1, z2, x_in, y_in;
    smallfelem x_out, y_out;
    longfelem tmp;

    if (EC_POINT_is_at_infinity(group, point)) {
        ECerr(EC_F_EC_GFP_NISTP256_POINT_GET_AFFINE_COORDINATES,
              EC_R_POINT_AT_INFINITY);
        return 0;
    }
    if ((!BN_to_felem(x_in, point->X)) || (!BN_to_felem(y_in, point->Y)) ||
        (!BN_to_felem(z1, point->Z)))
        return 0;
    felem_inv(z2, z1);
    felem_square(tmp, z2);
    felem_reduce(z1, tmp);
    felem_mul(tmp, x_in, z1);
    felem_reduce(x_in, tmp);
    felem_contract(x_out, x_in);
    if (x != NULL) {
        if (!smallfelem_to_BN(x, x_out)) {
            ECerr(EC_F_EC_GFP_NISTP256_POINT_GET_AFFINE_COORDINATES,
                  ERR_R_BN_LIB);
            return 0;
        }
    }
    felem_mul(tmp, z1, z2);
    felem_reduce(z1, tmp);
    felem_mul(tmp, y_in, z1);
    felem_reduce(y_in, tmp);
    felem_contract(y_out, y_in);
    if (y != NULL) {
        if (!smallfelem_to_BN(y, y_out)) {
            ECerr(EC_F_EC_GFP_NISTP256_POINT_GET_AFFINE_COORDINATES,
                  ERR_R_BN_LIB);
            return 0;
        }
    }
    return 1;
}