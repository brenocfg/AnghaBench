#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* meth; int /*<<< orphan*/  field; } ;
struct TYPE_13__ {scalar_t__ Z_is_one; int /*<<< orphan*/ * Y; int /*<<< orphan*/ * X; int /*<<< orphan*/ * Z; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* field_mul ) (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* field_sqr ) (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* field_encode ) (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ EC_POINT ;
typedef  TYPE_3__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_priv_rand_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_F_EC_GFP_SIMPLE_BLIND_COORDINATES ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  stub1 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ec_GFp_simple_blind_coordinates(const EC_GROUP *group, EC_POINT *p,
                                    BN_CTX *ctx)
{
    int ret = 0;
    BIGNUM *lambda = NULL;
    BIGNUM *temp = NULL;

    BN_CTX_start(ctx);
    lambda = BN_CTX_get(ctx);
    temp = BN_CTX_get(ctx);
    if (temp == NULL) {
        ECerr(EC_F_EC_GFP_SIMPLE_BLIND_COORDINATES, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    /* make sure lambda is not zero */
    do {
        if (!BN_priv_rand_range(lambda, group->field)) {
            ECerr(EC_F_EC_GFP_SIMPLE_BLIND_COORDINATES, ERR_R_BN_LIB);
            goto err;
        }
    } while (BN_is_zero(lambda));

    /* if field_encode defined convert between representations */
    if (group->meth->field_encode != NULL
        && !group->meth->field_encode(group, lambda, lambda, ctx))
        goto err;
    if (!group->meth->field_mul(group, p->Z, p->Z, lambda, ctx))
        goto err;
    if (!group->meth->field_sqr(group, temp, lambda, ctx))
        goto err;
    if (!group->meth->field_mul(group, p->X, p->X, temp, ctx))
        goto err;
    if (!group->meth->field_mul(group, temp, temp, lambda, ctx))
        goto err;
    if (!group->meth->field_mul(group, p->Y, p->Y, temp, ctx))
        goto err;
    p->Z_is_one = 0;

    ret = 1;

 err:
    BN_CTX_end(ctx);
    return ret;
}