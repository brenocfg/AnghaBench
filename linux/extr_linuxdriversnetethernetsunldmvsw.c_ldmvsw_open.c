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
struct vio_driver_state {int dummy; } ;
struct vnet_port {struct vio_driver_state vio; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDC_EVENT_RESET ; 
 struct vnet_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vio_link_state_change (struct vio_driver_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vio_port_up (struct vio_driver_state*) ; 
 int /*<<< orphan*/  vnet_port_reset (struct vnet_port*) ; 

int ldmvsw_open(struct net_device *dev)
{
	struct vnet_port *port = netdev_priv(dev);
	struct vio_driver_state *vio = &port->vio;

	/* reset the channel */
	vio_link_state_change(vio, LDC_EVENT_RESET);
	vnet_port_reset(port);
	vio_port_up(vio);

	return 0;
}