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
typedef  int /*<<< orphan*/  outputs ;
typedef  int /*<<< orphan*/  iv ;
typedef  int /*<<< orphan*/  input_key ;
typedef  int /*<<< orphan*/  constants ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_CTX_set_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_derive (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_CIPHER ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_KEY ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_MAC ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_MODE ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SALT ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SEED ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_end () ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_utf8_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_mem_eq (unsigned char*,int,unsigned char*,int) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_kdfbyname (char*) ; 

__attribute__((used)) static int test_kdf_kbkdf_6803_256(void)
{
    int ret = 0, i, p;
    EVP_KDF_CTX *kctx;
    OSSL_PARAM params[7];
    static unsigned char input_key[] = {
        0xB9, 0xD6, 0x82, 0x8B, 0x20, 0x56, 0xB7, 0xBE,
        0x65, 0x6D, 0x88, 0xA1, 0x23, 0xB1, 0xFA, 0xC6,
        0x82, 0x14, 0xAC, 0x2B, 0x72, 0x7E, 0xCF, 0x5F,
        0x69, 0xAF, 0xE0, 0xC4, 0xDF, 0x2A, 0x6D, 0x2C,
    };
    static unsigned char constants[][5] = {
        { 0x00, 0x00, 0x00, 0x02, 0x99 },
        { 0x00, 0x00, 0x00, 0x02, 0xaa },
        { 0x00, 0x00, 0x00, 0x02, 0x55 },
    };
    static unsigned char outputs[][32] = {
        {0xE4, 0x67, 0xF9, 0xA9, 0x55, 0x2B, 0xC7, 0xD3,
         0x15, 0x5A, 0x62, 0x20, 0xAF, 0x9C, 0x19, 0x22,
         0x0E, 0xEE, 0xD4, 0xFF, 0x78, 0xB0, 0xD1, 0xE6,
         0xA1, 0x54, 0x49, 0x91, 0x46, 0x1A, 0x9E, 0x50,
        },
        {0x41, 0x2A, 0xEF, 0xC3, 0x62, 0xA7, 0x28, 0x5F,
         0xC3, 0x96, 0x6C, 0x6A, 0x51, 0x81, 0xE7, 0x60,
         0x5A, 0xE6, 0x75, 0x23, 0x5B, 0x6D, 0x54, 0x9F,
         0xBF, 0xC9, 0xAB, 0x66, 0x30, 0xA4, 0xC6, 0x04,
        },
        {0xFA, 0x62, 0x4F, 0xA0, 0xE5, 0x23, 0x99, 0x3F,
         0xA3, 0x88, 0xAE, 0xFD, 0xC6, 0x7E, 0x67, 0xEB,
         0xCD, 0x8C, 0x08, 0xE8, 0xA0, 0x24, 0x6B, 0x1D,
         0x73, 0xB0, 0xD1, 0xDD, 0x9F, 0xC5, 0x82, 0xB0,
        },
    };
    static unsigned char iv[16] = { 0 };
    unsigned char result[32] = { 0 };

    for (i = 0; i < 3; i++) {
        p = 0;
        params[p++] = OSSL_PARAM_construct_utf8_string(
            OSSL_KDF_PARAM_CIPHER, "CAMELLIA-256-CBC", 0);
        params[p++] = OSSL_PARAM_construct_utf8_string(
            OSSL_KDF_PARAM_MAC, "CMAC", 0);
        params[p++] = OSSL_PARAM_construct_utf8_string(
            OSSL_KDF_PARAM_MODE, "FEEDBACK", 0);
        params[p++] = OSSL_PARAM_construct_octet_string(
            OSSL_KDF_PARAM_KEY, input_key, sizeof(input_key));
        params[p++] = OSSL_PARAM_construct_octet_string(
            OSSL_KDF_PARAM_SALT, constants[i], sizeof(constants[i]));
        params[p++] = OSSL_PARAM_construct_octet_string(
            OSSL_KDF_PARAM_SEED, iv, sizeof(iv));
        params[p] = OSSL_PARAM_construct_end();

        kctx = get_kdfbyname("KBKDF");
        ret = TEST_ptr(kctx)
            && TEST_true(EVP_KDF_CTX_set_params(kctx, params))
            && TEST_int_gt(EVP_KDF_derive(kctx, result, sizeof(result)), 0)
            && TEST_mem_eq(result, sizeof(result), outputs[i],
                           sizeof(outputs[i]));
        EVP_KDF_CTX_free(kctx);
        if (ret != 1)
            return ret;
    }

    return ret;
}