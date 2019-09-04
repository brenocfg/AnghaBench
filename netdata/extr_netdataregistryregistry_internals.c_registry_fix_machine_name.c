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
 scalar_t__ likely (size_t*) ; 
 scalar_t__ unlikely (scalar_t__) ; 

__attribute__((used)) static inline char *registry_fix_machine_name(char *name, size_t *len) {
    char *s = name?name:"";

    // skip leading spaces
    while(*s && isspace(*s)) s++;

    // make sure all spaces are a SPACE
    char *t = s;
    while(*t) {
        if(unlikely(isspace(*t)))
            *t = ' ';

        t++;
    }

    // remove trailing spaces
    while(--t >= s) {
        if(*t == ' ')
            *t = '\0';
        else
            break;
    }
    t++;

    if(likely(len))
        *len = (t - s);

    return s;
}