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
struct dsa_slave_priv {int /*<<< orphan*/  stats64; } ;
struct dsa_port {int /*<<< orphan*/  pl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_PORT_UNREGISTER ; 
 int /*<<< orphan*/  dsa_slave_notify (struct net_device*,int /*<<< orphan*/ ) ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 struct dsa_slave_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  phylink_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_disconnect_phy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

void dsa_slave_destroy(struct net_device *slave_dev)
{
	struct dsa_port *dp = dsa_slave_to_port(slave_dev);
	struct dsa_slave_priv *p = netdev_priv(slave_dev);

	netif_carrier_off(slave_dev);
	rtnl_lock();
	phylink_disconnect_phy(dp->pl);
	rtnl_unlock();

	dsa_slave_notify(slave_dev, DSA_PORT_UNREGISTER);
	unregister_netdev(slave_dev);
	phylink_destroy(dp->pl);
	free_percpu(p->stats64);
	free_netdev(slave_dev);
}