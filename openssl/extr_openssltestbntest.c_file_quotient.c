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
 int /*<<< orphan*/ * BN_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_div (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ BN_div_word (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_get_word (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_mod_word (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * BN_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/ * BN_nnmod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_error (char*) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  equalBN (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getBN (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int file_quotient(STANZA *s)
{
    BIGNUM *a = NULL, *b = NULL, *quotient = NULL, *remainder = NULL;
    BIGNUM *ret = NULL, *ret2 = NULL, *nnmod = NULL;
    BN_ULONG b_word, ret_word;
    int st = 0;

    if (!TEST_ptr(a = getBN(s, "A"))
            || !TEST_ptr(b = getBN(s, "B"))
            || !TEST_ptr(quotient = getBN(s, "Quotient"))
            || !TEST_ptr(remainder = getBN(s, "Remainder"))
            || !TEST_ptr(ret = BN_new())
            || !TEST_ptr(ret2 = BN_new())
            || !TEST_ptr(nnmod = BN_new()))
        goto err;

    if (!TEST_true(BN_div(ret, ret2, a, b, ctx))
            || !equalBN("A / B", quotient, ret)
            || !equalBN("A % B", remainder, ret2)
            || !TEST_true(BN_mul(ret, quotient, b, ctx))
            || !TEST_true(BN_add(ret, ret, remainder))
            || !equalBN("Quotient * B + Remainder", a, ret))
        goto err;

    /*
     * Test with BN_mod_word() and BN_div_word() if the divisor is
     * small enough.
     */
    b_word = BN_get_word(b);
    if (!BN_is_negative(b) && b_word != (BN_ULONG)-1) {
        BN_ULONG remainder_word = BN_get_word(remainder);

        assert(remainder_word != (BN_ULONG)-1);
        if (!TEST_ptr(BN_copy(ret, a)))
            goto err;
        ret_word = BN_div_word(ret, b_word);
        if (ret_word != remainder_word) {
#ifdef BN_DEC_FMT1
            TEST_error(
                    "Got A %% B (word) = " BN_DEC_FMT1 ", wanted " BN_DEC_FMT1,
                    ret_word, remainder_word);
#else
            TEST_error("Got A %% B (word) mismatch");
#endif
            goto err;
        }
        if (!equalBN ("A / B (word)", quotient, ret))
            goto err;

        ret_word = BN_mod_word(a, b_word);
        if (ret_word != remainder_word) {
#ifdef BN_DEC_FMT1
            TEST_error(
                    "Got A %% B (word) = " BN_DEC_FMT1 ", wanted " BN_DEC_FMT1 "",
                    ret_word, remainder_word);
#else
            TEST_error("Got A %% B (word) mismatch");
#endif
            goto err;
        }
    }

    /* Test BN_nnmod. */
    if (!BN_is_negative(b)) {
        if (!TEST_true(BN_copy(nnmod, remainder))
                || (BN_is_negative(nnmod)
                        && !TEST_true(BN_add(nnmod, nnmod, b)))
                || !TEST_true(BN_nnmod(ret, a, b, ctx))
                || !equalBN("A % B (non-negative)", nnmod, ret))
            goto err;
    }

    st = 1;
 err:
    BN_free(a);
    BN_free(b);
    BN_free(quotient);
    BN_free(remainder);
    BN_free(ret);
    BN_free(ret2);
    BN_free(nnmod);
    return st;
}