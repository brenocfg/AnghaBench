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
 int /*<<< orphan*/  EVP_KDF_CTRL_ADD_TLS_SEED ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_MD ; 
 int /*<<< orphan*/  EVP_KDF_CTRL_SET_TLS_SECRET ; 
 int /*<<< orphan*/  KDF_F_KDF_TLS1_PRF_CTRL_STR ; 
 int /*<<< orphan*/  KDF_R_VALUE_MISSING ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kdf_hex2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int kdf_md2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int kdf_str2ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  kdf_tls1_prf_ctrl ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int kdf_tls1_prf_ctrl_str(EVP_KDF_IMPL *impl,
                                 const char *type, const char *value)
{
    if (value == NULL) {
        KDFerr(KDF_F_KDF_TLS1_PRF_CTRL_STR, KDF_R_VALUE_MISSING);
        return 0;
    }
    if (strcmp(type, "digest") == 0)
        return kdf_md2ctrl(impl, kdf_tls1_prf_ctrl, EVP_KDF_CTRL_SET_MD, value);

    if (strcmp(type, "secret") == 0)
        return kdf_str2ctrl(impl, kdf_tls1_prf_ctrl,
                            EVP_KDF_CTRL_SET_TLS_SECRET, value);

    if (strcmp(type, "hexsecret") == 0)
        return kdf_hex2ctrl(impl, kdf_tls1_prf_ctrl,
                            EVP_KDF_CTRL_SET_TLS_SECRET, value);

    if (strcmp(type, "seed") == 0)
        return kdf_str2ctrl(impl, kdf_tls1_prf_ctrl, EVP_KDF_CTRL_ADD_TLS_SEED,
                            value);

    if (strcmp(type, "hexseed") == 0)
        return kdf_hex2ctrl(impl, kdf_tls1_prf_ctrl, EVP_KDF_CTRL_ADD_TLS_SEED,
                            value);

    return -2;
}