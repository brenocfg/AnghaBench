#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/ * r; int /*<<< orphan*/ * s; } ;
struct TYPE_15__ {int /*<<< orphan*/  mont_data; } ;
struct TYPE_14__ {int /*<<< orphan*/  libctx; } ;
typedef  TYPE_1__ EC_KEY ;
typedef  TYPE_2__ EC_GROUP ;
typedef  TYPE_3__ ECDSA_SIG ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new_ex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_bin2bn (unsigned char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_mul_montgomery (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* BN_new () ; 
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_rshift (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ECDSA_SIG_free (TYPE_3__*) ; 
 TYPE_3__* ECDSA_SIG_new () ; 
 int /*<<< orphan*/  EC_F_ECDSA_SIMPLE_SIGN_SIG ; 
 int /*<<< orphan*/ * EC_GROUP_get0_order (TYPE_2__ const*) ; 
 int /*<<< orphan*/  EC_KEY_can_sign (TYPE_1__*) ; 
 TYPE_2__* EC_KEY_get0_group (TYPE_1__*) ; 
 int /*<<< orphan*/ * EC_KEY_get0_private_key (TYPE_1__*) ; 
 int /*<<< orphan*/  EC_R_CURVE_DOES_NOT_SUPPORT_SIGNING ; 
 int /*<<< orphan*/  EC_R_MISSING_PRIVATE_KEY ; 
 int /*<<< orphan*/  EC_R_NEED_NEW_SETUP_VALUES ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  ERR_R_ECDSA_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/  bn_mod_add_fixed_top (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  bn_mul_mont_fixed_top (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bn_to_mont_fixed_top (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecdsa_sign_setup (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,unsigned char const*,int) ; 

ECDSA_SIG *ecdsa_simple_sign_sig(const unsigned char *dgst, int dgst_len,
                                 const BIGNUM *in_kinv, const BIGNUM *in_r,
                                 EC_KEY *eckey)
{
    int ok = 0, i;
    BIGNUM *kinv = NULL, *s, *m = NULL;
    const BIGNUM *order, *ckinv;
    BN_CTX *ctx = NULL;
    const EC_GROUP *group;
    ECDSA_SIG *ret;
    const BIGNUM *priv_key;

    group = EC_KEY_get0_group(eckey);
    priv_key = EC_KEY_get0_private_key(eckey);

    if (group == NULL) {
        ECerr(EC_F_ECDSA_SIMPLE_SIGN_SIG, ERR_R_PASSED_NULL_PARAMETER);
        return NULL;
    }
    if (priv_key == NULL) {
        ECerr(EC_F_ECDSA_SIMPLE_SIGN_SIG, EC_R_MISSING_PRIVATE_KEY);
        return NULL;
    }

    if (!EC_KEY_can_sign(eckey)) {
        ECerr(EC_F_ECDSA_SIMPLE_SIGN_SIG, EC_R_CURVE_DOES_NOT_SUPPORT_SIGNING);
        return NULL;
    }

    ret = ECDSA_SIG_new();
    if (ret == NULL) {
        ECerr(EC_F_ECDSA_SIMPLE_SIGN_SIG, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    ret->r = BN_new();
    ret->s = BN_new();
    if (ret->r == NULL || ret->s == NULL) {
        ECerr(EC_F_ECDSA_SIMPLE_SIGN_SIG, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    s = ret->s;

    if ((ctx = BN_CTX_new_ex(eckey->libctx)) == NULL
        || (m = BN_new()) == NULL) {
        ECerr(EC_F_ECDSA_SIMPLE_SIGN_SIG, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    order = EC_GROUP_get0_order(group);
    i = BN_num_bits(order);
    /*
     * Need to truncate digest if it is too long: first truncate whole bytes.
     */
    if (8 * dgst_len > i)
        dgst_len = (i + 7) / 8;
    if (!BN_bin2bn(dgst, dgst_len, m)) {
        ECerr(EC_F_ECDSA_SIMPLE_SIGN_SIG, ERR_R_BN_LIB);
        goto err;
    }
    /* If still too long, truncate remaining bits with a shift */
    if ((8 * dgst_len > i) && !BN_rshift(m, m, 8 - (i & 0x7))) {
        ECerr(EC_F_ECDSA_SIMPLE_SIGN_SIG, ERR_R_BN_LIB);
        goto err;
    }
    do {
        if (in_kinv == NULL || in_r == NULL) {
            if (!ecdsa_sign_setup(eckey, ctx, &kinv, &ret->r, dgst, dgst_len)) {
                ECerr(EC_F_ECDSA_SIMPLE_SIGN_SIG, ERR_R_ECDSA_LIB);
                goto err;
            }
            ckinv = kinv;
        } else {
            ckinv = in_kinv;
            if (BN_copy(ret->r, in_r) == NULL) {
                ECerr(EC_F_ECDSA_SIMPLE_SIGN_SIG, ERR_R_MALLOC_FAILURE);
                goto err;
            }
        }

        /*
         * With only one multiplicant being in Montgomery domain
         * multiplication yields real result without post-conversion.
         * Also note that all operations but last are performed with
         * zero-padded vectors. Last operation, BN_mod_mul_montgomery
         * below, returns user-visible value with removed zero padding.
         */
        if (!bn_to_mont_fixed_top(s, ret->r, group->mont_data, ctx)
            || !bn_mul_mont_fixed_top(s, s, priv_key, group->mont_data, ctx)) {
            ECerr(EC_F_ECDSA_SIMPLE_SIGN_SIG, ERR_R_BN_LIB);
            goto err;
        }
        if (!bn_mod_add_fixed_top(s, s, m, order)) {
            ECerr(EC_F_ECDSA_SIMPLE_SIGN_SIG, ERR_R_BN_LIB);
            goto err;
        }
        /*
         * |s| can still be larger than modulus, because |m| can be. In
         * such case we count on Montgomery reduction to tie it up.
         */
        if (!bn_to_mont_fixed_top(s, s, group->mont_data, ctx)
            || !BN_mod_mul_montgomery(s, s, ckinv, group->mont_data, ctx)) {
            ECerr(EC_F_ECDSA_SIMPLE_SIGN_SIG, ERR_R_BN_LIB);
            goto err;
        }

        if (BN_is_zero(s)) {
            /*
             * if kinv and r have been supplied by the caller, don't
             * generate new kinv and r values
             */
            if (in_kinv != NULL && in_r != NULL) {
                ECerr(EC_F_ECDSA_SIMPLE_SIGN_SIG, EC_R_NEED_NEW_SETUP_VALUES);
                goto err;
            }
        } else {
            /* s != 0 => we have a valid signature */
            break;
        }
    } while (1);

    ok = 1;
 err:
    if (!ok) {
        ECDSA_SIG_free(ret);
        ret = NULL;
    }
    BN_CTX_free(ctx);
    BN_clear_free(m);
    BN_clear_free(kinv);
    return ret;
}