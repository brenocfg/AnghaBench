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
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EVP_MAC_IMPL ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MAC_CTRL_SET_KEY ; 
 int /*<<< orphan*/  EVP_MAC_CTRL_SET_MD ; 
 int /*<<< orphan*/ * EVP_get_digestbyname (char const*) ; 
 int EVP_hex2ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int EVP_str2ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int hmac_ctrl_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hmac_ctrl_str_cb ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int hmac_ctrl_str(EVP_MAC_IMPL *hctx, const char *type,
                         const char *value)
{
    if (!value)
        return 0;
    if (strcmp(type, "digest") == 0) {
        const EVP_MD *d = EVP_get_digestbyname(value);

        if (d == NULL)
            return 0;
        return hmac_ctrl_int(hctx, EVP_MAC_CTRL_SET_MD, d);
    }
    if (strcmp(type, "key") == 0)
        return EVP_str2ctrl(hmac_ctrl_str_cb, hctx, EVP_MAC_CTRL_SET_KEY,
                            value);
    if (strcmp(type, "hexkey") == 0)
        return EVP_hex2ctrl(hmac_ctrl_str_cb, hctx, EVP_MAC_CTRL_SET_KEY,
                            value);
    return -2;
}