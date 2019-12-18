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

/* Variables and functions */
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_meth_add0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_meth_new (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_meth_set_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_meth_set_param_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_meth_set_public_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  custom_pmeth ; 
 int /*<<< orphan*/  ec_der_pub_keys ; 
 int /*<<< orphan*/  keycheckdata ; 
 int /*<<< orphan*/  keydata ; 
 int /*<<< orphan*/  keys ; 
 int /*<<< orphan*/  pkey_custom_check ; 
 int /*<<< orphan*/  pkey_custom_param_check ; 
 int /*<<< orphan*/  pkey_custom_pub_check ; 
 int /*<<< orphan*/  test_EVP_DigestSignInit ; 
 int /*<<< orphan*/  test_EVP_DigestVerifyInit ; 
 int /*<<< orphan*/  test_EVP_Enveloped ; 
 int /*<<< orphan*/  test_EVP_PKCS82PKEY ; 
 int /*<<< orphan*/  test_EVP_PKEY_CTX_get_set_params ; 
 int /*<<< orphan*/  test_EVP_PKEY_check ; 
 int /*<<< orphan*/  test_EVP_SM2 ; 
 int /*<<< orphan*/  test_EVP_SM2_verify ; 
 int /*<<< orphan*/  test_HKDF ; 
 int /*<<< orphan*/  test_X509_PUBKEY_inplace ; 
 int /*<<< orphan*/  test_d2i_AutoPrivateKey ; 
 int /*<<< orphan*/  test_invalide_ec_char2_pub_range_decode ; 
 int /*<<< orphan*/  test_set_get_raw_keys ; 

int setup_tests(void)
{
    ADD_ALL_TESTS(test_EVP_DigestSignInit, 4);
    ADD_TEST(test_EVP_DigestVerifyInit);
    ADD_TEST(test_EVP_Enveloped);
    ADD_ALL_TESTS(test_d2i_AutoPrivateKey, OSSL_NELEM(keydata));
#ifndef OPENSSL_NO_EC
    ADD_TEST(test_EVP_PKCS82PKEY);
#endif
#if !defined(OPENSSL_NO_SM2) && !defined(FIPS_MODE)
    ADD_TEST(test_EVP_SM2);
    ADD_TEST(test_EVP_SM2_verify);
#endif
    ADD_ALL_TESTS(test_set_get_raw_keys, OSSL_NELEM(keys));
    custom_pmeth = EVP_PKEY_meth_new(0xdefaced, 0);
    if (!TEST_ptr(custom_pmeth))
        return 0;
    EVP_PKEY_meth_set_check(custom_pmeth, pkey_custom_check);
    EVP_PKEY_meth_set_public_check(custom_pmeth, pkey_custom_pub_check);
    EVP_PKEY_meth_set_param_check(custom_pmeth, pkey_custom_param_check);
    if (!TEST_int_eq(EVP_PKEY_meth_add0(custom_pmeth), 1))
        return 0;
    ADD_ALL_TESTS(test_EVP_PKEY_check, OSSL_NELEM(keycheckdata));
    ADD_TEST(test_HKDF);
#ifndef OPENSSL_NO_EC
    ADD_TEST(test_X509_PUBKEY_inplace);
    ADD_ALL_TESTS(test_invalide_ec_char2_pub_range_decode,
                  OSSL_NELEM(ec_der_pub_keys));
#endif
#ifndef OPENSSL_NO_DSA
    ADD_TEST(test_EVP_PKEY_CTX_get_set_params);
#endif
    return 1;
}