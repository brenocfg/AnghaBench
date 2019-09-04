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
typedef  int /*<<< orphan*/  felem_bytearray ;
struct TYPE_4__ {int /*<<< orphan*/  field_mod_func; } ;
typedef  TYPE_1__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_bin2bn (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_nist_mod_256 ; 
 int /*<<< orphan*/  EC_F_EC_GFP_NISTP256_GROUP_SET_CURVE ; 
 int /*<<< orphan*/  EC_R_WRONG_CURVE_PARAMETERS ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ec_GFp_simple_group_set_curve (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nistp256_curve_params ; 

int ec_GFp_nistp256_group_set_curve(EC_GROUP *group, const BIGNUM *p,
                                    const BIGNUM *a, const BIGNUM *b,
                                    BN_CTX *ctx)
{
    int ret = 0;
    BN_CTX *new_ctx = NULL;
    BIGNUM *curve_p, *curve_a, *curve_b;

    if (ctx == NULL)
        if ((ctx = new_ctx = BN_CTX_new()) == NULL)
            return 0;
    BN_CTX_start(ctx);
    curve_p = BN_CTX_get(ctx);
    curve_a = BN_CTX_get(ctx);
    curve_b = BN_CTX_get(ctx);
    if (curve_b == NULL)
        goto err;
    BN_bin2bn(nistp256_curve_params[0], sizeof(felem_bytearray), curve_p);
    BN_bin2bn(nistp256_curve_params[1], sizeof(felem_bytearray), curve_a);
    BN_bin2bn(nistp256_curve_params[2], sizeof(felem_bytearray), curve_b);
    if ((BN_cmp(curve_p, p)) || (BN_cmp(curve_a, a)) || (BN_cmp(curve_b, b))) {
        ECerr(EC_F_EC_GFP_NISTP256_GROUP_SET_CURVE,
              EC_R_WRONG_CURVE_PARAMETERS);
        goto err;
    }
    group->field_mod_func = BN_nist_mod_256;
    ret = ec_GFp_simple_group_set_curve(group, p, a, b, ctx);
 err:
    BN_CTX_end(ctx);
    BN_CTX_free(new_ctx);
    return ret;
}