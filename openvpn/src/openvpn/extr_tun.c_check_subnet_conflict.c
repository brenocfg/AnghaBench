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
struct gc_arena {int dummy; } ;
typedef  int const in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_WARN ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 scalar_t__ get_default_gateway (int const*,int const*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_in_addr_t (int const,int /*<<< orphan*/ ,struct gc_arena*) ; 

void
check_subnet_conflict(const in_addr_t ip,
                      const in_addr_t netmask,
                      const char *prefix)
{
#if 0 /* too many false positives */
    struct gc_arena gc = gc_new();
    in_addr_t lan_gw = 0;
    in_addr_t lan_netmask = 0;

    if (get_default_gateway(&lan_gw, &lan_netmask) && lan_netmask)
    {
        const in_addr_t lan_network = lan_gw & lan_netmask;
        const in_addr_t network = ip & netmask;

        /* do the two subnets defined by network/netmask and lan_network/lan_netmask intersect? */
        if ((network & lan_netmask) == lan_network
            || (lan_network & netmask) == network)
        {
            msg(M_WARN, "WARNING: potential %s subnet conflict between local LAN [%s/%s] and remote VPN [%s/%s]",
                prefix,
                print_in_addr_t(lan_network, 0, &gc),
                print_in_addr_t(lan_netmask, 0, &gc),
                print_in_addr_t(network, 0, &gc),
                print_in_addr_t(netmask, 0, &gc));
        }
    }
    gc_free(&gc);
#endif /* if 0 */
}