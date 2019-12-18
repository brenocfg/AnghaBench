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
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_GENCB_call (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_check_prime (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * BN_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_gcd (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_is_one (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_lshift (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ BN_lshift1 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_mod_inverse (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_sub (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_priv_rand_range_ex (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_sub (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_sub_word (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  const* BN_value_one () ; 
 int /*<<< orphan*/  const bn_inv_sqrt_2 ; 

int bn_rsa_fips186_4_derive_prime(BIGNUM *Y, BIGNUM *X, const BIGNUM *Xin,
                                  const BIGNUM *r1, const BIGNUM *r2, int nlen,
                                  const BIGNUM *e, BN_CTX *ctx, BN_GENCB *cb)
{
    int ret = 0;
    int i, imax;
    int bits = nlen >> 1;
    BIGNUM *tmp, *R, *r1r2x2, *y1, *r1x2;
    BIGNUM *base, *range;

    BN_CTX_start(ctx);

    base = BN_CTX_get(ctx);
    range = BN_CTX_get(ctx);
    R = BN_CTX_get(ctx);
    tmp = BN_CTX_get(ctx);
    r1r2x2 = BN_CTX_get(ctx);
    y1 = BN_CTX_get(ctx);
    r1x2 = BN_CTX_get(ctx);
    if (r1x2 == NULL)
        goto err;

    if (Xin != NULL && BN_copy(X, Xin) == NULL)
        goto err;

    /*
     * We need to generate a random number X in the range
     * 1/sqrt(2) * 2^(nlen/2) <= X < 2^(nlen/2).
     * We can rewrite that as:
     * base = 1/sqrt(2) * 2^(nlen/2)
     * range = ((2^(nlen/2))) - (1/sqrt(2) * 2^(nlen/2))
     * X = base + random(range)
     * We only have the first 256 bit of 1/sqrt(2)
     */
    if (Xin == NULL) {
        if (bits < BN_num_bits(&bn_inv_sqrt_2))
            goto err;
        if (!BN_lshift(base, &bn_inv_sqrt_2, bits - BN_num_bits(&bn_inv_sqrt_2))
            || !BN_lshift(range, BN_value_one(), bits)
            || !BN_sub(range, range, base))
            goto err;
    }

    if (!(BN_lshift1(r1x2, r1)
            /* (Step 1) GCD(2r1, r2) = 1 */
            && BN_gcd(tmp, r1x2, r2, ctx)
            && BN_is_one(tmp)
            /* (Step 2) R = ((r2^-1 mod 2r1) * r2) - ((2r1^-1 mod r2)*2r1) */
            && BN_mod_inverse(R, r2, r1x2, ctx)
            && BN_mul(R, R, r2, ctx) /* R = (r2^-1 mod 2r1) * r2 */
            && BN_mod_inverse(tmp, r1x2, r2, ctx)
            && BN_mul(tmp, tmp, r1x2, ctx) /* tmp = (2r1^-1 mod r2)*2r1 */
            && BN_sub(R, R, tmp)
            /* Calculate 2r1r2 */
            && BN_mul(r1r2x2, r1x2, r2, ctx)))
        goto err;
    /* Make positive by adding the modulus */
    if (BN_is_negative(R) && !BN_add(R, R, r1r2x2))
        goto err;

    imax = 5 * bits; /* max = 5/2 * nbits */
    for (;;) {
        if (Xin == NULL) {
            /*
             * (Step 3) Choose Random X such that
             *    sqrt(2) * 2^(nlen/2-1) <= Random X <= (2^(nlen/2)) - 1.
             */
            if (!BN_priv_rand_range_ex(X, range, ctx) || !BN_add(X, X, base))
                goto end;
        }
        /* (Step 4) Y = X + ((R - X) mod 2r1r2) */
        if (!BN_mod_sub(Y, R, X, r1r2x2, ctx) || !BN_add(Y, Y, X))
            goto err;
        /* (Step 5) */
        i = 0;
        for (;;) {
            /* (Step 6) */
            if (BN_num_bits(Y) > bits) {
                if (Xin == NULL)
                    break; /* Randomly Generated X so Go back to Step 3 */
                else
                    goto err; /* X is not random so it will always fail */
            }
            BN_GENCB_call(cb, 0, 2);

            /* (Step 7) If GCD(Y-1) == 1 & Y is probably prime then return Y */
            if (BN_copy(y1, Y) == NULL
                    || !BN_sub_word(y1, 1)
                    || !BN_gcd(tmp, y1, e, ctx))
                goto err;
            if (BN_is_one(tmp) && BN_check_prime(Y, ctx, cb))
                goto end;
            /* (Step 8-10) */
            if (++i >= imax || !BN_add(Y, Y, r1r2x2))
                goto err;
        }
    }
end:
    ret = 1;
    BN_GENCB_call(cb, 3, 0);
err:
    BN_clear(y1);
    BN_CTX_end(ctx);
    return ret;
}