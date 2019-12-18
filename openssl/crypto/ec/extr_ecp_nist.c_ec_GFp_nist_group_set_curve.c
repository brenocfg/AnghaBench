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
struct TYPE_4__ {int /*<<< orphan*/  field_mod_func; int /*<<< orphan*/  libctx; } ;
typedef  TYPE_1__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new_ex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_get0_nist_prime_192 () ; 
 int /*<<< orphan*/  BN_get0_nist_prime_224 () ; 
 int /*<<< orphan*/  BN_get0_nist_prime_256 () ; 
 int /*<<< orphan*/  BN_get0_nist_prime_384 () ; 
 int /*<<< orphan*/  BN_get0_nist_prime_521 () ; 
 int /*<<< orphan*/  BN_nist_mod_192 ; 
 int /*<<< orphan*/  BN_nist_mod_224 ; 
 int /*<<< orphan*/  BN_nist_mod_256 ; 
 int /*<<< orphan*/  BN_nist_mod_384 ; 
 int /*<<< orphan*/  BN_nist_mod_521 ; 
 scalar_t__ BN_ucmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_F_EC_GFP_NIST_GROUP_SET_CURVE ; 
 int /*<<< orphan*/  EC_R_NOT_A_NIST_PRIME ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ec_GFp_simple_group_set_curve (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int ec_GFp_nist_group_set_curve(EC_GROUP *group, const BIGNUM *p,
                                const BIGNUM *a, const BIGNUM *b, BN_CTX *ctx)
{
    int ret = 0;
    BN_CTX *new_ctx = NULL;

    if (ctx == NULL)
        if ((ctx = new_ctx = BN_CTX_new_ex(group->libctx)) == NULL)
            return 0;

    BN_CTX_start(ctx);

    if (BN_ucmp(BN_get0_nist_prime_192(), p) == 0)
        group->field_mod_func = BN_nist_mod_192;
    else if (BN_ucmp(BN_get0_nist_prime_224(), p) == 0)
        group->field_mod_func = BN_nist_mod_224;
    else if (BN_ucmp(BN_get0_nist_prime_256(), p) == 0)
        group->field_mod_func = BN_nist_mod_256;
    else if (BN_ucmp(BN_get0_nist_prime_384(), p) == 0)
        group->field_mod_func = BN_nist_mod_384;
    else if (BN_ucmp(BN_get0_nist_prime_521(), p) == 0)
        group->field_mod_func = BN_nist_mod_521;
    else {
        ECerr(EC_F_EC_GFP_NIST_GROUP_SET_CURVE, EC_R_NOT_A_NIST_PRIME);
        goto err;
    }

    ret = ec_GFp_simple_group_set_curve(group, p, a, b, ctx);

 err:
    BN_CTX_end(ctx);
    BN_CTX_free(new_ctx);
    return ret;
}