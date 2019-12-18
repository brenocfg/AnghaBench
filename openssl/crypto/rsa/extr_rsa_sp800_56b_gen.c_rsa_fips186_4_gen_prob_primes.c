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
struct TYPE_3__ {int /*<<< orphan*/  dirty_cnt; int /*<<< orphan*/ * q; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ RSA ;
typedef  int /*<<< orphan*/  BN_GENCB ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear (int /*<<< orphan*/ *) ; 
 void* BN_secure_new () ; 
 int RSA_FIPS1864_MIN_KEYGEN_KEYSIZE ; 
 int /*<<< orphan*/  RSA_F_RSA_FIPS186_4_GEN_PROB_PRIMES ; 
 int /*<<< orphan*/  RSA_R_INVALID_KEY_LENGTH ; 
 int /*<<< orphan*/  RSA_R_PUB_EXPONENT_OUT_OF_RANGE ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_rsa_fips186_4_gen_prob_primes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rsa_check_pminusq_diff (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rsa_check_public_exponent (int /*<<< orphan*/  const*) ; 

int rsa_fips186_4_gen_prob_primes(RSA *rsa, BIGNUM *p1, BIGNUM *p2,
                                  BIGNUM *Xpout, const BIGNUM *Xp,
                                  const BIGNUM *Xp1, const BIGNUM *Xp2,
                                  BIGNUM *q1, BIGNUM *q2, BIGNUM *Xqout,
                                  const BIGNUM *Xq, const BIGNUM *Xq1,
                                  const BIGNUM *Xq2, int nbits,
                                  const BIGNUM *e, BN_CTX *ctx, BN_GENCB *cb)
{
    int ret = 0, ok;
    BIGNUM *Xpo = NULL, *Xqo = NULL, *tmp = NULL;

    /* (Step 1) Check key length
     * NOTE: SP800-131A Rev1 Disallows key lengths of < 2048 bits for RSA
     * Signature Generation and Key Agree/Transport.
     */
    if (nbits < RSA_FIPS1864_MIN_KEYGEN_KEYSIZE) {
        RSAerr(RSA_F_RSA_FIPS186_4_GEN_PROB_PRIMES, RSA_R_INVALID_KEY_LENGTH);
        return 0;
    }

    if (!rsa_check_public_exponent(e)) {
        RSAerr(RSA_F_RSA_FIPS186_4_GEN_PROB_PRIMES,
               RSA_R_PUB_EXPONENT_OUT_OF_RANGE);
        return 0;
    }

    /* (Step 3) Determine strength and check rand generator strength is ok -
     * this step is redundant because the generator always returns a higher
     * strength than is required.
     */

    BN_CTX_start(ctx);
    tmp = BN_CTX_get(ctx);
    Xpo = (Xpout != NULL) ? Xpout : BN_CTX_get(ctx);
    Xqo = (Xqout != NULL) ? Xqout : BN_CTX_get(ctx);
    if (tmp == NULL || Xpo == NULL || Xqo == NULL)
        goto err;

    if (rsa->p == NULL)
        rsa->p = BN_secure_new();
    if (rsa->q == NULL)
        rsa->q = BN_secure_new();
    if (rsa->p == NULL || rsa->q == NULL)
        goto err;

    /* (Step 4) Generate p, Xp */
    if (!bn_rsa_fips186_4_gen_prob_primes(rsa->p, Xpo, p1, p2, Xp, Xp1, Xp2,
                                          nbits, e, ctx, cb))
        goto err;
    for(;;) {
        /* (Step 5) Generate q, Xq*/
        if (!bn_rsa_fips186_4_gen_prob_primes(rsa->q, Xqo, q1, q2, Xq, Xq1,
                                              Xq2, nbits, e, ctx, cb))
            goto err;

        /* (Step 6) |Xp - Xq| > 2^(nbitlen/2 - 100) */
        ok = rsa_check_pminusq_diff(tmp, Xpo, Xqo, nbits);
        if (ok < 0)
            goto err;
        if (ok == 0)
            continue;

        /* (Step 6) |p - q| > 2^(nbitlen/2 - 100) */
        ok = rsa_check_pminusq_diff(tmp, rsa->p, rsa->q, nbits);
        if (ok < 0)
            goto err;
        if (ok == 0)
            continue;
        break; /* successfully finished */
    }
    rsa->dirty_cnt++;
    ret = 1;
err:
    /* Zeroize any internally generated values that are not returned */
    if (Xpo != Xpout)
        BN_clear(Xpo);
    if (Xqo != Xqout)
        BN_clear(Xqo);
    BN_clear(tmp);

    BN_CTX_end(ctx);
    return ret;
}