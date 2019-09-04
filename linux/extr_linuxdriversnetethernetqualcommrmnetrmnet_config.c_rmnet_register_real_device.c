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
struct rmnet_port {int /*<<< orphan*/ * muxed_ep; struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int RMNET_MAX_LOGICAL_EP ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct rmnet_port*) ; 
 struct rmnet_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int netdev_rx_handler_register (struct net_device*,int /*<<< orphan*/ ,struct rmnet_port*) ; 
 scalar_t__ rmnet_is_real_dev_registered (struct net_device*) ; 
 int /*<<< orphan*/  rmnet_rx_handler ; 

__attribute__((used)) static int rmnet_register_real_device(struct net_device *real_dev)
{
	struct rmnet_port *port;
	int rc, entry;

	ASSERT_RTNL();

	if (rmnet_is_real_dev_registered(real_dev))
		return 0;

	port = kzalloc(sizeof(*port), GFP_ATOMIC);
	if (!port)
		return -ENOMEM;

	port->dev = real_dev;
	rc = netdev_rx_handler_register(real_dev, rmnet_rx_handler, port);
	if (rc) {
		kfree(port);
		return -EBUSY;
	}

	/* hold on to real dev for MAP data */
	dev_hold(real_dev);

	for (entry = 0; entry < RMNET_MAX_LOGICAL_EP; entry++)
		INIT_HLIST_HEAD(&port->muxed_ep[entry]);

	netdev_dbg(real_dev, "registered with rmnet\n");
	return 0;
}