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
struct netdev_notifier_changeupper_info {int /*<<< orphan*/  upper_dev; scalar_t__ linking; } ;
struct net_device {int dummy; } ;
struct dsa_port {int dummy; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int dsa_port_bridge_join (struct dsa_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_port_bridge_leave (struct dsa_port*,int /*<<< orphan*/ ) ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 scalar_t__ netif_is_bridge_master (int /*<<< orphan*/ ) ; 
 int notifier_from_errno (int) ; 

__attribute__((used)) static int dsa_slave_changeupper(struct net_device *dev,
				 struct netdev_notifier_changeupper_info *info)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	int err = NOTIFY_DONE;

	if (netif_is_bridge_master(info->upper_dev)) {
		if (info->linking) {
			err = dsa_port_bridge_join(dp, info->upper_dev);
			err = notifier_from_errno(err);
		} else {
			dsa_port_bridge_leave(dp, info->upper_dev);
			err = NOTIFY_OK;
		}
	}

	return err;
}