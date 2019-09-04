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
 scalar_t__ BN_div (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_gcd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_value_one () ; 

int rsa_get_lcm(BN_CTX *ctx, const BIGNUM *p, const BIGNUM *q,
                BIGNUM *lcm, BIGNUM *gcd, BIGNUM *p1, BIGNUM *q1,
                BIGNUM *p1q1)
{
    return BN_sub(p1, p, BN_value_one())    /* p-1 */
           && BN_sub(q1, q, BN_value_one()) /* q-1 */
           && BN_mul(p1q1, p1, q1, ctx)     /* (p-1)(q-1) */
           && BN_gcd(gcd, p1, q1, ctx)
           && BN_div(lcm, NULL, p1q1, gcd, ctx); /* LCM((p-1, q-1)) */
}