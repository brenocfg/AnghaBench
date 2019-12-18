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
struct net_device {scalar_t__ type; int /*<<< orphan*/  name; int /*<<< orphan*/  priv_flags; } ;
struct failover_ops {scalar_t__ type; int /*<<< orphan*/  name; int /*<<< orphan*/  priv_flags; } ;
struct failover {int /*<<< orphan*/  list; int /*<<< orphan*/  failover_dev; int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct failover* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IFF_FAILOVER ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  failover_existing_slave_register (struct net_device*) ; 
 int /*<<< orphan*/  failover_list ; 
 int /*<<< orphan*/  failover_lock ; 
 struct failover* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct failover *failover_register(struct net_device *dev,
				   struct failover_ops *ops)
{
	struct failover *failover;

	if (dev->type != ARPHRD_ETHER)
		return ERR_PTR(-EINVAL);

	failover = kzalloc(sizeof(*failover), GFP_KERNEL);
	if (!failover)
		return ERR_PTR(-ENOMEM);

	rcu_assign_pointer(failover->ops, ops);
	dev_hold(dev);
	dev->priv_flags |= IFF_FAILOVER;
	rcu_assign_pointer(failover->failover_dev, dev);

	spin_lock(&failover_lock);
	list_add_tail(&failover->list, &failover_list);
	spin_unlock(&failover_lock);

	netdev_info(dev, "failover master:%s registered\n", dev->name);

	failover_existing_slave_register(dev);

	return failover;
}