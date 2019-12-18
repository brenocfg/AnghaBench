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
typedef  int /*<<< orphan*/  sa_family_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  lwan_status_critical (char*) ; 
 int /*<<< orphan*/  parse_listener_ipv4 (char*,char**,char**) ; 
 int /*<<< orphan*/  parse_listener_ipv6 (char*,char**,char**) ; 
 scalar_t__ streq (char*,char*) ; 

__attribute__((used)) static sa_family_t parse_listener(char *listener, char **node, char **port)
{
    if (streq(listener, "systemd")) {
        lwan_status_critical(
            "Listener configured to use systemd socket activation, "
            "but started outside systemd.");
        return AF_UNSPEC;
    }

    if (*listener == '[')
        return parse_listener_ipv6(listener, node, port);

    return parse_listener_ipv4(listener, node, port);
}