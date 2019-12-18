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
struct netdev_phys_item_id {int dummy; } ;
struct net_device_ops {int (* ndo_get_phys_port_name ) (struct net_device*,char*,int) ;int (* ndo_get_port_parent_id ) (struct net_device*,struct netdev_phys_item_id*) ;} ;
struct net_device {struct net_device_ops* netdev_ops; } ;
struct devlink_port {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_PORT_TYPE_ETH ; 
 int EOPNOTSUPP ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __devlink_port_type_set (struct devlink_port*,int /*<<< orphan*/ ,struct net_device*) ; 
 int stub1 (struct net_device*,char*,int) ; 
 int stub2 (struct net_device*,struct netdev_phys_item_id*) ; 

void devlink_port_type_eth_set(struct devlink_port *devlink_port,
			       struct net_device *netdev)
{
	const struct net_device_ops *ops = netdev->netdev_ops;

	/* If driver registers devlink port, it should set devlink port
	 * attributes accordingly so the compat functions are called
	 * and the original ops are not used.
	 */
	if (ops->ndo_get_phys_port_name) {
		/* Some drivers use the same set of ndos for netdevs
		 * that have devlink_port registered and also for
		 * those who don't. Make sure that ndo_get_phys_port_name
		 * returns -EOPNOTSUPP here in case it is defined.
		 * Warn if not.
		 */
		char name[IFNAMSIZ];
		int err;

		err = ops->ndo_get_phys_port_name(netdev, name, sizeof(name));
		WARN_ON(err != -EOPNOTSUPP);
	}
	if (ops->ndo_get_port_parent_id) {
		/* Some drivers use the same set of ndos for netdevs
		 * that have devlink_port registered and also for
		 * those who don't. Make sure that ndo_get_port_parent_id
		 * returns -EOPNOTSUPP here in case it is defined.
		 * Warn if not.
		 */
		struct netdev_phys_item_id ppid;
		int err;

		err = ops->ndo_get_port_parent_id(netdev, &ppid);
		WARN_ON(err != -EOPNOTSUPP);
	}
	__devlink_port_type_set(devlink_port, DEVLINK_PORT_TYPE_ETH, netdev);
}