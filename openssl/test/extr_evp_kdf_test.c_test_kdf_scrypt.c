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
 int /*<<< orphan*/  OSSL_KDF_NAME_SCRYPT ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_PASSWORD ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SALT ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SCRYPT_MAXMEM ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SCRYPT_N ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SCRYPT_P ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SCRYPT_R ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_end () ; 
 void* OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,char*,int) ; 
 void* OSSL_PARAM_construct_uint (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_uint (int /*<<< orphan*/ *,int) ; 
 scalar_t__ TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_mem_eq (unsigned char*,int,unsigned char const*,int) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_kdfbyname (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_kdf_scrypt(void)
{
    int ret;
    EVP_KDF_CTX *kctx;
    OSSL_PARAM params[7], *p = params;
    unsigned char out[64];
    unsigned int nu = 1024, ru = 8, pu = 16, maxmem = 16;
    static const unsigned char expected[sizeof(out)] = {
        0xfd, 0xba, 0xbe, 0x1c, 0x9d, 0x34, 0x72, 0x00,
        0x78, 0x56, 0xe7, 0x19, 0x0d, 0x01, 0xe9, 0xfe,
        0x7c, 0x6a, 0xd7, 0xcb, 0xc8, 0x23, 0x78, 0x30,
        0xe7, 0x73, 0x76, 0x63, 0x4b, 0x37, 0x31, 0x62,
        0x2e, 0xaf, 0x30, 0xd9, 0x2e, 0x22, 0xa3, 0x88,
        0x6f, 0xf1, 0x09, 0x27, 0x9d, 0x98, 0x30, 0xda,
        0xc7, 0x27, 0xaf, 0xb9, 0x4a, 0x83, 0xee, 0x6d,
        0x83, 0x60, 0xcb, 0xdf, 0xa2, 0xcc, 0x06, 0x40
    };

    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_PASSWORD,
                                             (char *)"password", 8);
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_SALT,
                                             (char *)"NaCl", 4);
    *p++ = OSSL_PARAM_construct_uint(OSSL_KDF_PARAM_SCRYPT_N, &nu);
    *p++ = OSSL_PARAM_construct_uint(OSSL_KDF_PARAM_SCRYPT_R, &ru);
    *p++ = OSSL_PARAM_construct_uint(OSSL_KDF_PARAM_SCRYPT_P, &pu);
    *p++ = OSSL_PARAM_construct_uint(OSSL_KDF_PARAM_SCRYPT_MAXMEM, &maxmem);
    *p = OSSL_PARAM_construct_end();

    ret =
        TEST_ptr(kctx = get_kdfbyname(OSSL_KDF_NAME_SCRYPT))
        && TEST_true(EVP_KDF_CTX_set_params(kctx, params))
        /* failure test *//*
        && TEST_int_le(EVP_KDF_derive(kctx, out, sizeof(out)), 0)*/
        && TEST_true(OSSL_PARAM_set_uint(p - 1, 10 * 1024 * 1024))
        && TEST_true(EVP_KDF_CTX_set_params(kctx, p - 1))
        && TEST_int_gt(EVP_KDF_derive(kctx, out, sizeof(out)), 0)
        && TEST_mem_eq(out, sizeof(out), expected, sizeof(expected));

    EVP_KDF_CTX_free(kctx);
    return ret;
}