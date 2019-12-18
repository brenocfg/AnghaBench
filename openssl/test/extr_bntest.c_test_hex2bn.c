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
 int /*<<< orphan*/  TEST_BN_abs_eq_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEST_BN_eq_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEST_BN_eq_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_even (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_ge_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_gt_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_le_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_lt_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_ne_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_odd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parseBN (int /*<<< orphan*/ **,char*) ; 

__attribute__((used)) static int test_hex2bn(void)
{
    BIGNUM *bn = NULL;
    int st = 0;

    if (!TEST_int_eq(parseBN(&bn, "0"), 1)
            || !TEST_BN_eq_zero(bn)
            || !TEST_BN_ge_zero(bn)
            || !TEST_BN_even(bn))
        goto err;
    BN_free(bn);
    bn = NULL;

    if (!TEST_int_eq(parseBN(&bn, "256"), 3)
            || !TEST_BN_eq_word(bn, 0x256)
            || !TEST_BN_ge_zero(bn)
            || !TEST_BN_gt_zero(bn)
            || !TEST_BN_ne_zero(bn)
            || !TEST_BN_even(bn))
        goto err;
    BN_free(bn);
    bn = NULL;

    if (!TEST_int_eq(parseBN(&bn, "-42"), 3)
            || !TEST_BN_abs_eq_word(bn, 0x42)
            || !TEST_BN_lt_zero(bn)
            || !TEST_BN_le_zero(bn)
            || !TEST_BN_ne_zero(bn)
            || !TEST_BN_even(bn))
        goto err;
    BN_free(bn);
    bn = NULL;

    if (!TEST_int_eq(parseBN(&bn, "cb"), 2)
            || !TEST_BN_eq_word(bn, 0xCB)
            || !TEST_BN_ge_zero(bn)
            || !TEST_BN_gt_zero(bn)
            || !TEST_BN_ne_zero(bn)
            || !TEST_BN_odd(bn))
        goto err;
    BN_free(bn);
    bn = NULL;

    if (!TEST_int_eq(parseBN(&bn, "-0"), 2)
            || !TEST_BN_eq_zero(bn)
            || !TEST_BN_ge_zero(bn)
            || !TEST_BN_le_zero(bn)
            || !TEST_BN_even(bn))
        goto err;
    BN_free(bn);
    bn = NULL;

    if (!TEST_int_eq(parseBN(&bn, "abctrailing garbage is ignored"), 3)
            || !TEST_BN_eq_word(bn, 0xabc)
            || !TEST_BN_ge_zero(bn)
            || !TEST_BN_gt_zero(bn)
            || !TEST_BN_ne_zero(bn)
            || !TEST_BN_even(bn))
        goto err;
    st = 1;

 err:
    BN_free(bn);
    return st;
}