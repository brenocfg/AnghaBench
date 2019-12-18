#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ neg; } ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BNRAND_FLAG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_F_BNRAND_RANGE ; 
 int /*<<< orphan*/  BN_RAND_BOTTOM_ANY ; 
 int /*<<< orphan*/  BN_RAND_TOP_ANY ; 
 int /*<<< orphan*/  BN_R_INVALID_RANGE ; 
 int /*<<< orphan*/  BN_R_TOO_MANY_ITERATIONS ; 
 scalar_t__ BN_cmp (TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  BN_is_bit_set (TYPE_1__ const*,int) ; 
 scalar_t__ BN_is_zero (TYPE_1__ const*) ; 
 int BN_num_bits (TYPE_1__ const*) ; 
 int /*<<< orphan*/  BN_sub (TYPE_1__*,TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  BN_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_check_top (TYPE_1__*) ; 
 int /*<<< orphan*/  bnrand (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnrand_range(BNRAND_FLAG flag, BIGNUM *r, const BIGNUM *range,
                        BN_CTX *ctx)
{
    int n;
    int count = 100;

    if (range->neg || BN_is_zero(range)) {
        BNerr(BN_F_BNRAND_RANGE, BN_R_INVALID_RANGE);
        return 0;
    }

    n = BN_num_bits(range);     /* n > 0 */

    /* BN_is_bit_set(range, n - 1) always holds */

    if (n == 1)
        BN_zero(r);
    else if (!BN_is_bit_set(range, n - 2) && !BN_is_bit_set(range, n - 3)) {
        /*
         * range = 100..._2, so 3*range (= 11..._2) is exactly one bit longer
         * than range
         */
        do {
            if (!bnrand(flag, r, n + 1, BN_RAND_TOP_ANY, BN_RAND_BOTTOM_ANY,
                        ctx))
                return 0;

            /*
             * If r < 3*range, use r := r MOD range (which is either r, r -
             * range, or r - 2*range). Otherwise, iterate once more. Since
             * 3*range = 11..._2, each iteration succeeds with probability >=
             * .75.
             */
            if (BN_cmp(r, range) >= 0) {
                if (!BN_sub(r, r, range))
                    return 0;
                if (BN_cmp(r, range) >= 0)
                    if (!BN_sub(r, r, range))
                        return 0;
            }

            if (!--count) {
                BNerr(BN_F_BNRAND_RANGE, BN_R_TOO_MANY_ITERATIONS);
                return 0;
            }

        }
        while (BN_cmp(r, range) >= 0);
    } else {
        do {
            /* range = 11..._2  or  range = 101..._2 */
            if (!bnrand(flag, r, n, BN_RAND_TOP_ANY, BN_RAND_BOTTOM_ANY, ctx))
                return 0;

            if (!--count) {
                BNerr(BN_F_BNRAND_RANGE, BN_R_TOO_MANY_ITERATIONS);
                return 0;
            }
        }
        while (BN_cmp(r, range) >= 0);
    }

    bn_check_top(r);
    return 1;
}