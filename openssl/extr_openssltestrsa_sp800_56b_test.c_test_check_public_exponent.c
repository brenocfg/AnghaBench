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
 int /*<<< orphan*/  BN_lshift (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_value_one () ; 
 scalar_t__ TEST_false (int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsa_check_public_exponent (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_check_public_exponent(void)
{
    int ret = 0;
    BIGNUM *e = NULL;

    ret = TEST_ptr(e = BN_new())
          /* e is too small */
          && TEST_true(BN_set_word(e, 65535))
          && TEST_false(rsa_check_public_exponent(e))
          /* e is even will fail */
          && TEST_true(BN_set_word(e, 65536))
          && TEST_false(rsa_check_public_exponent(e))
          /* e is ok */
          && TEST_true(BN_set_word(e, 65537))
          && TEST_true(rsa_check_public_exponent(e))
          /* e = 2^256 is too big */
          && TEST_true(BN_lshift(e, BN_value_one(), 256))
          && TEST_false(rsa_check_public_exponent(e))
          /* e = 2^256-1 is odd and in range */
          && TEST_true(BN_sub(e, e, BN_value_one()))
          && TEST_true(rsa_check_public_exponent(e));
    BN_free(e);
    return ret;
}