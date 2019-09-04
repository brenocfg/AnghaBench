#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  d; int /*<<< orphan*/  e; int /*<<< orphan*/  q; int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ RSA ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_one (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_mod_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BN_num_bits (int /*<<< orphan*/ ) ; 
 int rsa_get_lcm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int rsa_check_private_exponent(const RSA *rsa, int nbits, BN_CTX *ctx)
{
    int ret;
    BIGNUM *r, *p1, *q1, *lcm, *p1q1, *gcd;

    /* (Step 6a) 2^(nbits/2) < d */
    if (BN_num_bits(rsa->d) <= (nbits >> 1))
        return 0;

    BN_CTX_start(ctx);
    r = BN_CTX_get(ctx);
    p1 = BN_CTX_get(ctx);
    q1 = BN_CTX_get(ctx);
    lcm = BN_CTX_get(ctx);
    p1q1 = BN_CTX_get(ctx);
    gcd = BN_CTX_get(ctx);
    ret = (gcd != NULL
          /* LCM(p - 1, q - 1) */
          && (rsa_get_lcm(ctx, rsa->p, rsa->q, lcm, gcd, p1, q1, p1q1) == 1)
          /* (Step 6a) d < LCM(p - 1, q - 1) */
          && (BN_cmp(rsa->d, lcm) < 0)
          /* (Step 6b) 1 = (e . d) mod LCM(p - 1, q - 1) */
          && BN_mod_mul(r, rsa->e, rsa->d, lcm, ctx)
          && BN_is_one(r));

    BN_clear(p1);
    BN_clear(q1);
    BN_clear(lcm);
    BN_clear(gcd);
    BN_CTX_end(ctx);
    return ret;
}