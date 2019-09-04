#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * Y; int /*<<< orphan*/ * X; scalar_t__ Z_is_one; } ;
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
 scalar_t__ BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_get_affine_coordinates (int /*<<< orphan*/  const*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EC_POINT_is_at_infinity (int /*<<< orphan*/  const*,TYPE_1__ const*) ; 

int ec_GF2m_simple_cmp(const EC_GROUP *group, const EC_POINT *a,
                       const EC_POINT *b, BN_CTX *ctx)
{
    BIGNUM *aX, *aY, *bX, *bY;
    BN_CTX *new_ctx = NULL;
    int ret = -1;

    if (EC_POINT_is_at_infinity(group, a)) {
        return EC_POINT_is_at_infinity(group, b) ? 0 : 1;
    }

    if (EC_POINT_is_at_infinity(group, b))
        return 1;

    if (a->Z_is_one && b->Z_is_one) {
        return ((BN_cmp(a->X, b->X) == 0) && BN_cmp(a->Y, b->Y) == 0) ? 0 : 1;
    }

    if (ctx == NULL) {
        ctx = new_ctx = BN_CTX_new();
        if (ctx == NULL)
            return -1;
    }

    BN_CTX_start(ctx);
    aX = BN_CTX_get(ctx);
    aY = BN_CTX_get(ctx);
    bX = BN_CTX_get(ctx);
    bY = BN_CTX_get(ctx);
    if (bY == NULL)
        goto err;

    if (!EC_POINT_get_affine_coordinates(group, a, aX, aY, ctx))
        goto err;
    if (!EC_POINT_get_affine_coordinates(group, b, bX, bY, ctx))
        goto err;
    ret = ((BN_cmp(aX, bX) == 0) && BN_cmp(aY, bY) == 0) ? 0 : 1;

 err:
    BN_CTX_end(ctx);
    BN_CTX_free(new_ctx);
    return ret;
}