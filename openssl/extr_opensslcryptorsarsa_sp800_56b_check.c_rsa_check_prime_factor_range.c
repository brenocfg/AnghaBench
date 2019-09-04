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
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_lshift (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_rshift (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int) ; 

int rsa_check_prime_factor_range(const BIGNUM *p, int nbits, BN_CTX *ctx)
{
    int ret = 0;
    BIGNUM *tmp, *low;

    nbits >>= 1;

    /* Upper bound check */
    if (BN_num_bits(p) != nbits)
        return 0;

    BN_CTX_start(ctx);
    tmp = BN_CTX_get(ctx);
    low = BN_CTX_get(ctx);

    /* set low = (√2)(2^(nbits/2 - 1) */
    if (low == NULL || !BN_set_word(tmp, 0xB504F334))
        goto err;

    if (nbits >= 32) {
        if (!BN_lshift(low, tmp, nbits - 32))
            goto err;
    } else if (!BN_rshift(low, tmp, 32 - nbits)) {
        goto err;
    }
    if (BN_cmp(p, low) < 0)
        goto err;
    ret = 1;
err:
    BN_CTX_end(ctx);
    return ret;
}