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
struct net_device {int /*<<< orphan*/  rx_handler_data; } ;
struct net_bridge_port {int dummy; } ;

/* Variables and functions */
 scalar_t__ netif_is_bridge_port (struct net_device const*) ; 
 struct net_bridge_port* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct net_bridge_port *br_port_get_rtnl(const struct net_device *dev)
{
	return netif_is_bridge_port(dev) ?
		rtnl_dereference(dev->rx_handler_data) : NULL;
}