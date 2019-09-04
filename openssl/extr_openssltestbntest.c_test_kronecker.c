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
 int /*<<< orphan*/  BN_add_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_bntest_rand (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_generate_prime_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_word (int /*<<< orphan*/ *,int) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int BN_kronecker (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_mod_exp_recp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_rshift1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_negative (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_sub_word (int /*<<< orphan*/ *,int) ; 
 int BN_ucmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int NUM0 ; 
 int /*<<< orphan*/  TEST_info (char*) ; 
 int /*<<< orphan*/  TEST_int_eq (int,int) ; 
 int /*<<< orphan*/  TEST_int_ge (int,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx ; 
 int rand_neg () ; 

__attribute__((used)) static int test_kronecker(void)
{
    BIGNUM *a = NULL, *b = NULL, *r = NULL, *t = NULL;
    int i, legendre, kronecker, st = 0;

    if (!TEST_ptr(a = BN_new())
            || !TEST_ptr(b = BN_new())
            || !TEST_ptr(r = BN_new())
            || !TEST_ptr(t = BN_new()))
        goto err;

    /*
     * We test BN_kronecker(a, b, ctx) just for b odd (Jacobi symbol). In
     * this case we know that if b is prime, then BN_kronecker(a, b, ctx) is
     * congruent to $a^{(b-1)/2}$, modulo $b$ (Legendre symbol). So we
     * generate a random prime b and compare these values for a number of
     * random a's.  (That is, we run the Solovay-Strassen primality test to
     * confirm that b is prime, except that we don't want to test whether b
     * is prime but whether BN_kronecker works.)
     */

    if (!TEST_true(BN_generate_prime_ex(b, 512, 0, NULL, NULL, NULL)))
        goto err;
    BN_set_negative(b, rand_neg());

    for (i = 0; i < NUM0; i++) {
        if (!TEST_true(BN_bntest_rand(a, 512, 0, 0)))
            goto err;
        BN_set_negative(a, rand_neg());

        /* t := (|b|-1)/2  (note that b is odd) */
        if (!TEST_true(BN_copy(t, b)))
            goto err;
        BN_set_negative(t, 0);
        if (!TEST_true(BN_sub_word(t, 1)))
            goto err;
        if (!TEST_true(BN_rshift1(t, t)))
            goto err;
        /* r := a^t mod b */
        BN_set_negative(b, 0);

        if (!TEST_true(BN_mod_exp_recp(r, a, t, b, ctx)))
            goto err;
        BN_set_negative(b, 1);

        if (BN_is_word(r, 1))
            legendre = 1;
        else if (BN_is_zero(r))
            legendre = 0;
        else {
            if (!TEST_true(BN_add_word(r, 1)))
                goto err;
            if (!TEST_int_eq(BN_ucmp(r, b), 0)) {
                TEST_info("Legendre symbol computation failed");
                goto err;
            }
            legendre = -1;
        }

        if (!TEST_int_ge(kronecker = BN_kronecker(a, b, ctx), -1))
            goto err;
        /* we actually need BN_kronecker(a, |b|) */
        if (BN_is_negative(a) && BN_is_negative(b))
            kronecker = -kronecker;

        if (!TEST_int_eq(legendre, kronecker))
            goto err;
    }

    st = 1;
 err:
    BN_free(a);
    BN_free(b);
    BN_free(r);
    BN_free(t);
    return st;
}