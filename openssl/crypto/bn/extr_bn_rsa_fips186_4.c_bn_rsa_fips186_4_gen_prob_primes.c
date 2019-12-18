#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  BN_GENCB ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_RAND_BOTTOM_ODD ; 
 int /*<<< orphan*/  BN_RAND_TOP_ONE ; 
 int /*<<< orphan*/  BN_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_priv_rand_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bn_rsa_fips186_4_aux_prime_max_sum_size_for_prob_primes (int) ; 
 int bn_rsa_fips186_4_aux_prime_min_size (int) ; 
 int /*<<< orphan*/  bn_rsa_fips186_4_derive_prime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bn_rsa_fips186_4_find_aux_prob_prime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int bn_rsa_fips186_4_gen_prob_primes(BIGNUM *p, BIGNUM *Xpout,
                                     BIGNUM *p1, BIGNUM *p2,
                                     const BIGNUM *Xp, const BIGNUM *Xp1,
                                     const BIGNUM *Xp2, int nlen,
                                     const BIGNUM *e, BN_CTX *ctx, BN_GENCB *cb)
{
    int ret = 0;
    BIGNUM *p1i = NULL, *p2i = NULL, *Xp1i = NULL, *Xp2i = NULL;
    int bitlen;

    if (p == NULL || Xpout == NULL)
        return 0;

    BN_CTX_start(ctx);

    p1i = (p1 != NULL) ? p1 : BN_CTX_get(ctx);
    p2i = (p2 != NULL) ? p2 : BN_CTX_get(ctx);
    Xp1i = (Xp1 != NULL) ? (BIGNUM *)Xp1 : BN_CTX_get(ctx);
    Xp2i = (Xp2 != NULL) ? (BIGNUM *)Xp2 : BN_CTX_get(ctx);
    if (p1i == NULL || p2i == NULL || Xp1i == NULL || Xp2i == NULL)
        goto err;

    bitlen = bn_rsa_fips186_4_aux_prime_min_size(nlen);
    if (bitlen == 0)
        goto err;

    /* (Steps 4.1/5.1): Randomly generate Xp1 if it is not passed in */
    if (Xp1 == NULL) {
        /* Set the top and bottom bits to make it odd and the correct size */
        if (!BN_priv_rand_ex(Xp1i, bitlen, BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ODD,
                             ctx))
            goto err;
    }
    /* (Steps 4.1/5.1): Randomly generate Xp2 if it is not passed in */
    if (Xp2 == NULL) {
        /* Set the top and bottom bits to make it odd and the correct size */
        if (!BN_priv_rand_ex(Xp2i, bitlen, BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ODD,
                             ctx))
            goto err;
    }

    /* (Steps 4.2/5.2) - find first auxiliary probable primes */
    if (!bn_rsa_fips186_4_find_aux_prob_prime(Xp1i, p1i, ctx, cb)
            || !bn_rsa_fips186_4_find_aux_prob_prime(Xp2i, p2i, ctx, cb))
        goto err;
    /* (Table B.1) auxiliary prime Max length check */
    if ((BN_num_bits(p1i) + BN_num_bits(p2i)) >=
            bn_rsa_fips186_4_aux_prime_max_sum_size_for_prob_primes(nlen))
        goto err;
    /* (Steps 4.3/5.3) - generate prime */
    if (!bn_rsa_fips186_4_derive_prime(p, Xpout, Xp, p1i, p2i, nlen, e, ctx, cb))
        goto err;
    ret = 1;
err:
    /* Zeroize any internally generated values that are not returned */
    if (p1 == NULL)
        BN_clear(p1i);
    if (p2 == NULL)
        BN_clear(p2i);
    if (Xp1 == NULL)
        BN_clear(Xp1i);
    if (Xp2 == NULL)
        BN_clear(Xp2i);
    BN_CTX_end(ctx);
    return ret;
}