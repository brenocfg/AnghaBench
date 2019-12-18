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
typedef  int /*<<< orphan*/  xcghash ;
typedef  int /*<<< orphan*/  sessid ;
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  kdftype ;
typedef  int /*<<< orphan*/  expected ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_CTX_set_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char EVP_KDF_SSHKDF_TYPE_INITIAL_IV_CLI_TO_SRV ; 
 int /*<<< orphan*/  EVP_KDF_derive (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  OSSL_KDF_NAME_SSHKDF ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_DIGEST ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_KEY ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SSHKDF_SESSION_ID ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SSHKDF_TYPE ; 
 int /*<<< orphan*/  OSSL_KDF_PARAM_SSHKDF_XCGHASH ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_end () ; 
 void* OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,unsigned char*,int) ; 
 void* OSSL_PARAM_construct_utf8_string (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_mem_eq (unsigned char*,int,unsigned char const*,int) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_kdfbyname (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_kdf_sshkdf(void)
{
    int ret;
    EVP_KDF_CTX *kctx;
    OSSL_PARAM params[6], *p = params;
    char kdftype = EVP_KDF_SSHKDF_TYPE_INITIAL_IV_CLI_TO_SRV;
    unsigned char out[8];
    /* Test data from NIST CAVS 14.1 test vectors */
    static unsigned char key[] = {
        0x00, 0x00, 0x00, 0x81, 0x00, 0x87, 0x5c, 0x55, 0x1c, 0xef, 0x52, 0x6a,
        0x4a, 0x8b, 0xe1, 0xa7, 0xdf, 0x27, 0xe9, 0xed, 0x35, 0x4b, 0xac, 0x9a,
        0xfb, 0x71, 0xf5, 0x3d, 0xba, 0xe9, 0x05, 0x67, 0x9d, 0x14, 0xf9, 0xfa,
        0xf2, 0x46, 0x9c, 0x53, 0x45, 0x7c, 0xf8, 0x0a, 0x36, 0x6b, 0xe2, 0x78,
        0x96, 0x5b, 0xa6, 0x25, 0x52, 0x76, 0xca, 0x2d, 0x9f, 0x4a, 0x97, 0xd2,
        0x71, 0xf7, 0x1e, 0x50, 0xd8, 0xa9, 0xec, 0x46, 0x25, 0x3a, 0x6a, 0x90,
        0x6a, 0xc2, 0xc5, 0xe4, 0xf4, 0x8b, 0x27, 0xa6, 0x3c, 0xe0, 0x8d, 0x80,
        0x39, 0x0a, 0x49, 0x2a, 0xa4, 0x3b, 0xad, 0x9d, 0x88, 0x2c, 0xca, 0xc2,
        0x3d, 0xac, 0x88, 0xbc, 0xad, 0xa4, 0xb4, 0xd4, 0x26, 0xa3, 0x62, 0x08,
        0x3d, 0xab, 0x65, 0x69, 0xc5, 0x4c, 0x22, 0x4d, 0xd2, 0xd8, 0x76, 0x43,
        0xaa, 0x22, 0x76, 0x93, 0xe1, 0x41, 0xad, 0x16, 0x30, 0xce, 0x13, 0x14,
        0x4e
    };
    static unsigned char xcghash[] = {
        0x0e, 0x68, 0x3f, 0xc8, 0xa9, 0xed, 0x7c, 0x2f, 0xf0, 0x2d, 0xef, 0x23,
        0xb2, 0x74, 0x5e, 0xbc, 0x99, 0xb2, 0x67, 0xda, 0xa8, 0x6a, 0x4a, 0xa7,
        0x69, 0x72, 0x39, 0x08, 0x82, 0x53, 0xf6, 0x42
    };
    static unsigned char sessid[] = {
        0x0e, 0x68, 0x3f, 0xc8, 0xa9, 0xed, 0x7c, 0x2f, 0xf0, 0x2d, 0xef, 0x23,
        0xb2, 0x74, 0x5e, 0xbc, 0x99, 0xb2, 0x67, 0xda, 0xa8, 0x6a, 0x4a, 0xa7,
        0x69, 0x72, 0x39, 0x08, 0x82, 0x53, 0xf6, 0x42
    };
    static const unsigned char expected[sizeof(out)] = {
        0x41, 0xff, 0x2e, 0xad, 0x16, 0x83, 0xf1, 0xe6
    };

    *p++ = OSSL_PARAM_construct_utf8_string(OSSL_KDF_PARAM_DIGEST,
                                            (char *)"sha256", sizeof("sha256"));
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_KEY, key,
                                             sizeof(key));
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_SSHKDF_XCGHASH,
                                             xcghash, sizeof(xcghash));
    *p++ = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_SSHKDF_SESSION_ID,
                                             sessid, sizeof(sessid));
    *p++ = OSSL_PARAM_construct_utf8_string(OSSL_KDF_PARAM_SSHKDF_TYPE,
                                            &kdftype, sizeof(kdftype));
    *p = OSSL_PARAM_construct_end();

    ret =
        TEST_ptr(kctx = get_kdfbyname(OSSL_KDF_NAME_SSHKDF))
        && TEST_true(EVP_KDF_CTX_set_params(kctx, params))
        && TEST_int_gt(EVP_KDF_derive(kctx, out, sizeof(out)), 0)
        && TEST_mem_eq(out, sizeof(out), expected, sizeof(expected));

    EVP_KDF_CTX_free(kctx);
    return ret;
}