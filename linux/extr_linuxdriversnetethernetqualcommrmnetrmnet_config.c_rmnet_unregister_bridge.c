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
struct rmnet_port {scalar_t__ rmnet_mode; struct net_device* bridge_ep; int /*<<< orphan*/  nr_rmnet_devs; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RMNET_EPMODE_BRIDGE ; 
 scalar_t__ RMNET_EPMODE_VND ; 
 struct rmnet_port* rmnet_get_port_rtnl (struct net_device*) ; 
 int /*<<< orphan*/  rmnet_unregister_real_device (struct net_device*,struct rmnet_port*) ; 

__attribute__((used)) static void rmnet_unregister_bridge(struct net_device *dev,
				    struct rmnet_port *port)
{
	struct rmnet_port *bridge_port;
	struct net_device *bridge_dev;

	if (port->rmnet_mode != RMNET_EPMODE_BRIDGE)
		return;

	/* bridge slave handling */
	if (!port->nr_rmnet_devs) {
		bridge_dev = port->bridge_ep;

		bridge_port = rmnet_get_port_rtnl(bridge_dev);
		bridge_port->bridge_ep = NULL;
		bridge_port->rmnet_mode = RMNET_EPMODE_VND;
	} else {
		bridge_dev = port->bridge_ep;

		bridge_port = rmnet_get_port_rtnl(bridge_dev);
		rmnet_unregister_real_device(bridge_dev, bridge_port);
	}
}