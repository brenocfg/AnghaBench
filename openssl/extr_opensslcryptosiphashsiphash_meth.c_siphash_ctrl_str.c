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

/* Variables and functions */
 int /*<<< orphan*/  EVP_MAC_CTRL_SET_KEY ; 
 int /*<<< orphan*/  EVP_MAC_CTRL_SET_SIZE ; 
 int EVP_hex2ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int EVP_str2ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 size_t atoi (char const*) ; 
 int siphash_ctrl_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  siphash_ctrl_str_cb ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int siphash_ctrl_str(EVP_MAC_IMPL *ctx,
                            const char *type, const char *value)
{
    if (value == NULL)
        return 0;
    if (strcmp(type, "digestsize") == 0) {
        size_t hash_size = atoi(value);

        return siphash_ctrl_int(ctx, EVP_MAC_CTRL_SET_SIZE, hash_size);
    }
    if (strcmp(type, "key") == 0)
        return EVP_str2ctrl(siphash_ctrl_str_cb, ctx, EVP_MAC_CTRL_SET_KEY,
                            value);
    if (strcmp(type, "hexkey") == 0)
        return EVP_hex2ctrl(siphash_ctrl_str_cb, ctx, EVP_MAC_CTRL_SET_KEY,
                            value);
    return -2;
}