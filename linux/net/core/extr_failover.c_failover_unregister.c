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
struct net_device {int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  name; } ;
struct failover {int /*<<< orphan*/  list; int /*<<< orphan*/  failover_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_FAILOVER ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  failover_lock ; 
 int /*<<< orphan*/  kfree (struct failover*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct net_device* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void failover_unregister(struct failover *failover)
{
	struct net_device *failover_dev;

	failover_dev = rcu_dereference(failover->failover_dev);

	netdev_info(failover_dev, "failover master:%s unregistered\n",
		    failover_dev->name);

	failover_dev->priv_flags &= ~IFF_FAILOVER;
	dev_put(failover_dev);

	spin_lock(&failover_lock);
	list_del(&failover->list);
	spin_unlock(&failover_lock);

	kfree(failover);
}