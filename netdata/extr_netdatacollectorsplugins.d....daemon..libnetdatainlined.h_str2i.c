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
 scalar_t__ unlikely (char) ; 

__attribute__((used)) static inline int str2i(const char *s) {
    int n = 0;
    char c, negative = (*s == '-');

    for(c = (negative)?*(++s):*s; c >= '0' && c <= '9' ; c = *(++s)) {
        n *= 10;
        n += c - '0';
    }

    if(unlikely(negative))
        return -n;

    return n;
}