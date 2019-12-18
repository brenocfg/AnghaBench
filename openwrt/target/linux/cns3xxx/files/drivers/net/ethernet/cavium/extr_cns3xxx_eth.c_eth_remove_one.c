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
struct sw {int dummy; } ;
struct port {int /*<<< orphan*/  phydev; struct net_device* netdev; } ;
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cns3xxx_mdio_remove () ; 
 int /*<<< orphan*/  destroy_rings (struct sw*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct net_device* napi_dev ; 
 struct sw* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ ) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 struct port** switch_port_tab ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int eth_remove_one(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);
	struct sw *sw = netdev_priv(dev);
	int i;

	destroy_rings(sw);
	for (i = 3; i >= 0; i--) {
		if (switch_port_tab[i]) {
			struct port *port = switch_port_tab[i];
			struct net_device *dev = port->netdev;
			unregister_netdev(dev);
			phy_disconnect(port->phydev);
			switch_port_tab[i] = 0;
			free_netdev(dev);
		}
	}

	free_netdev(napi_dev);
	cns3xxx_mdio_remove();

	return 0;
}