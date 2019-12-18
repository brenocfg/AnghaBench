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
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_F_BN_MOD_LSHIFT_QUICK ; 
 int /*<<< orphan*/  BN_R_INPUT_NOT_REDUCED ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * BN_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_lshift (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  BN_lshift1 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/  const*) ; 

int BN_mod_lshift_quick(BIGNUM *r, const BIGNUM *a, int n, const BIGNUM *m)
{
    if (r != a) {
        if (BN_copy(r, a) == NULL)
            return 0;
    }

    while (n > 0) {
        int max_shift;

        /* 0 < r < m */
        max_shift = BN_num_bits(m) - BN_num_bits(r);
        /* max_shift >= 0 */

        if (max_shift < 0) {
            BNerr(BN_F_BN_MOD_LSHIFT_QUICK, BN_R_INPUT_NOT_REDUCED);
            return 0;
        }

        if (max_shift > n)
            max_shift = n;

        if (max_shift) {
            if (!BN_lshift(r, r, max_shift))
                return 0;
            n -= max_shift;
        } else {
            if (!BN_lshift1(r, r))
                return 0;
            --n;
        }

        /* BN_num_bits(r) <= BN_num_bits(m) */

        if (BN_cmp(r, m) >= 0) {
            if (!BN_sub(r, r, m))
                return 0;
        }
    }
    bn_check_top(r);

    return 1;
}