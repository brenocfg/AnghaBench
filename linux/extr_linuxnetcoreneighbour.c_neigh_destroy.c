#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {TYPE_1__* netdev_ops; } ;
struct neighbour {TYPE_2__* tbl; int /*<<< orphan*/  parms; scalar_t__ arp_queue_len_bytes; int /*<<< orphan*/  lock; int /*<<< orphan*/  arp_queue; int /*<<< orphan*/  dead; struct net_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  entries; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* ndo_neigh_destroy ) (struct net_device*,struct neighbour*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NEIGH_CACHE_STAT_INC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroys ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  kfree_rcu (struct neighbour*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_dbg (int,char*,struct neighbour*) ; 
 scalar_t__ neigh_del_timer (struct neighbour*) ; 
 int /*<<< orphan*/  neigh_parms_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct neighbour*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void neigh_destroy(struct neighbour *neigh)
{
	struct net_device *dev = neigh->dev;

	NEIGH_CACHE_STAT_INC(neigh->tbl, destroys);

	if (!neigh->dead) {
		pr_warn("Destroying alive neighbour %p\n", neigh);
		dump_stack();
		return;
	}

	if (neigh_del_timer(neigh))
		pr_warn("Impossible event\n");

	write_lock_bh(&neigh->lock);
	__skb_queue_purge(&neigh->arp_queue);
	write_unlock_bh(&neigh->lock);
	neigh->arp_queue_len_bytes = 0;

	if (dev->netdev_ops->ndo_neigh_destroy)
		dev->netdev_ops->ndo_neigh_destroy(dev, neigh);

	dev_put(dev);
	neigh_parms_put(neigh->parms);

	neigh_dbg(2, "neigh %p is destroyed\n", neigh);

	atomic_dec(&neigh->tbl->entries);
	kfree_rcu(neigh, rcu);
}