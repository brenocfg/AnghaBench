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
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_rshift (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_rshift1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  equalBN (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getBN (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  getint (int /*<<< orphan*/ *,int*,char*) ; 

__attribute__((used)) static int file_rshift(STANZA *s)
{
    BIGNUM *a = NULL, *rshift = NULL, *ret = NULL;
    int n = 0, st = 0;

    if (!TEST_ptr(a = getBN(s, "A"))
            || !TEST_ptr(rshift = getBN(s, "RShift"))
            || !TEST_ptr(ret = BN_new())
            || !getint(s, &n, "N"))
        goto err;

    if (!TEST_true(BN_rshift(ret, a, n))
            || !equalBN("A >> N", rshift, ret))
        goto err;

    /* If N == 1, try with rshift1 as well */
    if (n == 1) {
        if (!TEST_true(BN_rshift1(ret, a))
                || !equalBN("A >> 1 (rshift1)", rshift, ret))
            goto err;
    }
    st = 1;

 err:
    BN_free(a);
    BN_free(rshift);
    BN_free(ret);
    return st;
}