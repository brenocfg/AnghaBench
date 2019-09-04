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
typedef  int /*<<< orphan*/  const EVP_KDF_CTX ;
typedef  int /*<<< orphan*/  EVP_KDF ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KDF_CTRL_ADD_TLS_SEED ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_MD ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_TLS_SECRET ; 
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_KDF_CTX_kdf (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_KDF_CTX_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_KDF_ctrl (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  EVP_KDF_derive (int /*<<< orphan*/  const*,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_KDF_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_get_kdfbyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 int /*<<< orphan*/  SN_tls1_prf ; 
 scalar_t__ TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_mem_eq (unsigned char*,int,unsigned char const*,int) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/  const*) ; 
 scalar_t__ TEST_ptr_eq (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ TEST_str_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_kdf_tls1_prf(void)
{
    int ret;
    EVP_KDF_CTX *kctx = NULL;
    const EVP_KDF *kdf;
    unsigned char out[16];
    const unsigned char expected[sizeof(out)] = {
        0x8e, 0x4d, 0x93, 0x25, 0x30, 0xd7, 0x65, 0xa0,
        0xaa, 0xe9, 0x74, 0xc3, 0x04, 0x73, 0x5e, 0xcc
    };

    ret =
        TEST_ptr(kdf = EVP_get_kdfbyname(SN_tls1_prf))
        && TEST_ptr(kctx = EVP_KDF_CTX_new(kdf))
        && TEST_ptr_eq(EVP_KDF_CTX_kdf(kctx), kdf)
        && TEST_str_eq(EVP_KDF_name(kdf), SN_tls1_prf)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_MD, EVP_sha256()), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_SET_TLS_SECRET,
                                    "secret", (size_t)6), 0)
        && TEST_int_gt(EVP_KDF_ctrl(kctx, EVP_KDF_CTRL_ADD_TLS_SEED, "seed",
                                    (size_t)4), 0)
        && TEST_int_gt(EVP_KDF_derive(kctx, out, sizeof(out)), 0)
        && TEST_mem_eq(out, sizeof(out), expected, sizeof(expected));

    EVP_KDF_CTX_free(kctx);
    return ret;
}