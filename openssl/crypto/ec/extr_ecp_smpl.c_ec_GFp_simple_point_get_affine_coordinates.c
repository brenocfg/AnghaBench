#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_1__* meth; int /*<<< orphan*/  field; int /*<<< orphan*/  libctx; } ;
struct TYPE_17__ {int /*<<< orphan*/ * Y; int /*<<< orphan*/ * X; int /*<<< orphan*/ * Z; } ;
struct TYPE_16__ {scalar_t__ field_encode; int /*<<< orphan*/  (* field_mul ) (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* field_sqr ) (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* field_inv ) (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* field_decode ) (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ EC_POINT ;
typedef  TYPE_3__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new_ex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_one (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_mod_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_sqr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_F_EC_GFP_SIMPLE_POINT_GET_AFFINE_COORDINATES ; 
 scalar_t__ EC_POINT_is_at_infinity (TYPE_3__ const*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  EC_R_POINT_AT_INFINITY ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  stub1 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub8 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ec_GFp_simple_point_get_affine_coordinates(const EC_GROUP *group,
                                               const EC_POINT *point,
                                               BIGNUM *x, BIGNUM *y,
                                               BN_CTX *ctx)
{
    BN_CTX *new_ctx = NULL;
    BIGNUM *Z, *Z_1, *Z_2, *Z_3;
    const BIGNUM *Z_;
    int ret = 0;

    if (EC_POINT_is_at_infinity(group, point)) {
        ECerr(EC_F_EC_GFP_SIMPLE_POINT_GET_AFFINE_COORDINATES,
              EC_R_POINT_AT_INFINITY);
        return 0;
    }

    if (ctx == NULL) {
        ctx = new_ctx = BN_CTX_new_ex(group->libctx);
        if (ctx == NULL)
            return 0;
    }

    BN_CTX_start(ctx);
    Z = BN_CTX_get(ctx);
    Z_1 = BN_CTX_get(ctx);
    Z_2 = BN_CTX_get(ctx);
    Z_3 = BN_CTX_get(ctx);
    if (Z_3 == NULL)
        goto err;

    /* transform  (X, Y, Z)  into  (x, y) := (X/Z^2, Y/Z^3) */

    if (group->meth->field_decode) {
        if (!group->meth->field_decode(group, Z, point->Z, ctx))
            goto err;
        Z_ = Z;
    } else {
        Z_ = point->Z;
    }

    if (BN_is_one(Z_)) {
        if (group->meth->field_decode) {
            if (x != NULL) {
                if (!group->meth->field_decode(group, x, point->X, ctx))
                    goto err;
            }
            if (y != NULL) {
                if (!group->meth->field_decode(group, y, point->Y, ctx))
                    goto err;
            }
        } else {
            if (x != NULL) {
                if (!BN_copy(x, point->X))
                    goto err;
            }
            if (y != NULL) {
                if (!BN_copy(y, point->Y))
                    goto err;
            }
        }
    } else {
        if (!group->meth->field_inv(group, Z_1, Z_, ctx)) {
            ECerr(EC_F_EC_GFP_SIMPLE_POINT_GET_AFFINE_COORDINATES,
                  ERR_R_BN_LIB);
            goto err;
        }

        if (group->meth->field_encode == 0) {
            /* field_sqr works on standard representation */
            if (!group->meth->field_sqr(group, Z_2, Z_1, ctx))
                goto err;
        } else {
            if (!BN_mod_sqr(Z_2, Z_1, group->field, ctx))
                goto err;
        }

        if (x != NULL) {
            /*
             * in the Montgomery case, field_mul will cancel out Montgomery
             * factor in X:
             */
            if (!group->meth->field_mul(group, x, point->X, Z_2, ctx))
                goto err;
        }

        if (y != NULL) {
            if (group->meth->field_encode == 0) {
                /*
                 * field_mul works on standard representation
                 */
                if (!group->meth->field_mul(group, Z_3, Z_2, Z_1, ctx))
                    goto err;
            } else {
                if (!BN_mod_mul(Z_3, Z_2, Z_1, group->field, ctx))
                    goto err;
            }

            /*
             * in the Montgomery case, field_mul will cancel out Montgomery
             * factor in Y:
             */
            if (!group->meth->field_mul(group, y, point->Y, Z_3, ctx))
                goto err;
        }
    }

    ret = 1;

 err:
    BN_CTX_end(ctx);
    BN_CTX_free(new_ctx);
    return ret;
}