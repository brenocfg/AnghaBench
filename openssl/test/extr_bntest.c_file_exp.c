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
 int /*<<< orphan*/  BN_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  equalBN (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getBN (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int file_exp(STANZA *s)
{
    BIGNUM *a = NULL, *e = NULL, *exp = NULL, *ret = NULL;
    int st = 0;

    if (!TEST_ptr(a = getBN(s, "A"))
            || !TEST_ptr(e = getBN(s, "E"))
            || !TEST_ptr(exp = getBN(s, "Exp"))
            || !TEST_ptr(ret = BN_new()))
        goto err;

    if (!TEST_true(BN_exp(ret, a, e, ctx))
            || !equalBN("A ^ E", exp, ret))
        goto err;

    st = 1;
 err:
    BN_free(a);
    BN_free(e);
    BN_free(exp);
    BN_free(ret);
    return st;
}