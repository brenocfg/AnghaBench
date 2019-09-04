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
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_ITER ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_MD ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_PASS ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SALT ; 
 int /*<<< orphan*/  KDF_F_KDF_PBKDF2_CTRL_STR ; 
 int /*<<< orphan*/  KDF_R_VALUE_MISSING ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atoi (char const*) ; 
 int call_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kdf_hex2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int kdf_md2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  kdf_pbkdf2_ctrl ; 
 int kdf_str2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int kdf_pbkdf2_ctrl_str(EVP_KDF_IMPL *impl, const char *type,
                               const char *value)
{
    if (value == NULL) {
        KDFerr(KDF_F_KDF_PBKDF2_CTRL_STR, KDF_R_VALUE_MISSING);
        return 0;
    }

    if (strcmp(type, "pass") == 0)
        return kdf_str2ctrl(impl, kdf_pbkdf2_ctrl, EVP_KDF_CTRL_SET_PASS,
                            value);

    if (strcmp(type, "hexpass") == 0)
        return kdf_hex2ctrl(impl, kdf_pbkdf2_ctrl, EVP_KDF_CTRL_SET_PASS,
                            value);

    if (strcmp(type, "salt") == 0)
        return kdf_str2ctrl(impl, kdf_pbkdf2_ctrl, EVP_KDF_CTRL_SET_SALT,
                            value);

    if (strcmp(type, "hexsalt") == 0)
        return kdf_hex2ctrl(impl, kdf_pbkdf2_ctrl, EVP_KDF_CTRL_SET_SALT,
                            value);

    if (strcmp(type, "iter") == 0)
        return call_ctrl(kdf_pbkdf2_ctrl, impl, EVP_KDF_CTRL_SET_ITER,
                         atoi(value));

    if (strcmp(type, "digest") == 0)
        return kdf_md2ctrl(impl, kdf_pbkdf2_ctrl, EVP_KDF_CTRL_SET_MD, value);

    return -2;
}