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
struct net_bridge_port_group {int /*<<< orphan*/  eth_addr; struct net_bridge_port* port; } ;
struct net_bridge_port {int flags; } ;

/* Variables and functions */
 int BR_MULTICAST_TO_UNICAST ; 
 int ether_addr_equal (unsigned char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool br_port_group_equal(struct net_bridge_port_group *p,
				struct net_bridge_port *port,
				const unsigned char *src)
{
	if (p->port != port)
		return false;

	if (!(port->flags & BR_MULTICAST_TO_UNICAST))
		return true;

	return ether_addr_equal(src, p->eth_addr);
}