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
 scalar_t__ isspace (char) ; 

inline char *trim_all(char *buffer) {
    char *d = buffer, *s = buffer;

    // skip spaces
    while(isspace(*s)) s++;

    while(*s) {
        // copy the non-space part
        while(*s && !isspace(*s)) *d++ = *s++;

        // add a space if we have to
        if(*s && isspace(*s)) {
            *d++ = ' ';
            s++;
        }

        // skip spaces
        while(isspace(*s)) s++;
    }

    *d = '\0';

    if(d > buffer) {
        d--;
        if(isspace(*d)) *d = '\0';
    }

    if(!buffer[0]) return NULL;
    return buffer;
}