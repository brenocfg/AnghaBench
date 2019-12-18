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
typedef  scalar_t__ u16 ;
struct netdev_adjacent {scalar_t__ ref_nr; int /*<<< orphan*/  list; scalar_t__ master; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct net_device {scalar_t__ name; TYPE_1__ dev; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct netdev_adjacent* __netdev_find_adj (struct net_device*,struct list_head*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  kfree_rcu (struct netdev_adjacent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ netdev_adjacent_is_neigh_list (struct net_device*,struct net_device*,struct list_head*) ; 
 int /*<<< orphan*/  netdev_adjacent_sysfs_del (struct net_device*,scalar_t__,struct list_head*) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void __netdev_adjacent_dev_remove(struct net_device *dev,
					 struct net_device *adj_dev,
					 u16 ref_nr,
					 struct list_head *dev_list)
{
	struct netdev_adjacent *adj;

	pr_debug("Remove adjacency: dev %s adj_dev %s ref_nr %d\n",
		 dev->name, adj_dev->name, ref_nr);

	adj = __netdev_find_adj(adj_dev, dev_list);

	if (!adj) {
		pr_err("Adjacency does not exist for device %s from %s\n",
		       dev->name, adj_dev->name);
		WARN_ON(1);
		return;
	}

	if (adj->ref_nr > ref_nr) {
		pr_debug("adjacency: %s to %s ref_nr - %d = %d\n",
			 dev->name, adj_dev->name, ref_nr,
			 adj->ref_nr - ref_nr);
		adj->ref_nr -= ref_nr;
		return;
	}

	if (adj->master)
		sysfs_remove_link(&(dev->dev.kobj), "master");

	if (netdev_adjacent_is_neigh_list(dev, adj_dev, dev_list))
		netdev_adjacent_sysfs_del(dev, adj_dev->name, dev_list);

	list_del_rcu(&adj->list);
	pr_debug("adjacency: dev_put for %s, because link removed from %s to %s\n",
		 adj_dev->name, dev->name, adj_dev->name);
	dev_put(adj_dev);
	kfree_rcu(adj, rcu);
}