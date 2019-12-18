#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; int /*<<< orphan*/ * q; int /*<<< orphan*/  method_mont_p; int /*<<< orphan*/ * p; int /*<<< orphan*/ * g; TYPE_1__* meth; int /*<<< orphan*/  lock; int /*<<< orphan*/ * priv_key; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* bn_mod_exp ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ DSA ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int /*<<< orphan*/  BN_MONT_CTX_set_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_consttime_swap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_generate_dsa_nonce (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_is_bit_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_mont (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_priv_rand_range (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int DSA_FLAG_CACHE_MONT_P ; 
 int /*<<< orphan*/  DSA_F_DSA_SIGN_SETUP ; 
 int /*<<< orphan*/  DSA_R_INVALID_PARAMETERS ; 
 int /*<<< orphan*/  DSA_R_MISSING_PARAMETERS ; 
 int /*<<< orphan*/  DSA_R_MISSING_PRIVATE_KEY ; 
 int /*<<< orphan*/  DSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int bn_get_top (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bn_wexpand (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * dsa_mod_inverse_fermat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_sign_setup(DSA *dsa, BN_CTX *ctx_in,
                          BIGNUM **kinvp, BIGNUM **rp,
                          const unsigned char *dgst, int dlen)
{
    BN_CTX *ctx = NULL;
    BIGNUM *k, *kinv = NULL, *r = *rp;
    BIGNUM *l;
    int ret = 0;
    int q_bits, q_words;

    if (!dsa->p || !dsa->q || !dsa->g) {
        DSAerr(DSA_F_DSA_SIGN_SETUP, DSA_R_MISSING_PARAMETERS);
        return 0;
    }

    /* Reject obviously invalid parameters */
    if (BN_is_zero(dsa->p) || BN_is_zero(dsa->q) || BN_is_zero(dsa->g)) {
        DSAerr(DSA_F_DSA_SIGN_SETUP, DSA_R_INVALID_PARAMETERS);
        return 0;
    }
    if (dsa->priv_key == NULL) {
        DSAerr(DSA_F_DSA_SIGN_SETUP, DSA_R_MISSING_PRIVATE_KEY);
        return 0;
    }

    k = BN_new();
    l = BN_new();
    if (k == NULL || l == NULL)
        goto err;

    if (ctx_in == NULL) {
        if ((ctx = BN_CTX_new()) == NULL)
            goto err;
    } else
        ctx = ctx_in;

    /* Preallocate space */
    q_bits = BN_num_bits(dsa->q);
    q_words = bn_get_top(dsa->q);
    if (!bn_wexpand(k, q_words + 2)
        || !bn_wexpand(l, q_words + 2))
        goto err;

    /* Get random k */
    do {
        if (dgst != NULL) {
            /*
             * We calculate k from SHA512(private_key + H(message) + random).
             * This protects the private key from a weak PRNG.
             */
            if (!BN_generate_dsa_nonce(k, dsa->q, dsa->priv_key, dgst,
                                       dlen, ctx))
                goto err;
        } else if (!BN_priv_rand_range(k, dsa->q))
            goto err;
    } while (BN_is_zero(k));

    BN_set_flags(k, BN_FLG_CONSTTIME);
    BN_set_flags(l, BN_FLG_CONSTTIME);

    if (dsa->flags & DSA_FLAG_CACHE_MONT_P) {
        if (!BN_MONT_CTX_set_locked(&dsa->method_mont_p,
                                    dsa->lock, dsa->p, ctx))
            goto err;
    }

    /* Compute r = (g^k mod p) mod q */

    /*
     * We do not want timing information to leak the length of k, so we
     * compute G^k using an equivalent scalar of fixed bit-length.
     *
     * We unconditionally perform both of these additions to prevent a
     * small timing information leakage.  We then choose the sum that is
     * one bit longer than the modulus.
     *
     * There are some concerns about the efficacy of doing this.  More
     * specifically refer to the discussion starting with:
     *     https://github.com/openssl/openssl/pull/7486#discussion_r228323705
     * The fix is to rework BN so these gymnastics aren't required.
     */
    if (!BN_add(l, k, dsa->q)
        || !BN_add(k, l, dsa->q))
        goto err;

    BN_consttime_swap(BN_is_bit_set(l, q_bits), k, l, q_words + 2);

    if ((dsa)->meth->bn_mod_exp != NULL) {
            if (!dsa->meth->bn_mod_exp(dsa, r, dsa->g, k, dsa->p, ctx,
                                       dsa->method_mont_p))
                goto err;
    } else {
            if (!BN_mod_exp_mont(r, dsa->g, k, dsa->p, ctx, dsa->method_mont_p))
                goto err;
    }

    if (!BN_mod(r, r, dsa->q, ctx))
        goto err;

    /* Compute part of 's = inv(k) (m + xr) mod q' */
    if ((kinv = dsa_mod_inverse_fermat(k, dsa->q, ctx)) == NULL)
        goto err;

    BN_clear_free(*kinvp);
    *kinvp = kinv;
    kinv = NULL;
    ret = 1;
 err:
    if (!ret)
        DSAerr(DSA_F_DSA_SIGN_SETUP, ERR_R_BN_LIB);
    if (ctx != ctx_in)
        BN_CTX_free(ctx);
    BN_clear_free(k);
    BN_clear_free(l);
    return ret;
}