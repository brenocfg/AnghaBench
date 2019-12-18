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
typedef  scalar_t__ prime_t ;
typedef  scalar_t__ BN_ULONG ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_MASK2 ; 
 int /*<<< orphan*/  BN_RAND_BOTTOM_ODD ; 
 int /*<<< orphan*/  BN_RAND_TOP_TWO ; 
 int /*<<< orphan*/  BN_add_word (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ BN_get_word (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_mod_word (int /*<<< orphan*/ *,scalar_t__) ; 
 int BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_priv_rand_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_bit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/ *) ; 
 int calc_trial_divisions (int) ; 
 scalar_t__* primes ; 
 scalar_t__ square (scalar_t__) ; 

__attribute__((used)) static int probable_prime(BIGNUM *rnd, int bits, int safe, prime_t *mods,
                          BN_CTX *ctx)
{
    int i;
    BN_ULONG delta;
    int trial_divisions = calc_trial_divisions(bits);
    BN_ULONG maxdelta = BN_MASK2 - primes[trial_divisions - 1];

 again:
    /* TODO: Not all primes are private */
    if (!BN_priv_rand_ex(rnd, bits, BN_RAND_TOP_TWO, BN_RAND_BOTTOM_ODD, ctx))
        return 0;
    if (safe && !BN_set_bit(rnd, 1))
        return 0;
    /* we now have a random number 'rnd' to test. */
    for (i = 1; i < trial_divisions; i++) {
        BN_ULONG mod = BN_mod_word(rnd, (BN_ULONG)primes[i]);
        if (mod == (BN_ULONG)-1)
            return 0;
        mods[i] = (prime_t) mod;
    }
    delta = 0;
 loop:
    for (i = 1; i < trial_divisions; i++) {
        /*
         * check that rnd is a prime and also that
         * gcd(rnd-1,primes) == 1 (except for 2)
         * do the second check only if we are interested in safe primes
         * in the case that the candidate prime is a single word then
         * we check only the primes up to sqrt(rnd)
         */
        if (bits <= 31 && delta <= 0x7fffffff
                && square(primes[i]) > BN_get_word(rnd) + delta)
            break;
        if (safe ? (mods[i] + delta) % primes[i] <= 1
                 : (mods[i] + delta) % primes[i] == 0) {
            delta += safe ? 4 : 2;
            if (delta > maxdelta)
                goto again;
            goto loop;
        }
    }
    if (!BN_add_word(rnd, delta))
        return 0;
    if (BN_num_bits(rnd) != bits)
        goto again;
    bn_check_top(rnd);
    return 1;
}