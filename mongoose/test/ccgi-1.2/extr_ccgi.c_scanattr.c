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
 char* scanspaces (char*) ; 

__attribute__((used)) static char *
scanattr(char *p, char *attr[2]) {
    int quote = 0;

    attr[0] = p = scanspaces(p);
    while (*p != '=' && *p != 0) {
        p++;
    }
    if (*p != '=' || p == attr[0]) {
        return 0;
    }
    *p++ = 0;
    if (*p == '"' || *p == '\'' || *p == '`') {
        quote = *p++;
    }
    attr[1] = p;
    if (quote != 0) {
        while(*p != quote && *p != 0) {
            p++;
        }
        if (*p != quote) {
            return 0;
        }
        *p++ = 0;
        if (*p == ';') {
            p++;
        }
    }
    else {
        while (*p != ';' && *p != ' ' && *p != '\t' &&
            *p != '\r' && *p != '\n' && *p != 0)
        {
            p++;
        }
        if (*p != 0) {
            *p++ = 0;
        }
    }
    return p;
}