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
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_MD ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SSHKDF_SESSION_ID ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SSHKDF_TYPE ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_SSHKDF_XCGHASH ; 
 int /*<<< orphan*/  KDF_F_KDF_SSHKDF_CTRL_STR ; 
 int /*<<< orphan*/  KDF_R_UNKNOWN_PARAMETER_TYPE ; 
 int /*<<< orphan*/  KDF_R_VALUE_ERROR ; 
 int /*<<< orphan*/  KDF_R_VALUE_MISSING ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int call_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int kdf_hex2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int kdf_md2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  kdf_sshkdf_ctrl ; 
 int kdf_str2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int kdf_sshkdf_ctrl_str(EVP_KDF_IMPL *impl, const char *type,
                               const char *value)
{
    if (value == NULL) {
        KDFerr(KDF_F_KDF_SSHKDF_CTRL_STR, KDF_R_VALUE_MISSING);
        return 0;
    }

    if (strcmp(type, "digest") == 0)
        return kdf_md2ctrl(impl, kdf_sshkdf_ctrl, EVP_KDF_CTRL_SET_MD, value);
    /* alias, for historical reasons */
    if (strcmp(type, "md") == 0)
        return kdf_md2ctrl(impl, kdf_sshkdf_ctrl, EVP_KDF_CTRL_SET_MD, value);

    if (strcmp(type, "key") == 0)
        return kdf_str2ctrl(impl, kdf_sshkdf_ctrl,
                            EVP_KDF_CTRL_SET_KEY, value);

    if (strcmp(type, "hexkey") == 0)
        return kdf_hex2ctrl(impl, kdf_sshkdf_ctrl,
                            EVP_KDF_CTRL_SET_KEY, value);

    if (strcmp(type, "xcghash") == 0)
        return kdf_str2ctrl(impl, kdf_sshkdf_ctrl,
                            EVP_KDF_CTRL_SET_SSHKDF_XCGHASH, value);

    if (strcmp(type, "hexxcghash") == 0)
        return kdf_hex2ctrl(impl, kdf_sshkdf_ctrl,
                            EVP_KDF_CTRL_SET_SSHKDF_XCGHASH, value);

    if (strcmp(type, "session_id") == 0)
        return kdf_str2ctrl(impl, kdf_sshkdf_ctrl,
                            EVP_KDF_CTRL_SET_SSHKDF_SESSION_ID, value);

    if (strcmp(type, "hexsession_id") == 0)
        return kdf_hex2ctrl(impl, kdf_sshkdf_ctrl,
                            EVP_KDF_CTRL_SET_SSHKDF_SESSION_ID, value);

    if (strcmp(type, "type") == 0) {
        if (strlen(value) != 1) {
            KDFerr(KDF_F_KDF_SSHKDF_CTRL_STR, KDF_R_VALUE_ERROR);
            return 0;
        }

        return call_ctrl(kdf_sshkdf_ctrl, impl, EVP_KDF_CTRL_SET_SSHKDF_TYPE,
                         (int)value[0]);
    }

    KDFerr(KDF_F_KDF_SSHKDF_CTRL_STR, KDF_R_UNKNOWN_PARAMETER_TYPE);
    return -2;
}