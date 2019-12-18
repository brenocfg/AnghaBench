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
struct net_device {int dummy; } ;
struct hsr_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_disable_lro (struct net_device*) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int dev_set_promiscuity (struct net_device*,int) ; 
 int /*<<< orphan*/  hsr_handle_frame ; 
 int netdev_rx_handler_register (struct net_device*,int /*<<< orphan*/ ,struct hsr_port*) ; 

__attribute__((used)) static int hsr_portdev_setup(struct net_device *dev, struct hsr_port *port)
{
	int res;

	dev_hold(dev);
	res = dev_set_promiscuity(dev, 1);
	if (res)
		goto fail_promiscuity;

	/* FIXME:
	 * What does net device "adjacency" mean? Should we do
	 * res = netdev_master_upper_dev_link(port->dev, port->hsr->dev); ?
	 */

	res = netdev_rx_handler_register(dev, hsr_handle_frame, port);
	if (res)
		goto fail_rx_handler;
	dev_disable_lro(dev);

	return 0;

fail_rx_handler:
	dev_set_promiscuity(dev, -1);
fail_promiscuity:
	dev_put(dev);

	return res;
}