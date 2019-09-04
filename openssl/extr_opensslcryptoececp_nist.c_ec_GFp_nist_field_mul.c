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
struct TYPE_3__ {int /*<<< orphan*/  field; int /*<<< orphan*/  (* field_mod_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_F_EC_GFP_NIST_FIELD_MUL ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ec_GFp_nist_field_mul(const EC_GROUP *group, BIGNUM *r, const BIGNUM *a,
                          const BIGNUM *b, BN_CTX *ctx)
{
    int ret = 0;
    BN_CTX *ctx_new = NULL;

    if (!group || !r || !a || !b) {
        ECerr(EC_F_EC_GFP_NIST_FIELD_MUL, ERR_R_PASSED_NULL_PARAMETER);
        goto err;
    }
    if (!ctx)
        if ((ctx_new = ctx = BN_CTX_new()) == NULL)
            goto err;

    if (!BN_mul(r, a, b, ctx))
        goto err;
    if (!group->field_mod_func(r, r, group->field, ctx))
        goto err;

    ret = 1;
 err:
    BN_CTX_free(ctx_new);
    return ret;
}