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
 scalar_t__ iscntrl (unsigned char) ; 
 int /*<<< orphan*/  isprint (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 
 scalar_t__ unlikely (int) ; 

void json_fix_string(char *s) {
    unsigned char c;
    while((c = (unsigned char)*s)) {
        if(unlikely(c == '\\'))
            *s++ = '/';
        else if(unlikely(c == '"'))
            *s++ = '\'';
        else if(unlikely(isspace(c) || iscntrl(c)))
            *s++ = ' ';
        else if(unlikely(!isprint(c) || c > 127))
            *s++ = '_';
        else
            s++;
    }
}