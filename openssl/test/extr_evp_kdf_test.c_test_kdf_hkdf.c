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
typedef  int /*<<< orphan*/  expected ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_CTX_set_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_derive (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  OSSL_KDF_NAME_HKDF ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_DIGEST ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_INFO ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_KEY ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SALT ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_end () ; 
 void* OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_utf8_string (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_mem_eq (unsigned char*,int,unsigned char const*,int) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_kdfbyname (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_kdf_hkdf(void)
{
    int ret;
    EVP_KDF_CTX *kctx;
    unsigned char out[10];
    OSSL_PARAM params[5], *p = params;
    static const unsigned char expected[sizeof(out)] = {
        0x2a, 0xc4, 0x36, 0x9f, 0x52, 0x59, 0x96, 0xf8, 0xde, 0x13
    };

    *p++ = OSSL_PARAM_construct_utf8_string(OSSL_KDF_PARAM_DIGEST,
                                            (char *)"sha256", sizeof("sha256"));
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_SALT,
                                             (unsigned char *)"salt", 4);
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_KEY,
                                             (unsigned char *)"secret", 6);
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_INFO,
                                             (unsigned char *)"label", 5);
    *p = OSSL_PARAM_construct_end();

    ret =
        TEST_ptr(kctx = get_kdfbyname(OSSL_KDF_NAME_HKDF))
        && TEST_true(EVP_KDF_CTX_set_params(kctx, params))
        && TEST_int_gt(EVP_KDF_derive(kctx, out, sizeof(out)), 0)
        && TEST_mem_eq(out, sizeof(out), expected, sizeof(expected));

    EVP_KDF_CTX_free(kctx);
    return ret;
}