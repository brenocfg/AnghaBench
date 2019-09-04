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
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_RAND_BOTTOM_ODD ; 
 int /*<<< orphan*/  BN_RAND_TOP_ONE ; 
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_add_word (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  BN_lshift1 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_mod (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_mod_word (int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  BN_rand (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_rshift1 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int NUMPRIMES ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/  const*) ; 
 scalar_t__* primes ; 

__attribute__((used)) static int probable_prime_dh_safe(BIGNUM *p, int bits, const BIGNUM *padd,
                                  const BIGNUM *rem, BN_CTX *ctx)
{
    int i, ret = 0;
    BIGNUM *t1, *qadd, *q;

    bits--;
    BN_CTX_start(ctx);
    t1 = BN_CTX_get(ctx);
    q = BN_CTX_get(ctx);
    qadd = BN_CTX_get(ctx);
    if (qadd == NULL)
        goto err;

    if (!BN_rshift1(qadd, padd))
        goto err;

    if (!BN_rand(q, bits, BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ODD))
        goto err;

    /* we need ((rnd-rem) % add) == 0 */
    if (!BN_mod(t1, q, qadd, ctx))
        goto err;
    if (!BN_sub(q, q, t1))
        goto err;
    if (rem == NULL) {
        if (!BN_add_word(q, 1))
            goto err;
    } else {
        if (!BN_rshift1(t1, rem))
            goto err;
        if (!BN_add(q, q, t1))
            goto err;
    }

    /* we now have a random number 'rand' to test. */
    if (!BN_lshift1(p, q))
        goto err;
    if (!BN_add_word(p, 1))
        goto err;

 loop:
    for (i = 1; i < NUMPRIMES; i++) {
        /* check that p and q are prime */
        /*
         * check that for p and q gcd(p-1,primes) == 1 (except for 2)
         */
        BN_ULONG pmod = BN_mod_word(p, (BN_ULONG)primes[i]);
        BN_ULONG qmod = BN_mod_word(q, (BN_ULONG)primes[i]);
        if (pmod == (BN_ULONG)-1 || qmod == (BN_ULONG)-1)
            goto err;
        if (pmod == 0 || qmod == 0) {
            if (!BN_add(p, p, padd))
                goto err;
            if (!BN_add(q, q, qadd))
                goto err;
            goto loop;
        }
    }
    ret = 1;

 err:
    BN_CTX_end(ctx);
    bn_check_top(p);
    return ret;
}