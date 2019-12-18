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

__attribute__((used)) static int ia5ncasecmp(const char *s1, const char *s2, size_t n)
{
    for (; n > 0; n--, s1++, s2++) {
        if (*s1 != *s2) {
            unsigned char c1 = (unsigned char)*s1, c2 = (unsigned char)*s2;

            /* Convert to lower case */
            if (c1 >= 0x41 /* A */ && c1 <= 0x5A /* Z */)
                c1 += 0x20;
            if (c2 >= 0x41 /* A */ && c2 <= 0x5A /* Z */)
                c2 += 0x20;

            if (c1 == c2)
                continue;

            if (c1 < c2)
                return -1;

            /* c1 > c2 */
            return 1;
        } else if (*s1 == 0) {
            /* If we get here we know that *s2 == 0 too */
            return 0;
        }
    }

    return 0;
}