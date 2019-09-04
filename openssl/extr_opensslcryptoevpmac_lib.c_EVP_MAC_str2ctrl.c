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
typedef  int /*<<< orphan*/  EVP_MAC_CTX ;

/* Variables and functions */
 int EVP_MAC_ctrl (int /*<<< orphan*/ *,int,char const*,size_t) ; 
 size_t INT_MAX ; 
 size_t strlen (char const*) ; 

int EVP_MAC_str2ctrl(EVP_MAC_CTX *ctx, int cmd, const char *value)
{
    size_t len;

    len = strlen(value);
    if (len > INT_MAX)
        return -1;
    return EVP_MAC_ctrl(ctx, cmd, value, len);
}