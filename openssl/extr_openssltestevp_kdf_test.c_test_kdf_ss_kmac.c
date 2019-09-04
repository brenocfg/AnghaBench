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
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_MAC_SIZE ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SALT ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SSKDF_INFO ; 
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_KDF_CTX_new_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_KDF_SS ; 
 int /*<<< orphan*/  EVP_KDF_ctrl (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  EVP_KDF_derive (int /*<<< orphan*/  const*,unsigned char*,int) ; 
 int /*<<< orphan*/ * EVP_get_macbyname (char*) ; 
 scalar_t__ TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_mem_eq (unsigned char*,int,unsigned char const*,int) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int test_kdf_ss_kmac(void)
{
    int ret;
    EVP_KDF_CTX *kctx;
    unsigned char out[64];
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
        0xe9,0xc1,0x84,0x53,0xa0,0x62,0xb5,0x3b,0xdb,0xfc,0xbb,0x5a,0x34,0xbd,
        0xb8,0xe5,0xe7,0x07,0xee,0xbb,0x5d,0xd1,0x34,0x42,0x43,0xd8,0xcf,0xc2,
        0xc2,0xe6,0x33,0x2f,0x91,0xbd,0xa5,0x86,0xf3,0x7d,0xe4,0x8a,0x65,0xd4,
        0xc5,0x14,0xfd,0xef,0xaa,0x1e,0x67,0x54,0xf3,0x73,0xd2,0x38,0xe1,0x95,
        0xae,0x15,0x7e,0x1d,0xe8,0x14,0x98,0x03
    };

    ret =
        TEST_ptr(kctx = EVP_KDF_CTX_new_id(EVP_KDF_SS))
        && TEST_ptr(mac = EVP_get_macbyname("KMAC128"))
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_MAC, mac), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_KEY, z,
                                    sizeof(z)), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_SSKDF_INFO, other,
                                    sizeof(other)), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_SALT, salt,
                                    sizeof(salt)), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_MAC_SIZE,
                                    (size_t)20), 0)
        && TEST_int_gt(EVP_KDF_derive(kctx, out, sizeof(out)), 0)
        && TEST_mem_eq(out, sizeof(out), expected, sizeof(expected));

    EVP_KDF_CTX_free(kctx);
    return ret;
}