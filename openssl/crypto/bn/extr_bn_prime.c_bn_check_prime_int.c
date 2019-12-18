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
 int /*<<< orphan*/  BN_num_bits (int /*<<< orphan*/  const*) ; 
 int bn_is_prime_int (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int bn_mr_min_checks (int /*<<< orphan*/ ) ; 

int bn_check_prime_int(const BIGNUM *w, int checks, BN_CTX *ctx,
                       int do_trial_division, BN_GENCB *cb)
{
    int min_checks = bn_mr_min_checks(BN_num_bits(w));

    if (checks < min_checks)
        checks = min_checks;

    return bn_is_prime_int(w, checks, ctx, do_trial_division, cb);
}