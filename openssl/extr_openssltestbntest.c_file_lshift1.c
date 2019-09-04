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
typedef  int /*<<< orphan*/  STANZA ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_div (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_lshift1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_rshift1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  equalBN (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getBN (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int file_lshift1(STANZA *s)
{
    BIGNUM *a = NULL, *lshift1 = NULL, *zero = NULL, *ret = NULL;
    BIGNUM *two = NULL, *remainder = NULL;
    int st = 0;

    if (!TEST_ptr(a = getBN(s, "A"))
            || !TEST_ptr(lshift1 = getBN(s, "LShift1"))
            || !TEST_ptr(zero = BN_new())
            || !TEST_ptr(ret = BN_new())
            || !TEST_ptr(two = BN_new())
            || !TEST_ptr(remainder = BN_new()))
        goto err;

    BN_zero(zero);

    if (!TEST_true(BN_set_word(two, 2))
            || !TEST_true(BN_add(ret, a, a))
            || !equalBN("A + A", lshift1, ret)
            || !TEST_true(BN_mul(ret, a, two, ctx))
            || !equalBN("A * 2", lshift1, ret)
            || !TEST_true(BN_div(ret, remainder, lshift1, two, ctx))
            || !equalBN("LShift1 / 2", a, ret)
            || !equalBN("LShift1 % 2", zero, remainder)
            || !TEST_true(BN_lshift1(ret, a))
            || !equalBN("A << 1", lshift1, ret)
            || !TEST_true(BN_rshift1(ret, lshift1))
            || !equalBN("LShift >> 1", a, ret)
            || !TEST_true(BN_rshift1(ret, lshift1))
            || !equalBN("LShift >> 1", a, ret))
        goto err;

    /* Set the LSB to 1 and test rshift1 again. */
    if (!TEST_true(BN_set_bit(lshift1, 0))
            || !TEST_true(BN_div(ret, NULL /* rem */ , lshift1, two, ctx))
            || !equalBN("(LShift1 | 1) / 2", a, ret)
            || !TEST_true(BN_rshift1(ret, lshift1))
            || !equalBN("(LShift | 1) >> 1", a, ret))
        goto err;

    st = 1;
 err:
    BN_free(a);
    BN_free(lshift1);
    BN_free(zero);
    BN_free(ret);
    BN_free(two);
    BN_free(remainder);

    return st;
}