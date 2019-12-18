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
typedef  int /*<<< orphan*/  len ;
typedef  int /*<<< orphan*/  expected ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_ITER ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_PBKDF2_PKCS5_MODE ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SALT ; 
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_CTX_set_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  EVP_KDF_derive (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  OSSL_KDF_NAME_PBKDF2 ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_DIGEST ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_ITER ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_PASSWORD ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_PKCS5 ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SALT ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_end () ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_int (int /*<<< orphan*/ ,int*) ; 
 void* OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_uint (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_utf8_string (int /*<<< orphan*/ ,char*,int) ; 
 size_t SIZE_MAX ; 
 scalar_t__ TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,int,unsigned char const*,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_kdfbyname (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_kdf_pbkdf2(void)
{
    int ret = 0;
    EVP_KDF_CTX *kctx;
    unsigned char out[25];
    size_t len = 0;
    unsigned int iterations = 4096;
    int mode = 0;
    OSSL_PARAM params[6], *p = params;
    const unsigned char expected[sizeof(out)] = {
        0x34, 0x8c, 0x89, 0xdb, 0xcb, 0xd3, 0x2b, 0x2f,
        0x32, 0xd8, 0x14, 0xb8, 0x11, 0x6e, 0x84, 0xcf,
        0x2b, 0x17, 0x34, 0x7e, 0xbc, 0x18, 0x00, 0x18,
        0x1c
    };

    if (sizeof(len) > 32)
        len = SIZE_MAX;

    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_PASSWORD,
                                             (unsigned char *)
                                                "passwordPASSWORDpassword", 24);
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_SALT,
                                             (unsigned char *)
                                                "saltSALTsaltSALTsaltSALTsaltSALTsalt",
                                                36);
    *p++ = OSSL_PARAM_construct_uint(OSSL_KDF_PARAM_ITER, &iterations);
    *p++ = OSSL_PARAM_construct_utf8_string(OSSL_KDF_PARAM_DIGEST,
                                             (char *)"sha256", 7);
    *p++ = OSSL_PARAM_construct_int(OSSL_KDF_PARAM_PKCS5, &mode);
    *p = OSSL_PARAM_construct_end();

    if (!TEST_ptr(kctx = get_kdfbyname(OSSL_KDF_NAME_PBKDF2))
        || !TEST_true(EVP_KDF_CTX_set_params(kctx, params))
        || !TEST_int_gt(EVP_KDF_derive(kctx, out, sizeof(out)), 0)
        || !TEST_mem_eq(out, sizeof(out), expected, sizeof(expected))
        || !TEST_true(EVP_KDF_CTX_set_params(kctx, params))
        /* A key length that is too small should fail */
        || !TEST_int_eq(EVP_KDF_derive(kctx, out, 112 / 8 - 1), 0)
        /* A key length that is too large should fail */
        || (len != 0 && !TEST_int_eq(EVP_KDF_derive(kctx, out, len), 0)))
        goto err;
#if 0
/* TODO */
          /* Salt length less than 128 bits should fail */
          || TEST_int_eq(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_SALT,
                                      "123456781234567",
                                      (size_t)15), 0)
          /* A small iteration count should fail */
          || TEST_int_eq(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_ITER, 1), 0)
          || TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_PBKDF2_PKCS5_MODE,
                                      1), 0)
          /* Small salts will pass if the "pkcs5" mode is enabled */
          || TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_SALT,
                                      "123456781234567",
                                      (size_t)15), 0)
          /* A small iteration count will pass if "pkcs5" mode is enabled */
          || TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_ITER, 1), 0)
          /*
           * If the "pkcs5" mode is disabled then the small salt and iter will
           * fail when the derive gets called.
           */
          || TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_PBKDF2_PKCS5_MODE,
                                      0), 0)
          || TEST_int_eq(EVP_KDF_derive(kctx, out, sizeof(out)), 0);
#endif
    ret = 1;
err:
    EVP_KDF_CTX_free(kctx);
    return ret;
}