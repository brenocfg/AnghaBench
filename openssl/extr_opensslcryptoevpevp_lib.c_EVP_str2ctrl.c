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

/* Variables and functions */
 size_t INT_MAX ; 
 size_t strlen (char const*) ; 

int EVP_str2ctrl(int (*cb)(void *ctx, int cmd, void *buf, size_t buflen),
                 void *ctx, int cmd, const char *value)
{
    size_t len;

    len = strlen(value);
    if (len > INT_MAX)
        return -1;
    return cb(ctx, cmd, (void *)value, len);
}