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
typedef  scalar_t__ ptrdiff_t ;

/* Variables and functions */
 scalar_t__ memchr (char const*,int,size_t) ; 

void *memrchr(const void *s, int c, size_t n)
{
    const char *end = (const char *)s + n + 1;
    const char *prev = NULL;

    for (const char *cur = s; cur <= end; prev = cur++) {
        cur = (const char *)memchr(cur, c, (size_t)(ptrdiff_t)(end - cur));
        if (!cur)
            break;
    }

    return (void *)prev;
}