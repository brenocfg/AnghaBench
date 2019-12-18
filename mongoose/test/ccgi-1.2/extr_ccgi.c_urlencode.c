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
 scalar_t__ isalnum (char const) ; 
 scalar_t__ strchr (char const*,char const) ; 

__attribute__((used)) static char *
urlencode(const char *in, char *out, const char *keep) {
    const char hexdigit[] = "0123456789ABCDEF";

    for (; *in != 0; in++) {
        if (isalnum(*in) ||
            (keep != 0 && strchr(keep, *in) != 0))
        {
            *out++ = *in;
        }
        else if (*in == ' ') {
            *out++ = '+';
        }
        else {
            *out++ = '%';
            *out++ = hexdigit[(*in >> 4) & 0xf];
            *out++ = hexdigit[*in & 0xf];
        }
    }
    *out = 0;
    return out;
}