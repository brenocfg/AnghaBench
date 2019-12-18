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
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RSA_new () ; 
 int /*<<< orphan*/  RSA_set0_factors (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_set0_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_false (int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsa_check_private_exponent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_check_private_exponent(void)
{
    int ret = 0;
    RSA *key = NULL;
    BN_CTX *ctx = NULL;
    BIGNUM *p = NULL, *q = NULL, *e = NULL, *d = NULL, *n = NULL;

    ret = TEST_ptr(key = RSA_new())
          && TEST_ptr(ctx = BN_CTX_new())
          && TEST_ptr(p = BN_new())
          && TEST_ptr(q = BN_new())
          /* lcm(15-1,17-1) = 14*16 / 2 = 112 */
          && TEST_true(BN_set_word(p, 15))
          && TEST_true(BN_set_word(q, 17))
          && TEST_true(RSA_set0_factors(key, p, q));
    if (!ret) {
        BN_free(p);
        BN_free(q);
        goto end;
    }

    ret = TEST_ptr(e = BN_new())
          && TEST_ptr(d = BN_new())
          && TEST_ptr(n = BN_new())
          && TEST_true(BN_set_word(e, 5))
          && TEST_true(BN_set_word(d, 157))
          && TEST_true(BN_set_word(n, 15*17))
          && TEST_true(RSA_set0_key(key, n, e, d));
    if (!ret) {
        BN_free(e);
        BN_free(d);
        BN_free(n);
        goto end;
    }
    /* fails since d >= lcm(p-1, q-1) */
    ret = TEST_false(rsa_check_private_exponent(key, 8, ctx))
          && TEST_true(BN_set_word(d, 45))
          /* d is correct size and 1 = e.d mod lcm(p-1, q-1) */
          && TEST_true(rsa_check_private_exponent(key, 8, ctx))
          /* d is too small compared to nbits */
          && TEST_false(rsa_check_private_exponent(key, 16, ctx))
          /* d is too small compared to nbits */
          && TEST_true(BN_set_word(d, 16))
          && TEST_false(rsa_check_private_exponent(key, 8, ctx))
          /* fail if 1 != e.d mod lcm(p-1, q-1) */
          && TEST_true(BN_set_word(d, 46))
          && TEST_false(rsa_check_private_exponent(key, 8, ctx));
end:
    RSA_free(key);
    BN_CTX_free(ctx);
    return ret;
}