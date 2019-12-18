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
 int /*<<< orphan*/  BN_GENCB_set_old (int /*<<< orphan*/ *,void (*) (int,int,void*),void*) ; 
 int bn_check_prime_int (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int BN_is_prime_fasttest(const BIGNUM *a, int checks,
                         void (*callback) (int, int, void *),
                         BN_CTX *ctx_passed, void *cb_arg,
                         int do_trial_division)
{
    BN_GENCB cb;
    BN_GENCB_set_old(&cb, callback, cb_arg);
    return bn_check_prime_int(a, checks, ctx_passed, do_trial_division, &cb);
}