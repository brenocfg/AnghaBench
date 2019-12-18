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
struct notifier_block {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct netdev_notifier_pre_changeaddr_info {int /*<<< orphan*/  dev_addr; } ;
struct net_device {int priv_flags; int /*<<< orphan*/  dev_addr; } ;
struct net_bridge_port {struct net_bridge* br; } ;
struct net_bridge {TYPE_1__* dev; int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  addr_assign_type; } ;

/* Variables and functions */
 int IFF_EBRIDGE ; 
 int IFF_UP ; 
#define  NETDEV_CHANGE 138 
#define  NETDEV_CHANGEADDR 137 
#define  NETDEV_CHANGEMTU 136 
#define  NETDEV_CHANGENAME 135 
#define  NETDEV_DOWN 134 
#define  NETDEV_FEAT_CHANGE 133 
#define  NETDEV_PRE_CHANGEADDR 132 
#define  NETDEV_PRE_TYPE_CHANGE 131 
 unsigned long NETDEV_REGISTER ; 
#define  NETDEV_RESEND_IGMP 130 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int /*<<< orphan*/  NET_ADDR_SET ; 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  RTM_NEWLINK ; 
 int /*<<< orphan*/  br_del_if (struct net_bridge*,struct net_device*) ; 
 int /*<<< orphan*/  br_fdb_changeaddr (struct net_bridge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_ifinfo_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_mtu_auto_adjust (struct net_bridge*) ; 
 int /*<<< orphan*/  br_port_carrier_check (struct net_bridge_port*,int*) ; 
 struct net_bridge_port* br_port_get_rtnl (struct net_device*) ; 
 int /*<<< orphan*/  br_stp_disable_port (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_stp_enable_port (struct net_bridge_port*) ; 
 int br_stp_recalculate_bridge_id (struct net_bridge*) ; 
 int /*<<< orphan*/  br_sysfs_addbr (struct net_device*) ; 
 int br_sysfs_renameif (struct net_bridge_port*) ; 
 int br_vlan_bridge_event (struct net_device*,unsigned long,void*) ; 
 int /*<<< orphan*/  br_vlan_port_event (struct net_bridge_port*,unsigned long) ; 
 int /*<<< orphan*/  call_netdevice_notifiers (int const,TYPE_1__*) ; 
 int dev_pre_changeaddr_notify (TYPE_1__*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 struct netlink_ext_ack* netdev_notifier_info_to_extack (void*) ; 
 int /*<<< orphan*/  netdev_update_features (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_oper_up (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (TYPE_1__*) ; 
 int notifier_from_errno (int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int br_device_event(struct notifier_block *unused, unsigned long event, void *ptr)
{
	struct netlink_ext_ack *extack = netdev_notifier_info_to_extack(ptr);
	struct netdev_notifier_pre_changeaddr_info *prechaddr_info;
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct net_bridge_port *p;
	struct net_bridge *br;
	bool notified = false;
	bool changed_addr;
	int err;

	if (dev->priv_flags & IFF_EBRIDGE) {
		err = br_vlan_bridge_event(dev, event, ptr);
		if (err)
			return notifier_from_errno(err);

		if (event == NETDEV_REGISTER) {
			/* register of bridge completed, add sysfs entries */
			br_sysfs_addbr(dev);
			return NOTIFY_DONE;
		}
	}

	/* not a port of a bridge */
	p = br_port_get_rtnl(dev);
	if (!p)
		return NOTIFY_DONE;

	br = p->br;

	switch (event) {
	case NETDEV_CHANGEMTU:
		br_mtu_auto_adjust(br);
		break;

	case NETDEV_PRE_CHANGEADDR:
		if (br->dev->addr_assign_type == NET_ADDR_SET)
			break;
		prechaddr_info = ptr;
		err = dev_pre_changeaddr_notify(br->dev,
						prechaddr_info->dev_addr,
						extack);
		if (err)
			return notifier_from_errno(err);
		break;

	case NETDEV_CHANGEADDR:
		spin_lock_bh(&br->lock);
		br_fdb_changeaddr(p, dev->dev_addr);
		changed_addr = br_stp_recalculate_bridge_id(br);
		spin_unlock_bh(&br->lock);

		if (changed_addr)
			call_netdevice_notifiers(NETDEV_CHANGEADDR, br->dev);

		break;

	case NETDEV_CHANGE:
		br_port_carrier_check(p, &notified);
		break;

	case NETDEV_FEAT_CHANGE:
		netdev_update_features(br->dev);
		break;

	case NETDEV_DOWN:
		spin_lock_bh(&br->lock);
		if (br->dev->flags & IFF_UP) {
			br_stp_disable_port(p);
			notified = true;
		}
		spin_unlock_bh(&br->lock);
		break;

	case NETDEV_UP:
		if (netif_running(br->dev) && netif_oper_up(dev)) {
			spin_lock_bh(&br->lock);
			br_stp_enable_port(p);
			notified = true;
			spin_unlock_bh(&br->lock);
		}
		break;

	case NETDEV_UNREGISTER:
		br_del_if(br, dev);
		break;

	case NETDEV_CHANGENAME:
		err = br_sysfs_renameif(p);
		if (err)
			return notifier_from_errno(err);
		break;

	case NETDEV_PRE_TYPE_CHANGE:
		/* Forbid underlaying device to change its type. */
		return NOTIFY_BAD;

	case NETDEV_RESEND_IGMP:
		/* Propagate to master device */
		call_netdevice_notifiers(event, br->dev);
		break;
	}

	if (event != NETDEV_UNREGISTER)
		br_vlan_port_event(p, event);

	/* Events that may cause spanning tree to refresh */
	if (!notified && (event == NETDEV_CHANGEADDR || event == NETDEV_UP ||
			  event == NETDEV_CHANGE || event == NETDEV_DOWN))
		br_ifinfo_notify(RTM_NEWLINK, NULL, p);

	return NOTIFY_DONE;
}