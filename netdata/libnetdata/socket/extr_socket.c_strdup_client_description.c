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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNIX 128 
 int /*<<< orphan*/  snprintfz (char*,int,char*,char const*,char const*,...) ; 
 char* strdupz (char*) ; 

char *strdup_client_description(int family, const char *protocol, const char *ip, uint16_t port) {
    char buffer[100 + 1];

    switch(family) {
        case AF_INET:
            snprintfz(buffer, 100, "%s:%s:%d", protocol, ip, port);
            break;

        case AF_INET6:
        default:
            snprintfz(buffer, 100, "%s:[%s]:%d", protocol, ip, port);
            break;

        case AF_UNIX:
            snprintfz(buffer, 100, "%s:%s", protocol, ip);
            break;
    }

    return strdupz(buffer);
}