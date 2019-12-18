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
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_rand (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  TEST_BN_eq_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_eq_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_rand(void)
{
    BIGNUM *bn = NULL;
    int st = 0;

    if (!TEST_ptr(bn = BN_new()))
        return 0;

    /* Test BN_rand for degenerate cases with |top| and |bottom| parameters. */
    if (!TEST_false(BN_rand(bn, 0, 0 /* top */ , 0 /* bottom */ ))
            || !TEST_false(BN_rand(bn, 0, 1 /* top */ , 1 /* bottom */ ))
            || !TEST_true(BN_rand(bn, 1, 0 /* top */ , 0 /* bottom */ ))
            || !TEST_BN_eq_one(bn)
            || !TEST_false(BN_rand(bn, 1, 1 /* top */ , 0 /* bottom */ ))
            || !TEST_true(BN_rand(bn, 1, -1 /* top */ , 1 /* bottom */ ))
            || !TEST_BN_eq_one(bn)
            || !TEST_true(BN_rand(bn, 2, 1 /* top */ , 0 /* bottom */ ))
            || !TEST_BN_eq_word(bn, 3))
        goto err;

    st = 1;
 err:
    BN_free(bn);
    return st;
}