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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int BN_BITS2 ; 
 scalar_t__ BN_MASK2 ; 
 int /*<<< orphan*/  BN_RAND_BOTTOM_ODD ; 
 int /*<<< orphan*/  BN_RAND_TOP_TWO ; 
 int /*<<< orphan*/  BN_add_word (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ BN_get_word (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_mod_word (int /*<<< orphan*/ *,scalar_t__) ; 
 int BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_priv_rand (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NUMPRIMES ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/ *) ; 
 scalar_t__* primes ; 

__attribute__((used)) static int probable_prime(BIGNUM *rnd, int bits, prime_t *mods)
{
    int i;
    BN_ULONG delta;
    BN_ULONG maxdelta = BN_MASK2 - primes[NUMPRIMES - 1];
    char is_single_word = bits <= BN_BITS2;

 again:
    /* TODO: Not all primes are private */
    if (!BN_priv_rand(rnd, bits, BN_RAND_TOP_TWO, BN_RAND_BOTTOM_ODD))
        return 0;
    /* we now have a random number 'rnd' to test. */
    for (i = 1; i < NUMPRIMES; i++) {
        BN_ULONG mod = BN_mod_word(rnd, (BN_ULONG)primes[i]);
        if (mod == (BN_ULONG)-1)
            return 0;
        mods[i] = (prime_t) mod;
    }
    /*
     * If bits is so small that it fits into a single word then we
     * additionally don't want to exceed that many bits.
     */
    if (is_single_word) {
        BN_ULONG size_limit;

        if (bits == BN_BITS2) {
            /*
             * Shifting by this much has undefined behaviour so we do it a
             * different way
             */
            size_limit = ~((BN_ULONG)0) - BN_get_word(rnd);
        } else {
            size_limit = (((BN_ULONG)1) << bits) - BN_get_word(rnd) - 1;
        }
        if (size_limit < maxdelta)
            maxdelta = size_limit;
    }
    delta = 0;
 loop:
    if (is_single_word) {
        BN_ULONG rnd_word = BN_get_word(rnd);

        /*-
         * In the case that the candidate prime is a single word then
         * we check that:
         *   1) It's greater than primes[i] because we shouldn't reject
         *      3 as being a prime number because it's a multiple of
         *      three.
         *   2) That it's not a multiple of a known prime. We don't
         *      check that rnd-1 is also coprime to all the known
         *      primes because there aren't many small primes where
         *      that's true.
         */
        for (i = 1; i < NUMPRIMES && primes[i] < rnd_word; i++) {
            if ((mods[i] + delta) % primes[i] == 0) {
                delta += 2;
                if (delta > maxdelta)
                    goto again;
                goto loop;
            }
        }
    } else {
        for (i = 1; i < NUMPRIMES; i++) {
            /*
             * check that rnd is not a prime and also that gcd(rnd-1,primes)
             * == 1 (except for 2)
             */
            if (((mods[i] + delta) % primes[i]) <= 1) {
                delta += 2;
                if (delta > maxdelta)
                    goto again;
                goto loop;
            }
        }
    }
    if (!BN_add_word(rnd, delta))
        return 0;
    if (BN_num_bits(rnd) != bits)
        goto again;
    bn_check_top(rnd);
    return 1;
}