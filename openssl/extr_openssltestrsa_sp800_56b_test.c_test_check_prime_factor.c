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
typedef  int /*<<< orphan*/  p3 ;
typedef  int /*<<< orphan*/  p2 ;
typedef  int /*<<< orphan*/  p1 ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int) ; 
 scalar_t__ TEST_false (int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bn_load_new (unsigned char const*,int) ; 
 int /*<<< orphan*/  rsa_check_prime_factor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_check_prime_factor(void)
{
    int ret = 0;
    BN_CTX *ctx = NULL;
    BIGNUM *p = NULL, *e = NULL;
    BIGNUM *bn_p1 = NULL, *bn_p2 = NULL, *bn_p3 = NULL;

    /* Some range checks that are larger than 32 bits */
    static const unsigned char p1[] = { 0x0B, 0x50, 0x4f, 0x33, 0x73 };
    static const unsigned char p2[] = { 0x0B, 0x50, 0x4f, 0x33, 0x75 };
    static const unsigned char p3[] = { 0x0F, 0x50, 0x00, 0x03, 0x75 };

    ret = TEST_ptr(p = BN_new())
          && TEST_ptr(bn_p1 = bn_load_new(p1, sizeof(p1)))
          && TEST_ptr(bn_p2 = bn_load_new(p2, sizeof(p2)))
          && TEST_ptr(bn_p3 = bn_load_new(p3, sizeof(p3)))
          && TEST_ptr(e = BN_new())
          && TEST_ptr(ctx = BN_CTX_new())
          /* Fails the prime test */
          && TEST_true(BN_set_word(e, 0x1))
          && TEST_false(rsa_check_prime_factor(bn_p1, e, 72, ctx))
          /* p is prime and in range and gcd(p-1, e) = 1 */
          && TEST_true(rsa_check_prime_factor(bn_p2, e, 72, ctx))
          /* gcd(p-1,e) = 1 test fails */
          && TEST_true(BN_set_word(e, 0x2))
          && TEST_false(rsa_check_prime_factor(p, e, 72, ctx))
          /* p fails the range check */
          && TEST_true(BN_set_word(e, 0x1))
          && TEST_false(rsa_check_prime_factor(bn_p3, e, 72, ctx));

    BN_free(bn_p3);
    BN_free(bn_p2);
    BN_free(bn_p1);
    BN_free(e);
    BN_free(p);
    BN_CTX_free(ctx);
    return ret;
}