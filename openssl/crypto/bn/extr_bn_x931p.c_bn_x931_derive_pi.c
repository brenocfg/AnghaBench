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
 int /*<<< orphan*/  BN_GENCB_call (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  BN_add_word (int /*<<< orphan*/ *,int) ; 
 int BN_check_prime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_is_odd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bn_x931_derive_pi(BIGNUM *pi, const BIGNUM *Xpi, BN_CTX *ctx,
                             BN_GENCB *cb)
{
    int i = 0, is_prime;
    if (!BN_copy(pi, Xpi))
        return 0;
    if (!BN_is_odd(pi) && !BN_add_word(pi, 1))
        return 0;
    for (;;) {
        i++;
        BN_GENCB_call(cb, 0, i);
        /* NB 27 MR is specified in X9.31 */
        is_prime = BN_check_prime(pi, ctx, cb);
        if (is_prime < 0)
            return 0;
        if (is_prime)
            break;
        if (!BN_add_word(pi, 2))
            return 0;
    }
    BN_GENCB_call(cb, 2, i);
    return 1;
}