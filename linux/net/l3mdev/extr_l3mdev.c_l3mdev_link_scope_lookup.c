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
struct net_device {TYPE_1__* l3mdev_ops; } ;
struct net {int dummy; } ;
struct flowi6 {scalar_t__ flowi6_oif; } ;
struct dst_entry {int dummy; } ;
struct TYPE_2__ {struct dst_entry* (* l3mdev_link_scope_lookup ) (struct net_device*,struct flowi6*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct net_device* dev_get_by_index_rcu (struct net*,scalar_t__) ; 
 struct net_device* netdev_master_upper_dev_get_rcu (struct net_device*) ; 
 scalar_t__ netif_is_l3_master (struct net_device*) ; 
 scalar_t__ netif_is_l3_slave (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock_held () ; 
 struct dst_entry* stub1 (struct net_device*,struct flowi6*) ; 

struct dst_entry *l3mdev_link_scope_lookup(struct net *net,
					   struct flowi6 *fl6)
{
	struct dst_entry *dst = NULL;
	struct net_device *dev;

	WARN_ON_ONCE(!rcu_read_lock_held());
	if (fl6->flowi6_oif) {
		dev = dev_get_by_index_rcu(net, fl6->flowi6_oif);
		if (dev && netif_is_l3_slave(dev))
			dev = netdev_master_upper_dev_get_rcu(dev);

		if (dev && netif_is_l3_master(dev) &&
		    dev->l3mdev_ops->l3mdev_link_scope_lookup)
			dst = dev->l3mdev_ops->l3mdev_link_scope_lookup(dev, fl6);
	}

	return dst;
}