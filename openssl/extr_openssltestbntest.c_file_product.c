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
 int /*<<< orphan*/  BN_div (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  equalBN (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getBN (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int file_product(STANZA *s)
{
    BIGNUM *a = NULL, *b = NULL, *product = NULL, *ret = NULL;
    BIGNUM *remainder = NULL, *zero = NULL;
    int st = 0;

    if (!TEST_ptr(a = getBN(s, "A"))
            || !TEST_ptr(b = getBN(s, "B"))
            || !TEST_ptr(product = getBN(s, "Product"))
            || !TEST_ptr(ret = BN_new())
            || !TEST_ptr(remainder = BN_new())
            || !TEST_ptr(zero = BN_new()))
        goto err;

    BN_zero(zero);

    if (!TEST_true(BN_mul(ret, a, b, ctx))
            || !equalBN("A * B", product, ret)
            || !TEST_true(BN_div(ret, remainder, product, a, ctx))
            || !equalBN("Product / A", b, ret)
            || !equalBN("Product % A", zero, remainder)
            || !TEST_true(BN_div(ret, remainder, product, b, ctx))
            || !equalBN("Product / B", a, ret)
            || !equalBN("Product % B", zero, remainder))
        goto err;

    st = 1;
 err:
    BN_free(a);
    BN_free(b);
    BN_free(product);
    BN_free(ret);
    BN_free(remainder);
    BN_free(zero);
    return st;
}