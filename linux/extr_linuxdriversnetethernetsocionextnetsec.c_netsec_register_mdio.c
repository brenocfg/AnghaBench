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
typedef  int /*<<< orphan*/  u32 ;
struct netsec_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/ * phydev; struct mii_bus* mii_bus; } ;
struct mii_bus {char* name; int /*<<< orphan*/  phy_mask; int /*<<< orphan*/  parent; int /*<<< orphan*/  write; int /*<<< orphan*/  read; struct netsec_priv* priv; int /*<<< orphan*/  id; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 struct device_node* dev_of_node (int /*<<< orphan*/ ) ; 
 struct mii_bus* devm_mdiobus_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_phy_device (struct mii_bus*,int /*<<< orphan*/ ,int) ; 
 int mdiobus_register (struct mii_bus*) ; 
 int /*<<< orphan*/  mdiobus_unregister (struct mii_bus*) ; 
 int /*<<< orphan*/  netsec_phy_read ; 
 int /*<<< orphan*/  netsec_phy_write ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int of_mdiobus_register (struct mii_bus*,struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int phy_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int netsec_register_mdio(struct netsec_priv *priv, u32 phy_addr)
{
	struct mii_bus *bus;
	int ret;

	bus = devm_mdiobus_alloc(priv->dev);
	if (!bus)
		return -ENOMEM;

	snprintf(bus->id, MII_BUS_ID_SIZE, "%s", dev_name(priv->dev));
	bus->priv = priv;
	bus->name = "SNI NETSEC MDIO";
	bus->read = netsec_phy_read;
	bus->write = netsec_phy_write;
	bus->parent = priv->dev;
	priv->mii_bus = bus;

	if (dev_of_node(priv->dev)) {
		struct device_node *mdio_node, *parent = dev_of_node(priv->dev);

		mdio_node = of_get_child_by_name(parent, "mdio");
		if (mdio_node) {
			parent = mdio_node;
		} else {
			/* older f/w doesn't populate the mdio subnode,
			 * allow relaxed upgrade of f/w in due time.
			 */
			dev_info(priv->dev, "Upgrade f/w for mdio subnode!\n");
		}

		ret = of_mdiobus_register(bus, parent);
		of_node_put(mdio_node);

		if (ret) {
			dev_err(priv->dev, "mdiobus register err(%d)\n", ret);
			return ret;
		}
	} else {
		/* Mask out all PHYs from auto probing. */
		bus->phy_mask = ~0;
		ret = mdiobus_register(bus);
		if (ret) {
			dev_err(priv->dev, "mdiobus register err(%d)\n", ret);
			return ret;
		}

		priv->phydev = get_phy_device(bus, phy_addr, false);
		if (IS_ERR(priv->phydev)) {
			ret = PTR_ERR(priv->phydev);
			dev_err(priv->dev, "get_phy_device err(%d)\n", ret);
			priv->phydev = NULL;
			return -ENODEV;
		}

		ret = phy_device_register(priv->phydev);
		if (ret) {
			mdiobus_unregister(bus);
			dev_err(priv->dev,
				"phy_device_register err(%d)\n", ret);
		}
	}

	return ret;
}