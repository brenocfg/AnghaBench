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
struct TYPE_5__ {int /*<<< orphan*/ * group; int /*<<< orphan*/  libctx; } ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  TYPE_1__ EC_KEY ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new_ex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_F_EC_KEY_SET_PUBLIC_KEY_AFFINE_COORDINATES ; 
 scalar_t__ EC_KEY_check_key (TYPE_1__*) ; 
 int /*<<< orphan*/  EC_KEY_set_public_key (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_get_affine_coordinates (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_set_affine_coordinates (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_R_COORDINATES_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 

int EC_KEY_set_public_key_affine_coordinates(EC_KEY *key, BIGNUM *x,
                                             BIGNUM *y)
{
    BN_CTX *ctx = NULL;
    BIGNUM *tx, *ty;
    EC_POINT *point = NULL;
    int ok = 0;

    if (key == NULL || key->group == NULL || x == NULL || y == NULL) {
        ECerr(EC_F_EC_KEY_SET_PUBLIC_KEY_AFFINE_COORDINATES,
              ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }
    ctx = BN_CTX_new_ex(key->libctx);
    if (ctx == NULL)
        return 0;

    BN_CTX_start(ctx);
    point = EC_POINT_new(key->group);

    if (point == NULL)
        goto err;

    tx = BN_CTX_get(ctx);
    ty = BN_CTX_get(ctx);
    if (ty == NULL)
        goto err;

    if (!EC_POINT_set_affine_coordinates(key->group, point, x, y, ctx))
        goto err;
    if (!EC_POINT_get_affine_coordinates(key->group, point, tx, ty, ctx))
        goto err;

    /*
     * Check if retrieved coordinates match originals. The range check is done
     * inside EC_KEY_check_key().
     */
    if (BN_cmp(x, tx) || BN_cmp(y, ty)) {
        ECerr(EC_F_EC_KEY_SET_PUBLIC_KEY_AFFINE_COORDINATES,
              EC_R_COORDINATES_OUT_OF_RANGE);
        goto err;
    }

    if (!EC_KEY_set_public_key(key, point))
        goto err;

    if (EC_KEY_check_key(key) == 0)
        goto err;

    ok = 1;

 err:
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    EC_POINT_free(point);
    return ok;

}