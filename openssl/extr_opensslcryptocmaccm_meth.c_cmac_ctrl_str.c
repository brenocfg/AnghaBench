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
typedef  int /*<<< orphan*/  EVP_MAC_IMPL ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MAC_CTRL_SET_CIPHER ; 
 int /*<<< orphan*/  EVP_MAC_CTRL_SET_KEY ; 
 int /*<<< orphan*/ * EVP_get_cipherbyname (char const*) ; 
 int EVP_hex2ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int EVP_str2ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int cmac_ctrl_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cmac_ctrl_str_cb ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int cmac_ctrl_str(EVP_MAC_IMPL *cctx, const char *type,
                         const char *value)
{
    if (!value)
        return 0;
    if (strcmp(type, "cipher") == 0) {
        const EVP_CIPHER *c = EVP_get_cipherbyname(value);

        if (c == NULL)
            return 0;
        return cmac_ctrl_int(cctx, EVP_MAC_CTRL_SET_CIPHER, c);
    }
    if (strcmp(type, "key") == 0)
        return EVP_str2ctrl(cmac_ctrl_str_cb, cctx, EVP_MAC_CTRL_SET_KEY,
                            value);
    if (strcmp(type, "hexkey") == 0)
        return EVP_hex2ctrl(cmac_ctrl_str_cb, cctx, EVP_MAC_CTRL_SET_KEY,
                            value);
    return -2;
}