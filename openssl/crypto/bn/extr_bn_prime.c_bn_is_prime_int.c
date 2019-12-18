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
typedef  scalar_t__ BN_ULONG ;
typedef  int /*<<< orphan*/  BN_GENCB ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_GENCB_call (int /*<<< orphan*/ *,int,int) ; 
 int BN_PRIMETEST_PROBABLY_PRIME ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ BN_is_odd (int /*<<< orphan*/  const*) ; 
 int BN_is_word (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ BN_mod_word (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_value_one () ; 
 int bn_miller_rabin_is_prime (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int calc_trial_divisions (int /*<<< orphan*/ ) ; 
 int* primes ; 

__attribute__((used)) static int bn_is_prime_int(const BIGNUM *w, int checks, BN_CTX *ctx,
                           int do_trial_division, BN_GENCB *cb)
{
    int i, status, ret = -1;
#ifndef FIPS_MODE
    BN_CTX *ctxlocal = NULL;
#else

    if (ctx == NULL)
        return -1;
#endif

    /* w must be bigger than 1 */
    if (BN_cmp(w, BN_value_one()) <= 0)
        return 0;

    /* w must be odd */
    if (BN_is_odd(w)) {
        /* Take care of the really small prime 3 */
        if (BN_is_word(w, 3))
            return 1;
    } else {
        /* 2 is the only even prime */
        return BN_is_word(w, 2);
    }

    /* first look for small factors */
    if (do_trial_division) {
        int trial_divisions = calc_trial_divisions(BN_num_bits(w));

        for (i = 1; i < trial_divisions; i++) {
            BN_ULONG mod = BN_mod_word(w, primes[i]);
            if (mod == (BN_ULONG)-1)
                return -1;
            if (mod == 0)
                return BN_is_word(w, primes[i]);
        }
        if (!BN_GENCB_call(cb, 1, -1))
            return -1;
    }
#ifndef FIPS_MODE
    if (ctx == NULL && (ctxlocal = ctx = BN_CTX_new()) == NULL)
        goto err;
#endif

    ret = bn_miller_rabin_is_prime(w, checks, ctx, cb, 0, &status);
    if (!ret)
        goto err;
    ret = (status == BN_PRIMETEST_PROBABLY_PRIME);
err:
#ifndef FIPS_MODE
    BN_CTX_free(ctxlocal);
#endif
    return ret;
}