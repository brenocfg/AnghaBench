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
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_KEY ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_MAC ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_MAC_SIZE ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_MD ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SALT ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SSKDF_INFO ; 
 int /*<<< orphan*/  KDF_F_SSKDF_CTRL_STR ; 
 int /*<<< orphan*/  KDF_R_VALUE_ERROR ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int atoi (char const*) ; 
 int call_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int kdf_hex2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int kdf_md2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int kdf_str2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sskdf_ctrl ; 
 int sskdf_mac2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int sskdf_ctrl_str(EVP_KDF_IMPL *impl, const char *type,
                          const char *value)
{
    if (strcmp(type, "secret") == 0 || strcmp(type, "key") == 0)
         return kdf_str2ctrl(impl, sskdf_ctrl, EVP_KDF_CTRL_SET_KEY,
                             value);

    if (strcmp(type, "hexsecret") == 0 || strcmp(type, "hexkey") == 0)
        return kdf_hex2ctrl(impl, sskdf_ctrl, EVP_KDF_CTRL_SET_KEY,
                            value);

    if (strcmp(type, "info") == 0)
        return kdf_str2ctrl(impl, sskdf_ctrl, EVP_KDF_CTRL_SET_SSKDF_INFO,
                            value);

    if (strcmp(type, "hexinfo") == 0)
        return kdf_hex2ctrl(impl, sskdf_ctrl, EVP_KDF_CTRL_SET_SSKDF_INFO,
                            value);

    if (strcmp(type, "digest") == 0)
        return kdf_md2ctrl(impl, sskdf_ctrl, EVP_KDF_CTRL_SET_MD, value);

    if (strcmp(type, "mac") == 0)
        return sskdf_mac2ctrl(impl, sskdf_ctrl, EVP_KDF_CTRL_SET_MAC, value);

    if (strcmp(type, "salt") == 0)
        return kdf_str2ctrl(impl, sskdf_ctrl, EVP_KDF_CTRL_SET_SALT, value);

    if (strcmp(type, "hexsalt") == 0)
        return kdf_hex2ctrl(impl, sskdf_ctrl, EVP_KDF_CTRL_SET_SALT, value);


    if (strcmp(type, "maclen") == 0) {
        int val = atoi(value);
        if (val < 0) {
            KDFerr(KDF_F_SSKDF_CTRL_STR, KDF_R_VALUE_ERROR);
            return 0;
        }
        return call_ctrl(sskdf_ctrl, impl, EVP_KDF_CTRL_SET_MAC_SIZE,
                         (size_t)val);
    }
    return -2;
}