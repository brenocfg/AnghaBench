#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int Z_is_one; int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
typedef  TYPE_1__ EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_one (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_POINT_get_affine_coordinates (int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EC_POINT_is_at_infinity (int /*<<< orphan*/  const*,TYPE_1__*) ; 

int ec_GF2m_simple_make_affine(const EC_GROUP *group, EC_POINT *point,
                               BN_CTX *ctx)
{
    BIGNUM *x, *y;
    int ret = 0;
#ifndef FIPS_MODE
    BN_CTX *new_ctx = NULL;
#endif

    if (point->Z_is_one || EC_POINT_is_at_infinity(group, point))
        return 1;

#ifndef FIPS_MODE
    if (ctx == NULL) {
        ctx = new_ctx = BN_CTX_new();
        if (ctx == NULL)
            return 0;
    }
#endif

    BN_CTX_start(ctx);
    x = BN_CTX_get(ctx);
    y = BN_CTX_get(ctx);
    if (y == NULL)
        goto err;

    if (!EC_POINT_get_affine_coordinates(group, point, x, y, ctx))
        goto err;
    if (!BN_copy(point->X, x))
        goto err;
    if (!BN_copy(point->Y, y))
        goto err;
    if (!BN_one(point->Z))
        goto err;
    point->Z_is_one = 1;

    ret = 1;

 err:
    BN_CTX_end(ctx);
#ifndef FIPS_MODE
    BN_CTX_free(new_ctx);
#endif
    return ret;
}