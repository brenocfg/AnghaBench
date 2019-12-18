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
struct dsa_port {int /*<<< orphan*/  pl; int /*<<< orphan*/  xmit_queue; int /*<<< orphan*/  xmit_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  phylink_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

int dsa_slave_suspend(struct net_device *slave_dev)
{
	struct dsa_port *dp = dsa_slave_to_port(slave_dev);

	if (!netif_running(slave_dev))
		return 0;

	cancel_work_sync(&dp->xmit_work);
	skb_queue_purge(&dp->xmit_queue);

	netif_device_detach(slave_dev);

	rtnl_lock();
	phylink_stop(dp->pl);
	rtnl_unlock();

	return 0;
}