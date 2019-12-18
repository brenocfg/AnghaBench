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
typedef  scalar_t__ BN_ULONG ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_add_word (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_get_word (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_is_negative (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_sub_word (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  BN_uadd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_usub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  equalBN (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getBN (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int file_sum(STANZA *s)
{
    BIGNUM *a = NULL, *b = NULL, *sum = NULL, *ret = NULL;
    BN_ULONG b_word;
    int st = 0;

    if (!TEST_ptr(a = getBN(s, "A"))
            || !TEST_ptr(b = getBN(s, "B"))
            || !TEST_ptr(sum = getBN(s, "Sum"))
            || !TEST_ptr(ret = BN_new()))
        goto err;

    if (!TEST_true(BN_add(ret, a, b))
            || !equalBN("A + B", sum, ret)
            || !TEST_true(BN_sub(ret, sum, a))
            || !equalBN("Sum - A", b, ret)
            || !TEST_true(BN_sub(ret, sum, b))
            || !equalBN("Sum - B", a, ret))
        goto err;

    /*
     * Test that the functions work when |r| and |a| point to the same BIGNUM,
     * or when |r| and |b| point to the same BIGNUM.
     * TODO: Test where all of |r|, |a|, and |b| point to the same BIGNUM.
     */
    if (!TEST_true(BN_copy(ret, a))
            || !TEST_true(BN_add(ret, ret, b))
            || !equalBN("A + B (r is a)", sum, ret)
            || !TEST_true(BN_copy(ret, b))
            || !TEST_true(BN_add(ret, a, ret))
            || !equalBN("A + B (r is b)", sum, ret)
            || !TEST_true(BN_copy(ret, sum))
            || !TEST_true(BN_sub(ret, ret, a))
            || !equalBN("Sum - A (r is a)", b, ret)
            || !TEST_true(BN_copy(ret, a))
            || !TEST_true(BN_sub(ret, sum, ret))
            || !equalBN("Sum - A (r is b)", b, ret)
            || !TEST_true(BN_copy(ret, sum))
            || !TEST_true(BN_sub(ret, ret, b))
            || !equalBN("Sum - B (r is a)", a, ret)
            || !TEST_true(BN_copy(ret, b))
            || !TEST_true(BN_sub(ret, sum, ret))
            || !equalBN("Sum - B (r is b)", a, ret))
        goto err;

    /*
     * Test BN_uadd() and BN_usub() with the prerequisites they are
     * documented as having. Note that these functions are frequently used
     * when the prerequisites don't hold. In those cases, they are supposed
     * to work as if the prerequisite hold, but we don't test that yet.
     * TODO: test that.
     */
    if (!BN_is_negative(a) && !BN_is_negative(b) && BN_cmp(a, b) >= 0) {
        if (!TEST_true(BN_uadd(ret, a, b))
                || !equalBN("A +u B", sum, ret)
                || !TEST_true(BN_usub(ret, sum, a))
                || !equalBN("Sum -u A", b, ret)
                || !TEST_true(BN_usub(ret, sum, b))
                || !equalBN("Sum -u B", a, ret))
            goto err;
        /*
         * Test that the functions work when |r| and |a| point to the same
         * BIGNUM, or when |r| and |b| point to the same BIGNUM.
         * TODO: Test where all of |r|, |a|, and |b| point to the same BIGNUM.
         */
        if (!TEST_true(BN_copy(ret, a))
                || !TEST_true(BN_uadd(ret, ret, b))
                || !equalBN("A +u B (r is a)", sum, ret)
                || !TEST_true(BN_copy(ret, b))
                || !TEST_true(BN_uadd(ret, a, ret))
                || !equalBN("A +u B (r is b)", sum, ret)
                || !TEST_true(BN_copy(ret, sum))
                || !TEST_true(BN_usub(ret, ret, a))
                || !equalBN("Sum -u A (r is a)", b, ret)
                || !TEST_true(BN_copy(ret, a))
                || !TEST_true(BN_usub(ret, sum, ret))
                || !equalBN("Sum -u A (r is b)", b, ret)
                || !TEST_true(BN_copy(ret, sum))
                || !TEST_true(BN_usub(ret, ret, b))
                || !equalBN("Sum -u B (r is a)", a, ret)
                || !TEST_true(BN_copy(ret, b))
                || !TEST_true(BN_usub(ret, sum, ret))
                || !equalBN("Sum -u B (r is b)", a, ret))
            goto err;
    }

    /*
     * Test with BN_add_word() and BN_sub_word() if |b| is small enough.
     */
    b_word = BN_get_word(b);
    if (!BN_is_negative(b) && b_word != (BN_ULONG)-1) {
        if (!TEST_true(BN_copy(ret, a))
                || !TEST_true(BN_add_word(ret, b_word))
                || !equalBN("A + B (word)", sum, ret)
                || !TEST_true(BN_copy(ret, sum))
                || !TEST_true(BN_sub_word(ret, b_word))
                || !equalBN("Sum - B (word)", a, ret))
            goto err;
    }
    st = 1;

 err:
    BN_free(a);
    BN_free(b);
    BN_free(sum);
    BN_free(ret);
    return st;
}