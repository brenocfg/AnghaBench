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
 int /*<<< orphan*/  EVP_KDF_CTRL_ADD_HKDF_INFO ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_KEY ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_MD ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SALT ; 
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_KDF_CTX_new_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_KDF_HKDF ; 
 int /*<<< orphan*/  EVP_KDF_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  EVP_KDF_derive (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 scalar_t__ TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_mem_eq (unsigned char*,int,unsigned char const*,int) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_kdf_hkdf(void)
{
    int ret;
    EVP_KDF_CTX *kctx;
    unsigned char out[10];
    const unsigned char expected[sizeof(out)] = {
        0x2a, 0xc4, 0x36, 0x9f, 0x52, 0x59, 0x96, 0xf8, 0xde, 0x13
    };

    ret =
        TEST_ptr(kctx = EVP_KDF_CTX_new_id(EVP_KDF_HKDF))
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_MD, EVP_sha256()), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_SALT, "salt",
                                    (size_t)4), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_KEY, "secret",
                                    (size_t)6), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_ADD_HKDF_INFO, "label",
                                    (size_t)5), 0)
        && TEST_int_gt(EVP_KDF_derive(kctx, out, sizeof(out)), 0)
        && TEST_mem_eq(out, sizeof(out), expected, sizeof(expected));

    EVP_KDF_CTX_free(kctx);
    return ret;
}