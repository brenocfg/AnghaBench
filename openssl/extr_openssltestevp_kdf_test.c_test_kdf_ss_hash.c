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
typedef  int /*<<< orphan*/  z ;
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  other ;
typedef  int /*<<< orphan*/  expected ;
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_KEY ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_MD ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SSKDF_INFO ; 
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_KDF_CTX_new_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_KDF_SS ; 
 int /*<<< orphan*/  EVP_KDF_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char const*,...) ; 
 int /*<<< orphan*/  EVP_KDF_derive (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_sha224 () ; 
 scalar_t__ TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_mem_eq (unsigned char*,int,unsigned char const*,int) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_kdf_ss_hash(void)
{
    int ret;
    EVP_KDF_CTX *kctx = NULL;
    const unsigned char z[] = {
        0x6d,0xbd,0xc2,0x3f,0x04,0x54,0x88,0xe4,0x06,0x27,0x57,0xb0,0x6b,0x9e,
        0xba,0xe1,0x83,0xfc,0x5a,0x59,0x46,0xd8,0x0d,0xb9,0x3f,0xec,0x6f,0x62,
        0xec,0x07,0xe3,0x72,0x7f,0x01,0x26,0xae,0xd1,0x2c,0xe4,0xb2,0x62,0xf4,
        0x7d,0x48,0xd5,0x42,0x87,0xf8,0x1d,0x47,0x4c,0x7c,0x3b,0x18,0x50,0xe9
    };
    const unsigned char other[] = {
        0xa1,0xb2,0xc3,0xd4,0xe5,0x43,0x41,0x56,0x53,0x69,0x64,0x3c,0x83,0x2e,
        0x98,0x49,0xdc,0xdb,0xa7,0x1e,0x9a,0x31,0x39,0xe6,0x06,0xe0,0x95,0xde,
        0x3c,0x26,0x4a,0x66,0xe9,0x8a,0x16,0x58,0x54,0xcd,0x07,0x98,0x9b,0x1e,
        0xe0,0xec,0x3f,0x8d,0xbe
    };
    const unsigned char expected[] = {
        0xa4,0x62,0xde,0x16,0xa8,0x9d,0xe8,0x46,0x6e,0xf5,0x46,0x0b,0x47,0xb8
    };
    unsigned char out[14];

    ret =
        TEST_ptr(kctx = EVP_KDF_CTX_new_id(EVP_KDF_SS))
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_MD, EVP_sha224()), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_KEY, z, sizeof(z)), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_SSKDF_INFO, other,
                                    sizeof(other)), 0)
        && TEST_int_gt(EVP_KDF_derive(kctx, out, sizeof(out)), 0)
        && TEST_mem_eq(out, sizeof(out), expected, sizeof(expected));

    EVP_KDF_CTX_free(kctx);
    return ret;
}