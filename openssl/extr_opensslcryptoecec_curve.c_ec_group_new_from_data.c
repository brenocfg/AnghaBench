#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  nid; int /*<<< orphan*/  const* (* meth ) () ;TYPE_4__* data; } ;
typedef  TYPE_2__ ec_list_element ;
struct TYPE_20__ {int seed_len; int param_len; scalar_t__ field_type; scalar_t__ cofactor; } ;
struct TYPE_19__ {TYPE_1__* meth; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* group_set_curve ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  const EC_METHOD ;
typedef  TYPE_3__ EC_GROUP ;
typedef  TYPE_4__ EC_CURVE_DATA ;
typedef  int /*<<< orphan*/  BN_ULONG ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/ * BN_bin2bn (unsigned char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_F_EC_GROUP_NEW_FROM_DATA ; 
 int /*<<< orphan*/  EC_GROUP_free (TYPE_3__*) ; 
 TYPE_3__* EC_GROUP_new (int /*<<< orphan*/  const*) ; 
 TYPE_3__* EC_GROUP_new_curve_GF2m (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* EC_GROUP_new_curve_GFp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_set_curve_name (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_GROUP_set_generator (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_set_seed (TYPE_3__*,unsigned char const*,int) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (TYPE_3__*) ; 
 int /*<<< orphan*/  EC_POINT_set_affine_coordinates (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ NID_X9_62_prime_field ; 
 int /*<<< orphan*/  const* stub1 () ; 
 int /*<<< orphan*/  const* stub2 () ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static EC_GROUP *ec_group_new_from_data(const ec_list_element curve)
{
    EC_GROUP *group = NULL;
    EC_POINT *P = NULL;
    BN_CTX *ctx = NULL;
    BIGNUM *p = NULL, *a = NULL, *b = NULL, *x = NULL, *y = NULL, *order =
        NULL;
    int ok = 0;
    int seed_len, param_len;
    const EC_METHOD *meth;
    const EC_CURVE_DATA *data;
    const unsigned char *params;

    /* If no curve data curve method must handle everything */
    if (curve.data == NULL)
        return EC_GROUP_new(curve.meth != NULL ? curve.meth() : NULL);

    if ((ctx = BN_CTX_new()) == NULL) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_DATA, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    data = curve.data;
    seed_len = data->seed_len;
    param_len = data->param_len;
    params = (const unsigned char *)(data + 1); /* skip header */
    params += seed_len;         /* skip seed */

    if ((p = BN_bin2bn(params + 0 * param_len, param_len, NULL)) == NULL
        || (a = BN_bin2bn(params + 1 * param_len, param_len, NULL)) == NULL
        || (b = BN_bin2bn(params + 2 * param_len, param_len, NULL)) == NULL) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_DATA, ERR_R_BN_LIB);
        goto err;
    }

    if (curve.meth != 0) {
        meth = curve.meth();
        if (((group = EC_GROUP_new(meth)) == NULL) ||
            (!(group->meth->group_set_curve(group, p, a, b, ctx)))) {
            ECerr(EC_F_EC_GROUP_NEW_FROM_DATA, ERR_R_EC_LIB);
            goto err;
        }
    } else if (data->field_type == NID_X9_62_prime_field) {
        if ((group = EC_GROUP_new_curve_GFp(p, a, b, ctx)) == NULL) {
            ECerr(EC_F_EC_GROUP_NEW_FROM_DATA, ERR_R_EC_LIB);
            goto err;
        }
    }
#ifndef OPENSSL_NO_EC2M
    else {                      /* field_type ==
                                 * NID_X9_62_characteristic_two_field */

        if ((group = EC_GROUP_new_curve_GF2m(p, a, b, ctx)) == NULL) {
            ECerr(EC_F_EC_GROUP_NEW_FROM_DATA, ERR_R_EC_LIB);
            goto err;
        }
    }
#endif

    EC_GROUP_set_curve_name(group, curve.nid);

    if ((P = EC_POINT_new(group)) == NULL) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_DATA, ERR_R_EC_LIB);
        goto err;
    }

    if ((x = BN_bin2bn(params + 3 * param_len, param_len, NULL)) == NULL
        || (y = BN_bin2bn(params + 4 * param_len, param_len, NULL)) == NULL) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_DATA, ERR_R_BN_LIB);
        goto err;
    }
    if (!EC_POINT_set_affine_coordinates(group, P, x, y, ctx)) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_DATA, ERR_R_EC_LIB);
        goto err;
    }
    if ((order = BN_bin2bn(params + 5 * param_len, param_len, NULL)) == NULL
        || !BN_set_word(x, (BN_ULONG)data->cofactor)) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_DATA, ERR_R_BN_LIB);
        goto err;
    }
    if (!EC_GROUP_set_generator(group, P, order, x)) {
        ECerr(EC_F_EC_GROUP_NEW_FROM_DATA, ERR_R_EC_LIB);
        goto err;
    }
    if (seed_len) {
        if (!EC_GROUP_set_seed(group, params - seed_len, seed_len)) {
            ECerr(EC_F_EC_GROUP_NEW_FROM_DATA, ERR_R_EC_LIB);
            goto err;
        }
    }
    ok = 1;
 err:
    if (!ok) {
        EC_GROUP_free(group);
        group = NULL;
    }
    EC_POINT_free(P);
    BN_CTX_free(ctx);
    BN_free(p);
    BN_free(a);
    BN_free(b);
    BN_free(order);
    BN_free(x);
    BN_free(y);
    return group;
}