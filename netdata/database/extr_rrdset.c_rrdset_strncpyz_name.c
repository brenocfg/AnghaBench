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
 int /*<<< orphan*/  isalnum (char) ; 

char *rrdset_strncpyz_name(char *to, const char *from, size_t length) {
    char c, *p = to;

    while (length-- && (c = *from++)) {
        if(c != '.' && !isalnum(c))
            c = '_';

        *p++ = c;
    }

    *p = '\0';

    return to;
}