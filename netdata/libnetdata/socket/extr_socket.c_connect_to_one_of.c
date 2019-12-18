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
struct timeval {int dummy; } ;

/* Variables and functions */
 int connect_to_this (char*,int,struct timeval*) ; 
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  strncpyz (char*,char const*,int) ; 

int connect_to_one_of(const char *destination, int default_port, struct timeval *timeout, size_t *reconnects_counter, char *connected_to, size_t connected_to_size) {
    int sock = -1;

    const char *s = destination;
    while(*s) {
        const char *e = s;

        // skip path, moving both s(tart) and e(nd)
        if(*e == '/')
            while(!isspace(*e) && *e != ',') s = ++e;

        // skip separators, moving both s(tart) and e(nd)
        while(isspace(*e) || *e == ',') s = ++e;

        // move e(nd) to the first separator
        while(*e && !isspace(*e) && *e != ',' && *e != '/') e++;

        // is there anything?
        if(!*s || s == e) break;

        char buf[e - s + 1];
        strncpyz(buf, s, e - s);
        if(reconnects_counter) *reconnects_counter += 1;
        sock = connect_to_this(buf, default_port, timeout);
        if(sock != -1) {
            if(connected_to && connected_to_size) {
                strncpy(connected_to, buf, connected_to_size);
                connected_to[connected_to_size - 1] = '\0';
            }
            break;
        }
        s = e;
    }

    return sock;
}