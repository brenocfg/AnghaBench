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
typedef  int /*<<< orphan*/  EVP_KDF_IMPL ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_MAXMEM_BYTES ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_PASS ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SALT ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SCRYPT_N ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SCRYPT_P ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SCRYPT_R ; 
 int /*<<< orphan*/  KDF_F_KDF_SCRYPT_CTRL_STR ; 
 int /*<<< orphan*/  KDF_R_VALUE_MISSING ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kdf_hex2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  kdf_scrypt_ctrl ; 
 int kdf_scrypt_ctrl_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int kdf_scrypt_ctrl_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int kdf_str2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int kdf_scrypt_ctrl_str(EVP_KDF_IMPL *impl, const char *type,
                               const char *value)
{
    if (value == NULL) {
        KDFerr(KDF_F_KDF_SCRYPT_CTRL_STR, KDF_R_VALUE_MISSING);
        return 0;
    }

    if (strcmp(type, "pass") == 0)
        return kdf_str2ctrl(impl, kdf_scrypt_ctrl, EVP_KDF_CTRL_SET_PASS,
                            value);

    if (strcmp(type, "hexpass") == 0)
        return kdf_hex2ctrl(impl, kdf_scrypt_ctrl, EVP_KDF_CTRL_SET_PASS,
                            value);

    if (strcmp(type, "salt") == 0)
        return kdf_str2ctrl(impl, kdf_scrypt_ctrl, EVP_KDF_CTRL_SET_SALT,
                            value);

    if (strcmp(type, "hexsalt") == 0)
        return kdf_hex2ctrl(impl, kdf_scrypt_ctrl, EVP_KDF_CTRL_SET_SALT,
                            value);

    if (strcmp(type, "N") == 0)
        return kdf_scrypt_ctrl_uint64(impl, EVP_KDF_CTRL_SET_SCRYPT_N, value);

    if (strcmp(type, "r") == 0)
        return kdf_scrypt_ctrl_uint32(impl, EVP_KDF_CTRL_SET_SCRYPT_R, value);

    if (strcmp(type, "p") == 0)
        return kdf_scrypt_ctrl_uint32(impl, EVP_KDF_CTRL_SET_SCRYPT_P, value);

    if (strcmp(type, "maxmem_bytes") == 0)
        return kdf_scrypt_ctrl_uint64(impl, EVP_KDF_CTRL_SET_MAXMEM_BYTES,
                                      value);

    return -2;
}