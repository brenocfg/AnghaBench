#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* meth; } ;
struct TYPE_8__ {int (* mul ) (TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  const EC_POINT ;
typedef  TYPE_2__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_secure_new () ; 
 int /*<<< orphan*/  EC_F_EC_POINTS_MUL ; 
 int EC_POINT_set_to_infinity (TYPE_2__ const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_R_INCOMPATIBLE_OBJECTS ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ec_point_is_compat (int /*<<< orphan*/  const*,TYPE_2__ const*) ; 
 int ec_wNAF_mul (TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 

int EC_POINTs_mul(const EC_GROUP *group, EC_POINT *r, const BIGNUM *scalar,
                  size_t num, const EC_POINT *points[],
                  const BIGNUM *scalars[], BN_CTX *ctx)
{
    int ret = 0;
    size_t i = 0;
    BN_CTX *new_ctx = NULL;

    if ((scalar == NULL) && (num == 0)) {
        return EC_POINT_set_to_infinity(group, r);
    }

    if (!ec_point_is_compat(r, group)) {
        ECerr(EC_F_EC_POINTS_MUL, EC_R_INCOMPATIBLE_OBJECTS);
        return 0;
    }
    for (i = 0; i < num; i++) {
        if (!ec_point_is_compat(points[i], group)) {
            ECerr(EC_F_EC_POINTS_MUL, EC_R_INCOMPATIBLE_OBJECTS);
            return 0;
        }
    }

    if (ctx == NULL && (ctx = new_ctx = BN_CTX_secure_new()) == NULL) {
        ECerr(EC_F_EC_POINTS_MUL, ERR_R_INTERNAL_ERROR);
        return 0;
    }

    if (group->meth->mul != NULL)
        ret = group->meth->mul(group, r, scalar, num, points, scalars, ctx);
    else
        /* use default */
        ret = ec_wNAF_mul(group, r, scalar, num, points, scalars, ctx);

    BN_CTX_free(new_ctx);
    return ret;
}