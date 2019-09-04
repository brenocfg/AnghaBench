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

void init_zephyr(void) {
    // We now rely on CONFIG_NET_APP_SETTINGS to set up bootstrap
    // network addresses.
#if 0
    #ifdef CONFIG_NETWORKING
    if (net_if_get_default() == NULL) {
        // If there's no default networking interface,
        // there's nothing to configure.
        return;
    }
    #endif
    #ifdef CONFIG_NET_IPV4
    static struct in_addr in4addr_my = {{{192, 0, 2, 1}}};
    net_if_ipv4_addr_add(net_if_get_default(), &in4addr_my, NET_ADDR_MANUAL, 0);
    static struct in_addr in4netmask_my = {{{255, 255, 255, 0}}};
    net_if_ipv4_set_netmask(net_if_get_default(), &in4netmask_my);
    static struct in_addr in4gw_my = {{{192, 0, 2, 2}}};
    net_if_ipv4_set_gw(net_if_get_default(), &in4gw_my);
    #endif
    #ifdef CONFIG_NET_IPV6
    // 2001:db8::1
    static struct in6_addr in6addr_my = {{{0x20, 0x01, 0x0d, 0xb8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}}};
    net_if_ipv6_addr_add(net_if_get_default(), &in6addr_my, NET_ADDR_MANUAL, 0);
    #endif
#endif
}