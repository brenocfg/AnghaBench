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

__attribute__((used)) static int test_kdf_kbkdf_8009_prf2(void)
{
    int ret, i = 0;
    EVP_KDF_CTX *kctx;
    OSSL_PARAM params[6];
    char *label = "prf", *digest = "sha384", *prf_input = "test",
        *mac = "HMAC";
    static unsigned char input_key[] = {
        0x6D, 0x40, 0x4D, 0x37, 0xFA, 0xF7, 0x9F, 0x9D,
        0xF0, 0xD3, 0x35, 0x68, 0xD3, 0x20, 0x66, 0x98,
        0x00, 0xEB, 0x48, 0x36, 0x47, 0x2E, 0xA8, 0xA0,
        0x26, 0xD1, 0x6B, 0x71, 0x82, 0x46, 0x0C, 0x52,
    };
    static unsigned char output[] = {
        0x98, 0x01, 0xF6, 0x9A, 0x36, 0x8C, 0x2B, 0xF6,
        0x75, 0xE5, 0x95, 0x21, 0xE1, 0x77, 0xD9, 0xA0,
        0x7F, 0x67, 0xEF, 0xE1, 0xCF, 0xDE, 0x8D, 0x3C,
        0x8D, 0x6F, 0x6A, 0x02, 0x56, 0xE3, 0xB1, 0x7D,
        0xB3, 0xC1, 0xB6, 0x2A, 0xD1, 0xB8, 0x55, 0x33,
        0x60, 0xD1, 0x73, 0x67, 0xEB, 0x15, 0x14, 0xD2,
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