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
 int BN_BITS2 ; 
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int /*<<< orphan*/  BN_bntest_rand (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_consttime_swap (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_get_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_swap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  equalBN (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_swap(void)
{
    BIGNUM *a = NULL, *b = NULL, *c = NULL, *d = NULL;
    int top, cond, st = 0;

    if (!TEST_ptr(a = BN_new())
            || !TEST_ptr(b = BN_new())
            || !TEST_ptr(c = BN_new())
            || !TEST_ptr(d = BN_new()))
        goto err;

    if (!(TEST_true(BN_bntest_rand(a, 1024, 1, 0))
            && TEST_true(BN_bntest_rand(b, 1024, 1, 0))
            && TEST_ptr(BN_copy(c, a))
            && TEST_ptr(BN_copy(d, b))))
        goto err;
    top = BN_num_bits(a) / BN_BITS2;

    /* regular swap */
    BN_swap(a, b);
    if (!equalBN("swap", a, d)
            || !equalBN("swap", b, c))
        goto err;

    /* conditional swap: true */
    cond = 1;
    BN_consttime_swap(cond, a, b, top);
    if (!equalBN("cswap true", a, c)
            || !equalBN("cswap true", b, d))
        goto err;

    /* conditional swap: false */
    cond = 0;
    BN_consttime_swap(cond, a, b, top);
    if (!equalBN("cswap false", a, c)
            || !equalBN("cswap false", b, d))
        goto err;

    /* same tests but checking flag swap */
    BN_set_flags(a, BN_FLG_CONSTTIME);

    BN_swap(a, b);
    if (!equalBN("swap, flags", a, d)
            || !equalBN("swap, flags", b, c)
            || !TEST_true(BN_get_flags(b, BN_FLG_CONSTTIME))
            || !TEST_false(BN_get_flags(a, BN_FLG_CONSTTIME)))
        goto err;

    cond = 1;
    BN_consttime_swap(cond, a, b, top);
    if (!equalBN("cswap true, flags", a, c)
            || !equalBN("cswap true, flags", b, d)
            || !TEST_true(BN_get_flags(a, BN_FLG_CONSTTIME))
            || !TEST_false(BN_get_flags(b, BN_FLG_CONSTTIME)))
        goto err;

    cond = 0;
    BN_consttime_swap(cond, a, b, top);
    if (!equalBN("cswap false, flags", a, c)
            || !equalBN("cswap false, flags", b, d)
            || !TEST_true(BN_get_flags(a, BN_FLG_CONSTTIME))
            || !TEST_false(BN_get_flags(b, BN_FLG_CONSTTIME)))
        goto err;

    st = 1;
 err:
    BN_free(a);
    BN_free(b);
    BN_free(c);
    BN_free(d);
    return st;
}