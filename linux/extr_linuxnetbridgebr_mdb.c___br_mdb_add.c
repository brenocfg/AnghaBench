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
struct net_bridge_port {scalar_t__ state; struct net_bridge* br; } ;
struct net_bridge {int /*<<< orphan*/  multicast_lock; scalar_t__ multicast_disabled; int /*<<< orphan*/  dev; } ;
struct net {int dummy; } ;
struct br_mdb_entry {int /*<<< orphan*/  state; int /*<<< orphan*/  ifindex; } ;
struct br_ip {int dummy; } ;

/* Variables and functions */
 scalar_t__ BR_STATE_DISABLED ; 
 int EINVAL ; 
 int ENODEV ; 
 struct net_device* __dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mdb_entry_to_br_ip (struct br_mdb_entry*,struct br_ip*) ; 
 int br_mdb_add_group (struct net_bridge*,struct net_bridge_port*,struct br_ip*,int /*<<< orphan*/ ) ; 
 struct net_bridge_port* br_port_get_rtnl (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __br_mdb_add(struct net *net, struct net_bridge *br,
			struct br_mdb_entry *entry)
{
	struct br_ip ip;
	struct net_device *dev;
	struct net_bridge_port *p;
	int ret;

	if (!netif_running(br->dev) || br->multicast_disabled)
		return -EINVAL;

	dev = __dev_get_by_index(net, entry->ifindex);
	if (!dev)
		return -ENODEV;

	p = br_port_get_rtnl(dev);
	if (!p || p->br != br || p->state == BR_STATE_DISABLED)
		return -EINVAL;

	__mdb_entry_to_br_ip(entry, &ip);

	spin_lock_bh(&br->multicast_lock);
	ret = br_mdb_add_group(br, p, &ip, entry->state);
	spin_unlock_bh(&br->multicast_lock);
	return ret;
}