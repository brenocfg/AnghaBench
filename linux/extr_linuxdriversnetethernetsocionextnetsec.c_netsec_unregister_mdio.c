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
struct phy_device {int dummy; } ;
struct netsec_priv {int /*<<< orphan*/  mii_bus; int /*<<< orphan*/  dev; struct phy_device* phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_of_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_device_free (struct phy_device*) ; 
 int /*<<< orphan*/  phy_device_remove (struct phy_device*) ; 

__attribute__((used)) static void netsec_unregister_mdio(struct netsec_priv *priv)
{
	struct phy_device *phydev = priv->phydev;

	if (!dev_of_node(priv->dev) && phydev) {
		phy_device_remove(phydev);
		phy_device_free(phydev);
	}

	mdiobus_unregister(priv->mii_bus);
}