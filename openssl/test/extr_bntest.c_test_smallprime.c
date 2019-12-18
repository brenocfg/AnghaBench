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
 int /*<<< orphan*/  BN_generate_prime_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_smallprime(int kBits)
{
    BIGNUM *r;
    int st = 0;

    if (!TEST_ptr(r = BN_new()))
        goto err;

    if (kBits <= 1) {
        if (!TEST_false(BN_generate_prime_ex(r, kBits, 0,
                                             NULL, NULL, NULL)))
            goto err;
    } else {
        if (!TEST_true(BN_generate_prime_ex(r, kBits, 0,
                                            NULL, NULL, NULL))
                || !TEST_int_eq(BN_num_bits(r), kBits))
            goto err;
    }

    st = 1;
 err:
    BN_free(r);
    return st;
}