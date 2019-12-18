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
typedef  int /*<<< orphan*/  BN_MONT_CTX ;
typedef  int /*<<< orphan*/  BN_GENCB ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_GENCB_call (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  BN_MONT_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_MONT_CTX_new () ; 
 int /*<<< orphan*/  BN_MONT_CTX_set (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int BN_PRIMETEST_COMPOSITE ; 
 int BN_PRIMETEST_COMPOSITE_NOT_POWER_OF_PRIME ; 
 int BN_PRIMETEST_COMPOSITE_WITH_FACTOR ; 
 int BN_PRIMETEST_PROBABLY_PRIME ; 
 int /*<<< orphan*/  BN_add_word (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  BN_clear (int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_gcd (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_is_bit_set (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_is_odd (int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_is_one (int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_mod_exp_mont (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_priv_rand_range_ex (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_rshift (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ BN_sub_word (int /*<<< orphan*/  const*,int) ; 
 int bn_mr_min_checks (int /*<<< orphan*/ ) ; 

int bn_miller_rabin_is_prime(const BIGNUM *w, int iterations, BN_CTX *ctx,
                             BN_GENCB *cb, int enhanced, int *status)
{
    int i, j, a, ret = 0;
    BIGNUM *g, *w1, *w3, *x, *m, *z, *b;
    BN_MONT_CTX *mont = NULL;

    /* w must be odd */
    if (!BN_is_odd(w))
        return 0;

    BN_CTX_start(ctx);
    g = BN_CTX_get(ctx);
    w1 = BN_CTX_get(ctx);
    w3 = BN_CTX_get(ctx);
    x = BN_CTX_get(ctx);
    m = BN_CTX_get(ctx);
    z = BN_CTX_get(ctx);
    b = BN_CTX_get(ctx);

    if (!(b != NULL
            /* w1 := w - 1 */
            && BN_copy(w1, w)
            && BN_sub_word(w1, 1)
            /* w3 := w - 3 */
            && BN_copy(w3, w)
            && BN_sub_word(w3, 3)))
        goto err;

    /* check w is larger than 3, otherwise the random b will be too small */
    if (BN_is_zero(w3) || BN_is_negative(w3))
        goto err;

    /* (Step 1) Calculate largest integer 'a' such that 2^a divides w-1 */
    a = 1;
    while (!BN_is_bit_set(w1, a))
        a++;
    /* (Step 2) m = (w-1) / 2^a */
    if (!BN_rshift(m, w1, a))
        goto err;

    /* Montgomery setup for computations mod a */
    mont = BN_MONT_CTX_new();
    if (mont == NULL || !BN_MONT_CTX_set(mont, w, ctx))
        goto err;

    if (iterations == 0)
        iterations = bn_mr_min_checks(BN_num_bits(w));

    /* (Step 4) */
    for (i = 0; i < iterations; ++i) {
        /* (Step 4.1) obtain a Random string of bits b where 1 < b < w-1 */
        if (!BN_priv_rand_range_ex(b, w3, ctx)
                || !BN_add_word(b, 2)) /* 1 < b < w-1 */
            goto err;

        if (enhanced) {
            /* (Step 4.3) */
            if (!BN_gcd(g, b, w, ctx))
                goto err;
            /* (Step 4.4) */
            if (!BN_is_one(g)) {
                *status = BN_PRIMETEST_COMPOSITE_WITH_FACTOR;
                ret = 1;
                goto err;
            }
        }
        /* (Step 4.5) z = b^m mod w */
        if (!BN_mod_exp_mont(z, b, m, w, ctx, mont))
            goto err;
        /* (Step 4.6) if (z = 1 or z = w-1) */
        if (BN_is_one(z) || BN_cmp(z, w1) == 0)
            goto outer_loop;
        /* (Step 4.7) for j = 1 to a-1 */
        for (j = 1; j < a ; ++j) {
            /* (Step 4.7.1 - 4.7.2) x = z. z = x^2 mod w */
            if (!BN_copy(x, z) || !BN_mod_mul(z, x, x, w, ctx))
                goto err;
            /* (Step 4.7.3) */
            if (BN_cmp(z, w1) == 0)
                goto outer_loop;
            /* (Step 4.7.4) */
            if (BN_is_one(z))
                goto composite;
        }
        /* At this point z = b^((w-1)/2) mod w */
        /* (Steps 4.8 - 4.9) x = z, z = x^2 mod w */
        if (!BN_copy(x, z) || !BN_mod_mul(z, x, x, w, ctx))
            goto err;
        /* (Step 4.10) */
        if (BN_is_one(z))
            goto composite;
        /* (Step 4.11) x = b^(w-1) mod w */
        if (!BN_copy(x, z))
            goto err;
composite:
        if (enhanced) {
            /* (Step 4.1.2) g = GCD(x-1, w) */
            if (!BN_sub_word(x, 1) || !BN_gcd(g, x, w, ctx))
                goto err;
            /* (Steps 4.1.3 - 4.1.4) */
            if (BN_is_one(g))
                *status = BN_PRIMETEST_COMPOSITE_NOT_POWER_OF_PRIME;
            else
                *status = BN_PRIMETEST_COMPOSITE_WITH_FACTOR;
        } else {
            *status = BN_PRIMETEST_COMPOSITE;
        }
        ret = 1;
        goto err;
outer_loop: ;
        /* (Step 4.1.5) */
        if (!BN_GENCB_call(cb, 1, i))
            goto err;
    }
    /* (Step 5) */
    *status = BN_PRIMETEST_PROBABLY_PRIME;
    ret = 1;
err:
    BN_clear(g);
    BN_clear(w1);
    BN_clear(w3);
    BN_clear(x);
    BN_clear(m);
    BN_clear(z);
    BN_clear(b);
    BN_CTX_end(ctx);
    BN_MONT_CTX_free(mont);
    return ret;
}