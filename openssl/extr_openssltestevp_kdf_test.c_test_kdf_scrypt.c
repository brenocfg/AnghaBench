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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  expected ;
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_MAXMEM_BYTES ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_PASS ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SALT ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SCRYPT_N ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SCRYPT_P ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SCRYPT_R ; 
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_KDF_CTX_new_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_KDF_SCRYPT ; 
 int /*<<< orphan*/  EVP_KDF_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  EVP_KDF_derive (int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_int_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_mem_eq (unsigned char*,int,unsigned char const*,int) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_kdf_scrypt(void)
{
    int ret;
    EVP_KDF_CTX *kctx;
    unsigned char out[64];
    const unsigned char expected[sizeof(out)] = {
        0xfd, 0xba, 0xbe, 0x1c, 0x9d, 0x34, 0x72, 0x00,
        0x78, 0x56, 0xe7, 0x19, 0x0d, 0x01, 0xe9, 0xfe,
        0x7c, 0x6a, 0xd7, 0xcb, 0xc8, 0x23, 0x78, 0x30,
        0xe7, 0x73, 0x76, 0x63, 0x4b, 0x37, 0x31, 0x62,
        0x2e, 0xaf, 0x30, 0xd9, 0x2e, 0x22, 0xa3, 0x88,
        0x6f, 0xf1, 0x09, 0x27, 0x9d, 0x98, 0x30, 0xda,
        0xc7, 0x27, 0xaf, 0xb9, 0x4a, 0x83, 0xee, 0x6d,
        0x83, 0x60, 0xcb, 0xdf, 0xa2, 0xcc, 0x06, 0x40
    };

    ret =
        TEST_ptr(kctx = EVP_KDF_CTX_new_id(EVP_KDF_SCRYPT))
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_PASS, "password",
                                    (size_t)8), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_SALT, "NaCl",
                                    (size_t)4), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_SCRYPT_N,
                                    (uint64_t)1024), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_SCRYPT_R,
                                    (uint32_t)8), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_SCRYPT_P,
                                    (uint32_t)16), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_MAXMEM_BYTES,
                                    (uint64_t)16), 0)
        /* failure test */
        && TEST_int_le(EVP_KDF_derive(kctx, out, sizeof(out)), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_MAXMEM_BYTES,
                                    (uint64_t)(10 * 1024 * 1024)), 0)
        && TEST_int_gt(EVP_KDF_derive(kctx, out, sizeof(out)), 0)
        && TEST_mem_eq(out, sizeof(out), expected, sizeof(expected));

    EVP_KDF_CTX_free(kctx);
    return ret;
}