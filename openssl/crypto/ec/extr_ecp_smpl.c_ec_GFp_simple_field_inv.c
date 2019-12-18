#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* meth; int /*<<< orphan*/  field; int /*<<< orphan*/  libctx; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* field_mul ) (TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_secure_new_ex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_mod_inverse (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_priv_rand_range_ex (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_F_EC_GFP_SIMPLE_FIELD_INV ; 
 int /*<<< orphan*/  EC_R_CANNOT_INVERT ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int ec_GFp_simple_field_inv(const EC_GROUP *group, BIGNUM *r, const BIGNUM *a,
                            BN_CTX *ctx)
{
    BIGNUM *e = NULL;
    BN_CTX *new_ctx = NULL;
    int ret = 0;

    if (ctx == NULL
            && (ctx = new_ctx = BN_CTX_secure_new_ex(group->libctx)) == NULL)
        return 0;

    BN_CTX_start(ctx);
    if ((e = BN_CTX_get(ctx)) == NULL)
        goto err;

    do {
        if (!BN_priv_rand_range_ex(e, group->field, ctx))
        goto err;
    } while (BN_is_zero(e));

    /* r := a * e */
    if (!group->meth->field_mul(group, r, a, e, ctx))
        goto err;
    /* r := 1/(a * e) */
    if (!BN_mod_inverse(r, r, group->field, ctx)) {
        ECerr(EC_F_EC_GFP_SIMPLE_FIELD_INV, EC_R_CANNOT_INVERT);
        goto err;
    }
    /* r := e/(a * e) = 1/a */
    if (!group->meth->field_mul(group, r, r, e, ctx))
        goto err;

    ret = 1;

 err:
    BN_CTX_end(ctx);
    BN_CTX_free(new_ctx);
    return ret;
}