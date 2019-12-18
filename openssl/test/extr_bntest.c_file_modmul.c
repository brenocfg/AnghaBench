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
typedef  int /*<<< orphan*/  BN_MONT_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_MONT_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_MONT_CTX_new () ; 
 int /*<<< orphan*/  BN_MONT_CTX_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_from_montgomery (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ BN_is_odd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_mod_mul_montgomery (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_nnmod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_to_montgomery (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  equalBN (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getBN (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int file_modmul(STANZA *s)
{
    BIGNUM *a = NULL, *b = NULL, *m = NULL, *mod_mul = NULL, *ret = NULL;
    int st = 0;

    if (!TEST_ptr(a = getBN(s, "A"))
            || !TEST_ptr(b = getBN(s, "B"))
            || !TEST_ptr(m = getBN(s, "M"))
            || !TEST_ptr(mod_mul = getBN(s, "ModMul"))
            || !TEST_ptr(ret = BN_new()))
        goto err;

    if (!TEST_true(BN_mod_mul(ret, a, b, m, ctx))
            || !equalBN("A * B (mod M)", mod_mul, ret))
        goto err;

    if (BN_is_odd(m)) {
        /* Reduce |a| and |b| and test the Montgomery version. */
        BN_MONT_CTX *mont = BN_MONT_CTX_new();
        BIGNUM *a_tmp = BN_new();
        BIGNUM *b_tmp = BN_new();

        if (mont == NULL || a_tmp == NULL || b_tmp == NULL
                || !TEST_true(BN_MONT_CTX_set(mont, m, ctx))
                || !TEST_true(BN_nnmod(a_tmp, a, m, ctx))
                || !TEST_true(BN_nnmod(b_tmp, b, m, ctx))
                || !TEST_true(BN_to_montgomery(a_tmp, a_tmp, mont, ctx))
                || !TEST_true(BN_to_montgomery(b_tmp, b_tmp, mont, ctx))
                || !TEST_true(BN_mod_mul_montgomery(ret, a_tmp, b_tmp,
                                                    mont, ctx))
                || !TEST_true(BN_from_montgomery(ret, ret, mont, ctx))
                || !equalBN("A * B (mod M) (mont)", mod_mul, ret))
            st = 0;
        else
            st = 1;
        BN_MONT_CTX_free(mont);
        BN_free(a_tmp);
        BN_free(b_tmp);
        if (st == 0)
            goto err;
    }

    st = 1;
 err:
    BN_free(a);
    BN_free(b);
    BN_free(m);
    BN_free(mod_mul);
    BN_free(ret);
    return st;
}