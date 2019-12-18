#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vport {TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  priv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  IFF_OVS_DATAPATH ; 
 int /*<<< orphan*/  dev_set_promiscuity (TYPE_1__*,int) ; 
 int /*<<< orphan*/  netdev_master_upper_dev_get (TYPE_1__*) ; 
 int /*<<< orphan*/  netdev_rx_handler_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  netdev_upper_dev_unlink (TYPE_1__*,int /*<<< orphan*/ ) ; 

void ovs_netdev_detach_dev(struct vport *vport)
{
	ASSERT_RTNL();
	vport->dev->priv_flags &= ~IFF_OVS_DATAPATH;
	netdev_rx_handler_unregister(vport->dev);
	netdev_upper_dev_unlink(vport->dev,
				netdev_master_upper_dev_get(vport->dev));
	dev_set_promiscuity(vport->dev, -1);
}