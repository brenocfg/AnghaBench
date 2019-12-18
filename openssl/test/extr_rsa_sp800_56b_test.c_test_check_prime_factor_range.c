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
typedef  int /*<<< orphan*/  p4 ;
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
 int /*<<< orphan*/  rsa_check_prime_factor_range (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_check_prime_factor_range(void)
{
    int ret = 0;
    BN_CTX *ctx = NULL;
    BIGNUM *p = NULL;
    BIGNUM *bn_p1 = NULL, *bn_p2 = NULL, *bn_p3 = NULL, *bn_p4 = NULL;
    /* Some range checks that are larger than 32 bits */
    static const unsigned char p1[] = { 0x0B, 0x50, 0x4F, 0x33, 0x3F };
    static const unsigned char p2[] = { 0x10, 0x00, 0x00, 0x00, 0x00 };
    static const unsigned char p3[] = { 0x0B, 0x50, 0x4F, 0x33, 0x40 };
    static const unsigned char p4[] = { 0x0F, 0xFF, 0xFF, 0xFF, 0xFF };

    /* (√2)(2^(nbits/2 - 1) <= p <= 2^(nbits/2) - 1
     * For 8 bits:   0xB.504F <= p <= 0xF
     * for 72 bits:  0xB504F333F. <= p <= 0xF_FFFF_FFFF
     */
    ret = TEST_ptr(p = BN_new())
          && TEST_ptr(bn_p1 = bn_load_new(p1, sizeof(p1)))
          && TEST_ptr(bn_p2 = bn_load_new(p2, sizeof(p2)))
          && TEST_ptr(bn_p3 = bn_load_new(p3, sizeof(p3)))
          && TEST_ptr(bn_p4 = bn_load_new(p4, sizeof(p4)))
          && TEST_ptr(ctx = BN_CTX_new())
          && TEST_true(BN_set_word(p, 0xA))
          && TEST_false(rsa_check_prime_factor_range(p, 8, ctx))
          && TEST_true(BN_set_word(p, 0x10))
          && TEST_false(rsa_check_prime_factor_range(p, 8, ctx))
          && TEST_true(BN_set_word(p, 0xB))
          && TEST_false(rsa_check_prime_factor_range(p, 8, ctx))
          && TEST_true(BN_set_word(p, 0xC))
          && TEST_true(rsa_check_prime_factor_range(p, 8, ctx))
          && TEST_true(BN_set_word(p, 0xF))
          && TEST_true(rsa_check_prime_factor_range(p, 8, ctx))
          && TEST_false(rsa_check_prime_factor_range(bn_p1, 72, ctx))
          && TEST_false(rsa_check_prime_factor_range(bn_p2, 72, ctx))
          && TEST_true(rsa_check_prime_factor_range(bn_p3, 72, ctx))
          && TEST_true(rsa_check_prime_factor_range(bn_p4, 72, ctx));

    BN_free(bn_p4);
    BN_free(bn_p3);
    BN_free(bn_p2);
    BN_free(bn_p1);
    BN_free(p);
    BN_CTX_free(ctx);
    return ret;
}