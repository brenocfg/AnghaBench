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
typedef  int /*<<< orphan*/  result ;
typedef  int /*<<< orphan*/  output ;
typedef  int /*<<< orphan*/  input_key ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_CTX_set_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_derive (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_DIGEST ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_INFO ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_KEY ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_MAC ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SALT ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_end () ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_utf8_string (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_mem_eq (unsigned char*,int,unsigned char*,int) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_kdfbyname (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int test_kdf_kbkdf_8009_prf1(void)
{
    int ret, i = 0;
    EVP_KDF_CTX *kctx;
    OSSL_PARAM params[6];
    char *label = "prf", *digest = "sha256", *prf_input = "test",
        *mac = "HMAC";
    static unsigned char input_key[] = {
        0x37, 0x05, 0xD9, 0x60, 0x80, 0xC1, 0x77, 0x28,
        0xA0, 0xE8, 0x00, 0xEA, 0xB6, 0xE0, 0xD2, 0x3C,
    };
    static unsigned char output[] = {
        0x9D, 0x18, 0x86, 0x16, 0xF6, 0x38, 0x52, 0xFE,
        0x86, 0x91, 0x5B, 0xB8, 0x40, 0xB4, 0xA8, 0x86,
        0xFF, 0x3E, 0x6B, 0xB0, 0xF8, 0x19, 0xB4, 0x9B,
        0x89, 0x33, 0x93, 0xD3, 0x93, 0x85, 0x42, 0x95,
    };
    unsigned char result[sizeof(output)] = { 0 };

    params[i++] = OSSL_PARAM_construct_utf8_string(
        OSSL_KDF_PARAM_DIGEST, digest, strlen(digest) + 1);
    params[i++] = OSSL_PARAM_construct_utf8_string(
        OSSL_KDF_PARAM_MAC, mac, strlen(mac) + 1);
    params[i++] = OSSL_PARAM_construct_octet_string(
        OSSL_KDF_PARAM_KEY, input_key, sizeof(input_key));
    params[i++] = OSSL_PARAM_construct_octet_string(
        OSSL_KDF_PARAM_SALT, label, strlen(label));
    params[i++] = OSSL_PARAM_construct_octet_string(
        OSSL_KDF_PARAM_INFO, prf_input, strlen(prf_input));
    params[i] = OSSL_PARAM_construct_end();

    kctx = get_kdfbyname("KBKDF");
    ret = TEST_ptr(kctx)
        && TEST_true(EVP_KDF_CTX_set_params(kctx, params))
        && TEST_int_gt(EVP_KDF_derive(kctx, result, sizeof(result)), 0)
        && TEST_mem_eq(result, sizeof(result), output, sizeof(output));

    EVP_KDF_CTX_free(kctx);
    return ret;
}