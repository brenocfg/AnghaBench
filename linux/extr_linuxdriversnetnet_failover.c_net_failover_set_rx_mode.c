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
struct net_failover_info {int /*<<< orphan*/  standby_dev; int /*<<< orphan*/  primary_dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_mc_sync_multiple (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  dev_uc_sync_multiple (struct net_device*,struct net_device*) ; 
 struct net_failover_info* netdev_priv (struct net_device*) ; 
 struct net_device* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void net_failover_set_rx_mode(struct net_device *dev)
{
	struct net_failover_info *nfo_info = netdev_priv(dev);
	struct net_device *slave_dev;

	rcu_read_lock();

	slave_dev = rcu_dereference(nfo_info->primary_dev);
	if (slave_dev) {
		dev_uc_sync_multiple(slave_dev, dev);
		dev_mc_sync_multiple(slave_dev, dev);
	}

	slave_dev = rcu_dereference(nfo_info->standby_dev);
	if (slave_dev) {
		dev_uc_sync_multiple(slave_dev, dev);
		dev_mc_sync_multiple(slave_dev, dev);
	}

	rcu_read_unlock();
}