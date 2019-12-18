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
struct net_bridge_port {struct net_bridge* br; } ;
struct net_bridge {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NETDEV_CHANGEADDR ; 
 int /*<<< orphan*/  br_mtu_auto_adjust (struct net_bridge*) ; 
 struct net_bridge_port* br_port_get_rtnl (struct net_device*) ; 
 int /*<<< orphan*/  br_set_gso_limits (struct net_bridge*) ; 
 int br_stp_recalculate_bridge_id (struct net_bridge*) ; 
 int /*<<< orphan*/  call_netdevice_notifiers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_nbp (struct net_bridge_port*) ; 
 int /*<<< orphan*/  netdev_update_features (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int br_del_if(struct net_bridge *br, struct net_device *dev)
{
	struct net_bridge_port *p;
	bool changed_addr;

	p = br_port_get_rtnl(dev);
	if (!p || p->br != br)
		return -EINVAL;

	/* Since more than one interface can be attached to a bridge,
	 * there still maybe an alternate path for netconsole to use;
	 * therefore there is no reason for a NETDEV_RELEASE event.
	 */
	del_nbp(p);

	br_mtu_auto_adjust(br);
	br_set_gso_limits(br);

	spin_lock_bh(&br->lock);
	changed_addr = br_stp_recalculate_bridge_id(br);
	spin_unlock_bh(&br->lock);

	if (changed_addr)
		call_netdevice_notifiers(NETDEV_CHANGEADDR, br->dev);

	netdev_update_features(br->dev);

	return 0;
}