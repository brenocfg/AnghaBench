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
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

inline char *url_find_protocol(char *s) {
    while(*s) {
        // find the next space
        while (*s && *s != ' ') s++;

        // is it SPACE + "HTTP/" ?
        if(*s && !strncmp(s, " HTTP/", 6)) break;
        else s++;
    }

    return s;
}