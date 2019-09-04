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

int strncmp(const char *s1, const char *s2, size_t n) {
    while (*s1 && *s2 && n > 0) {
        char c1 = *s1++; // XXX UTF8 get char, next char
        char c2 = *s2++; // XXX UTF8 get char, next char
        n--;
        if (c1 < c2) return -1;
        else if (c1 > c2) return 1;
    }
    if (n == 0) return 0;
    else if (*s2) return -1;
    else if (*s1) return 1;
    else return 0;
}