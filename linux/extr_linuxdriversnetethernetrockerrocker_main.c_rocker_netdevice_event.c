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
struct rocker_port {int dummy; } ;
struct notifier_block {int dummy; } ;
struct netdev_notifier_changeupper_info {int /*<<< orphan*/  upper_dev; int /*<<< orphan*/  linking; int /*<<< orphan*/  master; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  NETDEV_CHANGEUPPER 128 
 int NOTIFY_DONE ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 struct rocker_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  rocker_port_dev_check (struct net_device*) ; 
 int rocker_world_port_master_linked (struct rocker_port*,int /*<<< orphan*/ ) ; 
 int rocker_world_port_master_unlinked (struct rocker_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rocker_netdevice_event(struct notifier_block *unused,
				  unsigned long event, void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct netdev_notifier_changeupper_info *info;
	struct rocker_port *rocker_port;
	int err;

	if (!rocker_port_dev_check(dev))
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_CHANGEUPPER:
		info = ptr;
		if (!info->master)
			goto out;
		rocker_port = netdev_priv(dev);
		if (info->linking) {
			err = rocker_world_port_master_linked(rocker_port,
							      info->upper_dev);
			if (err)
				netdev_warn(dev, "failed to reflect master linked (err %d)\n",
					    err);
		} else {
			err = rocker_world_port_master_unlinked(rocker_port,
								info->upper_dev);
			if (err)
				netdev_warn(dev, "failed to reflect master unlinked (err %d)\n",
					    err);
		}
	}
out:
	return NOTIFY_DONE;
}