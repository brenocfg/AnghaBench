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
struct net_device {int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  name; } ;
struct net_bridge_port {int /*<<< orphan*/  rcu; int /*<<< orphan*/  kobj; int /*<<< orphan*/  list; struct net_device* dev; struct net_bridge* br; } ;
struct net_bridge {TYPE_1__* dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  ifobj; } ;
struct TYPE_2__ {scalar_t__ needed_headroom; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_BRIDGE_PORT ; 
 int /*<<< orphan*/  KOBJ_REMOVE ; 
 int /*<<< orphan*/  RTM_DELLINK ; 
 int /*<<< orphan*/  br_fdb_delete_by_port (struct net_bridge*,struct net_bridge_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  br_ifinfo_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_multicast_del_port (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_netpoll_disable (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_stp_disable_port (struct net_bridge_port*) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_nbp_rcu ; 
 int /*<<< orphan*/  get_max_headroom (struct net_bridge*) ; 
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nbp_backup_clear (struct net_bridge_port*) ; 
 int /*<<< orphan*/  nbp_delete_promisc (struct net_bridge_port*) ; 
 int /*<<< orphan*/  nbp_update_port_count (struct net_bridge*) ; 
 int /*<<< orphan*/  nbp_vlan_flush (struct net_bridge_port*) ; 
 scalar_t__ netdev_get_fwd_headroom (struct net_device*) ; 
 int /*<<< orphan*/  netdev_reset_rx_headroom (struct net_device*) ; 
 int /*<<< orphan*/  netdev_rx_handler_unregister (struct net_device*) ; 
 int /*<<< orphan*/  netdev_upper_dev_unlink (struct net_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  switchdev_deferred_process () ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_headroom (struct net_bridge*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void del_nbp(struct net_bridge_port *p)
{
	struct net_bridge *br = p->br;
	struct net_device *dev = p->dev;

	sysfs_remove_link(br->ifobj, p->dev->name);

	nbp_delete_promisc(p);

	spin_lock_bh(&br->lock);
	br_stp_disable_port(p);
	spin_unlock_bh(&br->lock);

	br_ifinfo_notify(RTM_DELLINK, NULL, p);

	list_del_rcu(&p->list);
	if (netdev_get_fwd_headroom(dev) == br->dev->needed_headroom)
		update_headroom(br, get_max_headroom(br));
	netdev_reset_rx_headroom(dev);

	nbp_vlan_flush(p);
	br_fdb_delete_by_port(br, p, 0, 1);
	switchdev_deferred_process();
	nbp_backup_clear(p);

	nbp_update_port_count(br);

	netdev_upper_dev_unlink(dev, br->dev);

	dev->priv_flags &= ~IFF_BRIDGE_PORT;

	netdev_rx_handler_unregister(dev);

	br_multicast_del_port(p);

	kobject_uevent(&p->kobj, KOBJ_REMOVE);
	kobject_del(&p->kobj);

	br_netpoll_disable(p);

	call_rcu(&p->rcu, destroy_nbp_rcu);
}