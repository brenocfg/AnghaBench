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
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_gcd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_generate_prime_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_is_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int NUM0 ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx ; 

__attribute__((used)) static int test_gcd_prime(void)
{
    BIGNUM *a = NULL, *b = NULL, *gcd = NULL;
    int i, st = 0;

    if (!TEST_ptr(a = BN_new())
            || !TEST_ptr(b = BN_new())
            || !TEST_ptr(gcd = BN_new()))
        goto err;

    if (!TEST_true(BN_generate_prime_ex(a, 1024, 0, NULL, NULL, NULL)))
            goto err;
    for (i = 0; i < NUM0; i++) {
        if (!TEST_true(BN_generate_prime_ex(b, 1024, 0,
                                            NULL, NULL, NULL))
                || !TEST_true(BN_gcd(gcd, a, b, ctx))
                || !TEST_true(BN_is_one(gcd)))
            goto err;
    }

    st = 1;
 err:
    BN_free(a);
    BN_free(b);
    BN_free(gcd);
    return st;
}