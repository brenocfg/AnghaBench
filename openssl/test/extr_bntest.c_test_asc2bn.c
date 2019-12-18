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
 int /*<<< orphan*/  BN_asc2bn (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  TEST_BN_abs_eq_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEST_BN_eq_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEST_BN_eq_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_ge_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_lt_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_asc2bn(void)
{
    BIGNUM *bn = NULL;
    int st = 0;

    if (!TEST_ptr(bn = BN_new()))
        goto err;

    if (!TEST_true(BN_asc2bn(&bn, "0"))
            || !TEST_BN_eq_zero(bn)
            || !TEST_BN_ge_zero(bn))
        goto err;

    if (!TEST_true(BN_asc2bn(&bn, "256"))
            || !TEST_BN_eq_word(bn, 256)
            || !TEST_BN_ge_zero(bn))
        goto err;

    if (!TEST_true(BN_asc2bn(&bn, "-42"))
            || !TEST_BN_abs_eq_word(bn, 42)
            || !TEST_BN_lt_zero(bn))
        goto err;

    if (!TEST_true(BN_asc2bn(&bn, "0x1234"))
            || !TEST_BN_eq_word(bn, 0x1234)
            || !TEST_BN_ge_zero(bn))
        goto err;

    if (!TEST_true(BN_asc2bn(&bn, "0X1234"))
            || !TEST_BN_eq_word(bn, 0x1234)
            || !TEST_BN_ge_zero(bn))
        goto err;

    if (!TEST_true(BN_asc2bn(&bn, "-0xabcd"))
            || !TEST_BN_abs_eq_word(bn, 0xabcd)
            || !TEST_BN_lt_zero(bn))
        goto err;

    if (!TEST_true(BN_asc2bn(&bn, "-0"))
            || !TEST_BN_eq_zero(bn)
            || !TEST_BN_ge_zero(bn))
        goto err;

    if (!TEST_true(BN_asc2bn(&bn, "123trailing garbage is ignored"))
            || !TEST_BN_eq_word(bn, 123)
            || !TEST_BN_ge_zero(bn))
        goto err;

    st = 1;
 err:
    BN_free(bn);
    return st;
}