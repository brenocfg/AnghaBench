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
typedef  int /*<<< orphan*/  salt ;
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  other ;
typedef  int /*<<< orphan*/  expected ;
typedef  int /*<<< orphan*/  EVP_MAC ;
typedef  int /*<<< orphan*/  const EVP_KDF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_KEY ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_MAC ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_MD ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SALT ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SSKDF_INFO ; 
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_KDF_CTX_new_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_KDF_SS ; 
 int /*<<< orphan*/  EVP_KDF_ctrl (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned char const*,...) ; 
 int /*<<< orphan*/  EVP_KDF_derive (int /*<<< orphan*/  const*,unsigned char*,int) ; 
 int /*<<< orphan*/ * EVP_get_macbyname (char*) ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 scalar_t__ TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_mem_eq (unsigned char*,int,unsigned char const*,int) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int test_kdf_ss_hmac(void)
{
    int ret;
    EVP_KDF_CTX *kctx;
    const EVP_MAC *mac;

    const unsigned char z[] = {
        0xb7,0x4a,0x14,0x9a,0x16,0x15,0x46,0xf8,0xc2,0x0b,0x06,0xac,0x4e,0xd4
    };
    const unsigned char other[] = {
        0x34,0x8a,0x37,0xa2,0x7e,0xf1,0x28,0x2f,0x5f,0x02,0x0d,0xcc
    };
    const unsigned char salt[] = {
        0x36,0x38,0x27,0x1c,0xcd,0x68,0xa2,0x5d,0xc2,0x4e,0xcd,0xdd,0x39,0xef,
        0x3f,0x89
    };
    const unsigned char expected[] = {
        0x44,0xf6,0x76,0xe8,0x5c,0x1b,0x1a,0x8b,0xbc,0x3d,0x31,0x92,0x18,0x63,
        0x1c,0xa3
    };
    unsigned char out[16];

    ret =
        TEST_ptr(kctx = EVP_KDF_CTX_new_id(EVP_KDF_SS))
        && TEST_ptr(mac = EVP_get_macbyname("HMAC"))
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_MAC, mac), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_MD,  EVP_sha256()), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_KEY, z, sizeof(z)), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_SSKDF_INFO, other,
                                    sizeof(other)), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_SALT, salt,
                                    sizeof(salt)), 0)
        && TEST_int_gt(EVP_KDF_derive(kctx, out, sizeof(out)), 0)
        && TEST_mem_eq(out, sizeof(out), expected, sizeof(expected));

    EVP_KDF_CTX_free(kctx);
    return ret;
}