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
 scalar_t__ unlikely (int) ; 

void json_escape_string(char *dst, const char *src, size_t size) {
    const char *t;
    char *d = dst, *e = &dst[size - 1];

    for(t = src; *t && d < e ;t++) {
        if(unlikely(*t == '\\' || *t == '"')) {
            if(unlikely(d + 1 >= e)) break;
            *d++ = '\\';
        }
        *d++ = *t;
    }

    *d = '\0';
}