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
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_ITER ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_MD ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_PASS ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SALT ; 
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_KDF_CTX_new_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_KDF_PBKDF2 ; 
 int /*<<< orphan*/  EVP_KDF_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  EVP_KDF_derive (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int EVP_sha256 () ; 
 scalar_t__ TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_mem_eq (unsigned char*,int,unsigned char const*,int) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_kdf_pbkdf2(void)
{
    int ret;
    EVP_KDF_CTX *kctx;
    unsigned char out[32];
    const unsigned char expected[sizeof(out)] = {
        0xae, 0x4d, 0x0c, 0x95, 0xaf, 0x6b, 0x46, 0xd3,
        0x2d, 0x0a, 0xdf, 0xf9, 0x28, 0xf0, 0x6d, 0xd0,
        0x2a, 0x30, 0x3f, 0x8e, 0xf3, 0xc2, 0x51, 0xdf,
        0xd6, 0xe2, 0xd8, 0x5a, 0x95, 0x47, 0x4c, 0x43
    };

    ret =
        TEST_ptr(kctx = EVP_KDF_CTX_new_id(EVP_KDF_PBKDF2))
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_PASS, "password",
                                    (size_t)8), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_SALT, "salt",
                                    (size_t)4), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_ITER, 2), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_MD, EVP_sha256()), 0)
        && TEST_int_gt(EVP_KDF_derive(kctx, out, sizeof(out)), 0)
        && TEST_mem_eq(out, sizeof(out), expected, sizeof(expected));

    EVP_KDF_CTX_free(kctx);
    return ret;
}