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
struct dsa_port {int /*<<< orphan*/  pl; } ;

/* Variables and functions */
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  phylink_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int dsa_slave_resume(struct net_device *slave_dev)
{
	struct dsa_port *dp = dsa_slave_to_port(slave_dev);

	if (!netif_running(slave_dev))
		return 0;

	netif_device_attach(slave_dev);

	rtnl_lock();
	phylink_start(dp->pl);
	rtnl_unlock();

	return 0;
}