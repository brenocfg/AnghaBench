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
 int /*<<< orphan*/  EVP_KDF_CTRL_ADD_HKDF_INFO ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_HKDF_MODE ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_KEY ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_MD ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SALT ; 
 int EVP_KDF_HKDF_MODE_EXPAND_ONLY ; 
 int EVP_KDF_HKDF_MODE_EXTRACT_AND_EXPAND ; 
 int EVP_KDF_HKDF_MODE_EXTRACT_ONLY ; 
 int call_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int kdf_hex2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  kdf_hkdf_ctrl ; 
 int kdf_md2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int kdf_str2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int kdf_hkdf_ctrl_str(EVP_KDF_IMPL *impl, const char *type,
                             const char *value)
{
    if (strcmp(type, "mode") == 0) {
        int mode;

        if (strcmp(value, "EXTRACT_AND_EXPAND") == 0)
            mode = EVP_KDF_HKDF_MODE_EXTRACT_AND_EXPAND;
        else if (strcmp(value, "EXTRACT_ONLY") == 0)
            mode = EVP_KDF_HKDF_MODE_EXTRACT_ONLY;
        else if (strcmp(value, "EXPAND_ONLY") == 0)
            mode = EVP_KDF_HKDF_MODE_EXPAND_ONLY;
        else
            return 0;

        return call_ctrl(kdf_hkdf_ctrl, impl, EVP_KDF_CTRL_SET_HKDF_MODE, mode);
    }

    if (strcmp(type, "digest") == 0)
        return kdf_md2ctrl(impl, kdf_hkdf_ctrl, EVP_KDF_CTRL_SET_MD, value);

    if (strcmp(type, "salt") == 0)
        return kdf_str2ctrl(impl, kdf_hkdf_ctrl, EVP_KDF_CTRL_SET_SALT, value);

    if (strcmp(type, "hexsalt") == 0)
        return kdf_hex2ctrl(impl, kdf_hkdf_ctrl, EVP_KDF_CTRL_SET_SALT, value);

    if (strcmp(type, "key") == 0)
        return kdf_str2ctrl(impl, kdf_hkdf_ctrl, EVP_KDF_CTRL_SET_KEY, value);

    if (strcmp(type, "hexkey") == 0)
        return kdf_hex2ctrl(impl, kdf_hkdf_ctrl, EVP_KDF_CTRL_SET_KEY, value);

    if (strcmp(type, "info") == 0)
        return kdf_str2ctrl(impl, kdf_hkdf_ctrl, EVP_KDF_CTRL_ADD_HKDF_INFO,
                            value);

    if (strcmp(type, "hexinfo") == 0)
        return kdf_hex2ctrl(impl, kdf_hkdf_ctrl, EVP_KDF_CTRL_ADD_HKDF_INFO,
                            value);

    return -2;
}