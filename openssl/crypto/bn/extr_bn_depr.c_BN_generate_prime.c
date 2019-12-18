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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_GENCB_set_old (int /*<<< orphan*/ *,void (*) (int,int,void*),void*) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_generate_prime_ex (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 

BIGNUM *BN_generate_prime(BIGNUM *ret, int bits, int safe,
                          const BIGNUM *add, const BIGNUM *rem,
                          void (*callback) (int, int, void *), void *cb_arg)
{
    BN_GENCB cb;
    BIGNUM *rnd = NULL;

    BN_GENCB_set_old(&cb, callback, cb_arg);

    if (ret == NULL) {
        if ((rnd = BN_new()) == NULL)
            goto err;
    } else
        rnd = ret;
    if (!BN_generate_prime_ex(rnd, bits, safe, add, rem, &cb))
        goto err;

    /* we have a prime :-) */
    return rnd;
 err:
    BN_free(rnd);
    return NULL;
}