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
struct net_device_ops {scalar_t__ (* ndo_neigh_setup ) (struct net_device*,struct neigh_parms*) ;} ;
struct net_device {struct net_device_ops* netdev_ops; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct neigh_table {int /*<<< orphan*/  lock; TYPE_1__ parms; } ;
struct neigh_parms {int /*<<< orphan*/  list; int /*<<< orphan*/ * sysctl_table; int /*<<< orphan*/  net; struct net_device* dev; int /*<<< orphan*/  reachable_time; int /*<<< orphan*/  refcnt; struct neigh_table* tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASE_REACHABLE_TIME ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NEIGH_VAR (struct neigh_parms*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct neigh_parms*) ; 
 struct neigh_parms* kmemdup (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neigh_parms_data_state_cleanall (struct neigh_parms*) ; 
 int /*<<< orphan*/  neigh_rand_reach_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ stub1 (struct net_device*,struct neigh_parms*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_pnet (int /*<<< orphan*/ *,struct net*) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

struct neigh_parms *neigh_parms_alloc(struct net_device *dev,
				      struct neigh_table *tbl)
{
	struct neigh_parms *p;
	struct net *net = dev_net(dev);
	const struct net_device_ops *ops = dev->netdev_ops;

	p = kmemdup(&tbl->parms, sizeof(*p), GFP_KERNEL);
	if (p) {
		p->tbl		  = tbl;
		refcount_set(&p->refcnt, 1);
		p->reachable_time =
				neigh_rand_reach_time(NEIGH_VAR(p, BASE_REACHABLE_TIME));
		dev_hold(dev);
		p->dev = dev;
		write_pnet(&p->net, net);
		p->sysctl_table = NULL;

		if (ops->ndo_neigh_setup && ops->ndo_neigh_setup(dev, p)) {
			dev_put(dev);
			kfree(p);
			return NULL;
		}

		write_lock_bh(&tbl->lock);
		list_add(&p->list, &tbl->parms.list);
		write_unlock_bh(&tbl->lock);

		neigh_parms_data_state_cleanall(p);
	}
	return p;
}