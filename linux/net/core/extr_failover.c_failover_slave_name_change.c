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
struct net_device {int /*<<< orphan*/  perm_addr; } ;
struct failover_ops {int /*<<< orphan*/  (* slave_name_change ) (struct net_device*,struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 struct net_device* failover_get_bymac (int /*<<< orphan*/ ,struct failover_ops**) ; 
 int /*<<< orphan*/  netif_is_failover_slave (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct net_device*) ; 

__attribute__((used)) static int failover_slave_name_change(struct net_device *slave_dev)
{
	struct net_device *failover_dev;
	struct failover_ops *fops;

	if (!netif_is_failover_slave(slave_dev))
		goto done;

	ASSERT_RTNL();

	failover_dev = failover_get_bymac(slave_dev->perm_addr, &fops);
	if (!failover_dev)
		goto done;

	if (!netif_running(failover_dev))
		goto done;

	if (fops && fops->slave_name_change &&
	    !fops->slave_name_change(slave_dev, failover_dev))
		return NOTIFY_OK;

done:
	return NOTIFY_DONE;
}