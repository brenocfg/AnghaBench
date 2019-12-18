#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct netdev_phys_item_id {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  switch_id; int /*<<< orphan*/  switch_port; } ;
struct devlink_port {TYPE_1__ attrs; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  memcpy (struct netdev_phys_item_id*,int /*<<< orphan*/ *,int) ; 
 struct devlink_port* netdev_to_devlink_port (struct net_device*) ; 

int devlink_compat_switch_id_get(struct net_device *dev,
				 struct netdev_phys_item_id *ppid)
{
	struct devlink_port *devlink_port;

	/* Caller must hold RTNL mutex or reference to dev, which ensures that
	 * devlink_port instance cannot disappear in the middle. No need to take
	 * any devlink lock as only permanent values are accessed.
	 */
	devlink_port = netdev_to_devlink_port(dev);
	if (!devlink_port || !devlink_port->attrs.switch_port)
		return -EOPNOTSUPP;

	memcpy(ppid, &devlink_port->attrs.switch_id, sizeof(*ppid));

	return 0;
}