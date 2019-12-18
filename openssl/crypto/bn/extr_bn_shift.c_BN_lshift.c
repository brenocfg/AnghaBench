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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_F_BN_LSHIFT ; 
 int /*<<< orphan*/  BN_R_INVALID_SHIFT ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bn_correct_top (int /*<<< orphan*/ *) ; 
 int bn_lshift_fixed_top (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int BN_lshift(BIGNUM *r, const BIGNUM *a, int n)
{
    int ret;

    if (n < 0) {
        BNerr(BN_F_BN_LSHIFT, BN_R_INVALID_SHIFT);
        return 0;
    }

    ret = bn_lshift_fixed_top(r, a, n);

    bn_correct_top(r);
    bn_check_top(r);

    return ret;
}