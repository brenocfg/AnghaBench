#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * q; int /*<<< orphan*/ * priv_key; int /*<<< orphan*/ * g; int /*<<< orphan*/ * p; } ;
struct TYPE_8__ {int /*<<< orphan*/ * s; int /*<<< orphan*/ * r; } ;
typedef  TYPE_1__ DSA_SIG ;
typedef  TYPE_2__ DSA ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int /*<<< orphan*/  BN_RAND_BOTTOM_ANY ; 
 int /*<<< orphan*/  BN_RAND_TOP_ANY ; 
 int /*<<< orphan*/ * BN_bin2bn (unsigned char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_add_quick (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_mod_inverse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* BN_new () ; 
 scalar_t__ BN_num_bits (int /*<<< orphan*/ *) ; 
 int BN_num_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_priv_rand (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSA_F_DSA_DO_SIGN ; 
 int DSA_R_MISSING_PARAMETERS ; 
 int DSA_R_MISSING_PRIVATE_KEY ; 
 int /*<<< orphan*/  DSA_SIG_free (TYPE_1__*) ; 
 TYPE_1__* DSA_SIG_new () ; 
 int /*<<< orphan*/  DSAerr (int /*<<< orphan*/ ,int) ; 
 int ERR_R_BN_LIB ; 
 int /*<<< orphan*/  dsa_sign_setup (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,unsigned char const*,int) ; 

__attribute__((used)) static DSA_SIG *dsa_do_sign(const unsigned char *dgst, int dlen, DSA *dsa)
{
    BIGNUM *kinv = NULL;
    BIGNUM *m, *blind, *blindm, *tmp;
    BN_CTX *ctx = NULL;
    int reason = ERR_R_BN_LIB;
    DSA_SIG *ret = NULL;
    int rv = 0;

    if (dsa->p == NULL || dsa->q == NULL || dsa->g == NULL) {
        reason = DSA_R_MISSING_PARAMETERS;
        goto err;
    }
    if (dsa->priv_key == NULL) {
        reason = DSA_R_MISSING_PRIVATE_KEY;
        goto err;
    }

    ret = DSA_SIG_new();
    if (ret == NULL)
        goto err;
    ret->r = BN_new();
    ret->s = BN_new();
    if (ret->r == NULL || ret->s == NULL)
        goto err;

    ctx = BN_CTX_new();
    if (ctx == NULL)
        goto err;
    m = BN_CTX_get(ctx);
    blind = BN_CTX_get(ctx);
    blindm = BN_CTX_get(ctx);
    tmp = BN_CTX_get(ctx);
    if (tmp == NULL)
        goto err;

 redo:
    if (!dsa_sign_setup(dsa, ctx, &kinv, &ret->r, dgst, dlen))
        goto err;

    if (dlen > BN_num_bytes(dsa->q))
        /*
         * if the digest length is greater than the size of q use the
         * BN_num_bits(dsa->q) leftmost bits of the digest, see fips 186-3,
         * 4.2
         */
        dlen = BN_num_bytes(dsa->q);
    if (BN_bin2bn(dgst, dlen, m) == NULL)
        goto err;

    /*
     * The normal signature calculation is:
     *
     *   s := k^-1 * (m + r * priv_key) mod q
     *
     * We will blind this to protect against side channel attacks
     *
     *   s := blind^-1 * k^-1 * (blind * m + blind * r * priv_key) mod q
     */

    /* Generate a blinding value */
    do {
        if (!BN_priv_rand(blind, BN_num_bits(dsa->q) - 1,
                          BN_RAND_TOP_ANY, BN_RAND_BOTTOM_ANY))
            goto err;
    } while (BN_is_zero(blind));
    BN_set_flags(blind, BN_FLG_CONSTTIME);
    BN_set_flags(blindm, BN_FLG_CONSTTIME);
    BN_set_flags(tmp, BN_FLG_CONSTTIME);

    /* tmp := blind * priv_key * r mod q */
    if (!BN_mod_mul(tmp, blind, dsa->priv_key, dsa->q, ctx))
        goto err;
    if (!BN_mod_mul(tmp, tmp, ret->r, dsa->q, ctx))
        goto err;

    /* blindm := blind * m mod q */
    if (!BN_mod_mul(blindm, blind, m, dsa->q, ctx))
        goto err;

    /* s : = (blind * priv_key * r) + (blind * m) mod q */
    if (!BN_mod_add_quick(ret->s, tmp, blindm, dsa->q))
        goto err;

    /* s := s * k^-1 mod q */
    if (!BN_mod_mul(ret->s, ret->s, kinv, dsa->q, ctx))
        goto err;

    /* s:= s * blind^-1 mod q */
    if (BN_mod_inverse(blind, blind, dsa->q, ctx) == NULL)
        goto err;
    if (!BN_mod_mul(ret->s, ret->s, blind, dsa->q, ctx))
        goto err;

    /*
     * Redo if r or s is zero as required by FIPS 186-3: this is very
     * unlikely.
     */
    if (BN_is_zero(ret->r) || BN_is_zero(ret->s))
        goto redo;

    rv = 1;

 err:
    if (rv == 0) {
        DSAerr(DSA_F_DSA_DO_SIGN, reason);
        DSA_SIG_free(ret);
        ret = NULL;
    }
    BN_CTX_free(ctx);
    BN_clear_free(kinv);
    return ret;
}