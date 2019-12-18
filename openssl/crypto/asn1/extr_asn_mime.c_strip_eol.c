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
 int SMIME_ASCIICRLF ; 

__attribute__((used)) static int strip_eol(char *linebuf, int *plen, int flags)
{
    int len = *plen;
    char *p, c;
    int is_eol = 0;

    for (p = linebuf + len - 1; len > 0; len--, p--) {
        c = *p;
        if (c == '\n') {
            is_eol = 1;
        } else if (is_eol && flags & SMIME_ASCIICRLF && c == 32) {
            /* Strip trailing space on a line; 32 == ASCII for ' ' */
            continue;
        } else if (c != '\r') {
            break;
        }
    }
    *plen = len;
    return is_eol;
}