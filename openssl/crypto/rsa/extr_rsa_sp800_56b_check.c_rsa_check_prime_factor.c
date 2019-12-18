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
 int BN_check_prime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_gcd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_one (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_sub_word (int /*<<< orphan*/ *,int) ; 
 int rsa_check_prime_factor_range (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int rsa_check_prime_factor(BIGNUM *p, BIGNUM *e, int nbits, BN_CTX *ctx)
{
    int ret = 0;
    BIGNUM *p1 = NULL, *gcd = NULL;

    /* (Steps 5 a-b) prime test */
    if (BN_check_prime(p, ctx, NULL) != 1
            /* (Step 5c) (√2)(2^(nbits/2 - 1) <= p <= 2^(nbits/2 - 1) */
            || rsa_check_prime_factor_range(p, nbits, ctx) != 1)
        return 0;

    BN_CTX_start(ctx);
    p1 = BN_CTX_get(ctx);
    gcd = BN_CTX_get(ctx);
    ret = (gcd != NULL)
          /* (Step 5d) GCD(p-1, e) = 1 */
          && (BN_copy(p1, p) != NULL)
          && BN_sub_word(p1, 1)
          && BN_gcd(gcd, p1, e, ctx)
          && BN_is_one(gcd);

    BN_clear(p1);
    BN_CTX_end(ctx);
    return ret;
}