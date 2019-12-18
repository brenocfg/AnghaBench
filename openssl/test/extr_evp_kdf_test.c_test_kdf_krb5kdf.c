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
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  expected ;
typedef  int /*<<< orphan*/  constant ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_CTX_set_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_derive (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  OSSL_KDF_NAME_KRB5KDF ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_CIPHER ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_CONSTANT ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_KEY ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_end () ; 
 void* OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_utf8_string (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_mem_eq (unsigned char*,int,unsigned char const*,int) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_kdfbyname (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_kdf_krb5kdf(void)
{
    int ret;
    EVP_KDF_CTX *kctx;
    OSSL_PARAM params[4], *p = params;
    unsigned char out[16];
    static unsigned char key[] = {
        0x42, 0x26, 0x3C, 0x6E, 0x89, 0xF4, 0xFC, 0x28,
        0xB8, 0xDF, 0x68, 0xEE, 0x09, 0x79, 0x9F, 0x15
    };
    static unsigned char constant[] = {
        0x00, 0x00, 0x00, 0x02, 0x99
    };
    static const unsigned char expected[sizeof(out)] = {
        0x34, 0x28, 0x0A, 0x38, 0x2B, 0xC9, 0x27, 0x69,
        0xB2, 0xDA, 0x2F, 0x9E, 0xF0, 0x66, 0x85, 0x4B
    };

    *p++ = OSSL_PARAM_construct_utf8_string(OSSL_KDF_PARAM_CIPHER,
                                            (char *)"AES-128-CBC",
                                            sizeof("AES-128-CBC"));
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_KEY, key,
                                             sizeof(key));
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_CONSTANT,
                                             constant, sizeof(constant));
    *p = OSSL_PARAM_construct_end();

    ret =
        TEST_ptr(kctx = get_kdfbyname(OSSL_KDF_NAME_KRB5KDF))
        && TEST_true(EVP_KDF_CTX_set_params(kctx, params))
        && TEST_int_gt(EVP_KDF_derive(kctx, out, sizeof(out)), 0)
        && TEST_mem_eq(out, sizeof(out), expected, sizeof(expected));

    EVP_KDF_CTX_free(kctx);
    return ret;
}