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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct dsa_switch {int /*<<< orphan*/  slave_mii_bus; } ;
struct dsa_port {int /*<<< orphan*/  pl; struct dsa_switch* ds; } ;

/* Variables and functions */
 int ENODEV ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int /*<<< orphan*/  mdiobus_get_phy (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 int phylink_connect_phy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_slave_phy_connect(struct net_device *slave_dev, int addr)
{
	struct dsa_port *dp = dsa_slave_to_port(slave_dev);
	struct dsa_switch *ds = dp->ds;

	slave_dev->phydev = mdiobus_get_phy(ds->slave_mii_bus, addr);
	if (!slave_dev->phydev) {
		netdev_err(slave_dev, "no phy at %d\n", addr);
		return -ENODEV;
	}

	return phylink_connect_phy(dp->pl, slave_dev->phydev);
}