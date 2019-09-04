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
 int /*<<< orphan*/  BN_dec2bn (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_BN_abs_eq_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEST_BN_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_eq_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_eq_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEST_BN_eq_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_even (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_ge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_ge_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_gt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_gt_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_le (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_le_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_lt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_lt_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_ne (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_ne_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_odd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int test_bignum(void)
{
    BIGNUM *a = NULL, *b = NULL, *c = NULL;
    int r = 0;

    if (!TEST(1, TEST_int_eq(BN_dec2bn(&a, "0"), 1))
        | !TEST(1, TEST_BN_eq_word(a, 0))
        | !TEST(0, TEST_BN_eq_word(a, 30))
        | !TEST(1, TEST_BN_abs_eq_word(a, 0))
        | !TEST(0, TEST_BN_eq_one(a))
        | !TEST(1, TEST_BN_eq_zero(a))
        | !TEST(0, TEST_BN_ne_zero(a))
        | !TEST(1, TEST_BN_le_zero(a))
        | !TEST(0, TEST_BN_lt_zero(a))
        | !TEST(1, TEST_BN_ge_zero(a))
        | !TEST(0, TEST_BN_gt_zero(a))
        | !TEST(1, TEST_BN_even(a))
        | !TEST(0, TEST_BN_odd(a))
        | !TEST(1, TEST_BN_eq(b, c))
        | !TEST(0, TEST_BN_eq(a, b))
        | !TEST(0, TEST_BN_ne(NULL, c))
        | !TEST(1, TEST_int_eq(BN_dec2bn(&b, "1"), 1))
        | !TEST(1, TEST_BN_eq_word(b, 1))
        | !TEST(1, TEST_BN_eq_one(b))
        | !TEST(0, TEST_BN_abs_eq_word(b, 0))
        | !TEST(1, TEST_BN_abs_eq_word(b, 1))
        | !TEST(0, TEST_BN_eq_zero(b))
        | !TEST(1, TEST_BN_ne_zero(b))
        | !TEST(0, TEST_BN_le_zero(b))
        | !TEST(0, TEST_BN_lt_zero(b))
        | !TEST(1, TEST_BN_ge_zero(b))
        | !TEST(1, TEST_BN_gt_zero(b))
        | !TEST(0, TEST_BN_even(b))
        | !TEST(1, TEST_BN_odd(b))
        | !TEST(1, TEST_int_eq(BN_dec2bn(&c, "-334739439"), 10))
        | !TEST(0, TEST_BN_eq_word(c, 334739439))
        | !TEST(1, TEST_BN_abs_eq_word(c, 334739439))
        | !TEST(0, TEST_BN_eq_zero(c))
        | !TEST(1, TEST_BN_ne_zero(c))
        | !TEST(1, TEST_BN_le_zero(c))
        | !TEST(1, TEST_BN_lt_zero(c))
        | !TEST(0, TEST_BN_ge_zero(c))
        | !TEST(0, TEST_BN_gt_zero(c))
        | !TEST(0, TEST_BN_even(c))
        | !TEST(1, TEST_BN_odd(c))
        | !TEST(1, TEST_BN_eq(a, a))
        | !TEST(0, TEST_BN_ne(a, a))
        | !TEST(0, TEST_BN_eq(a, b))
        | !TEST(1, TEST_BN_ne(a, b))
        | !TEST(0, TEST_BN_lt(a, c))
        | !TEST(1, TEST_BN_lt(c, b))
        | !TEST(0, TEST_BN_lt(b, c))
        | !TEST(0, TEST_BN_le(a, c))
        | !TEST(1, TEST_BN_le(c, b))
        | !TEST(0, TEST_BN_le(b, c))
        | !TEST(1, TEST_BN_gt(a, c))
        | !TEST(0, TEST_BN_gt(c, b))
        | !TEST(1, TEST_BN_gt(b, c))
        | !TEST(1, TEST_BN_ge(a, c))
        | !TEST(0, TEST_BN_ge(c, b))
        | !TEST(1, TEST_BN_ge(b, c)))
        goto err;

    r = 1;
err:
    BN_free(a);
    BN_free(b);
    BN_free(c);
    return r;
}