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
 int /*<<< orphan*/  BN_GF2m_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_GF2m_arr2poly (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_GF2m_mod_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_bntest_rand (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int NUM0 ; 
 scalar_t__ TEST_BN_eq_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  p0 ; 
 int /*<<< orphan*/  p1 ; 

__attribute__((used)) static int test_gf2m_mul(void)
{
    BIGNUM *a, *b[2] = {NULL, NULL}, *c = NULL, *d = NULL;
    BIGNUM *e = NULL, *f = NULL, *g = NULL, *h = NULL;
    int i, j, st = 0;

    if (!TEST_ptr(a = BN_new())
            || !TEST_ptr(b[0] = BN_new())
            || !TEST_ptr(b[1] = BN_new())
            || !TEST_ptr(c = BN_new())
            || !TEST_ptr(d = BN_new())
            || !TEST_ptr(e = BN_new())
            || !TEST_ptr(f = BN_new())
            || !TEST_ptr(g = BN_new())
            || !TEST_ptr(h = BN_new()))
        goto err;

    if (!(TEST_true(BN_GF2m_arr2poly(p0, b[0]))
            && TEST_true(BN_GF2m_arr2poly(p1, b[1]))))
        goto err;

    for (i = 0; i < NUM0; i++) {
        if (!(TEST_true(BN_bntest_rand(a, 1024, 0, 0))
                && TEST_true(BN_bntest_rand(c, 1024, 0, 0))
                && TEST_true(BN_bntest_rand(d, 1024, 0, 0))))
            goto err;
        for (j = 0; j < 2; j++) {
            if (!(TEST_true(BN_GF2m_mod_mul(e, a, c, b[j], ctx))
                    && TEST_true(BN_GF2m_add(f, a, d))
                    && TEST_true(BN_GF2m_mod_mul(g, f, c, b[j], ctx))
                    && TEST_true(BN_GF2m_mod_mul(h, d, c, b[j], ctx))
                    && TEST_true(BN_GF2m_add(f, e, g))
                    && TEST_true(BN_GF2m_add(f, f, h))
                    /* Test that (a+d)*c = a*c + d*c. */
                    && TEST_BN_eq_zero(f)))
                goto err;
        }
    }
    st = 1;

 err:
    BN_free(a);
    BN_free(b[0]);
    BN_free(b[1]);
    BN_free(c);
    BN_free(d);
    BN_free(e);
    BN_free(f);
    BN_free(g);
    BN_free(h);
    return st;
}