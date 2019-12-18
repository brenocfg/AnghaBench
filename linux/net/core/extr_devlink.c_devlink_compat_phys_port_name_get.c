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
struct devlink_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EOPNOTSUPP ; 
 int __devlink_port_phys_port_name_get (struct devlink_port*,char*,size_t) ; 
 struct devlink_port* netdev_to_devlink_port (struct net_device*) ; 

int devlink_compat_phys_port_name_get(struct net_device *dev,
				      char *name, size_t len)
{
	struct devlink_port *devlink_port;

	/* RTNL mutex is held here which ensures that devlink_port
	 * instance cannot disappear in the middle. No need to take
	 * any devlink lock as only permanent values are accessed.
	 */
	ASSERT_RTNL();

	devlink_port = netdev_to_devlink_port(dev);
	if (!devlink_port)
		return -EOPNOTSUPP;

	return __devlink_port_phys_port_name_get(devlink_port, name, len);
}