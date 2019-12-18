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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct mii_bus {char* name; int /*<<< orphan*/ * irq; scalar_t__ phy_mask; int /*<<< orphan*/  id; struct device* parent; struct ag71xx_mdio* priv; int /*<<< orphan*/  reset; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct device_node {char* name; } ;
struct ag71xx_mdio {struct mii_bus* mii_bus; int /*<<< orphan*/  mdio_reset; int /*<<< orphan*/  mii_regmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int PHY_MAX_ADDR ; 
 int /*<<< orphan*/  PHY_POLL ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ag71xx_mdio_mii_read ; 
 int /*<<< orphan*/  ag71xx_mdio_mii_write ; 
 int /*<<< orphan*/  ag71xx_mdio_reset ; 
 int /*<<< orphan*/  bus_count ; 
 struct ag71xx_mdio* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct mii_bus* devm_mdiobus_alloc (struct device*) ; 
 int /*<<< orphan*/  devm_reset_control_get_exclusive (struct device*,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int of_mdiobus_register (struct mii_bus*,struct device_node*) ; 
 int of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ag71xx_mdio*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int ag71xx_mdio_probe(struct platform_device *pdev)
{
	struct device *amdev = &pdev->dev;
	struct device_node *np = pdev->dev.of_node;
	struct ag71xx_mdio *am;
	struct mii_bus *mii_bus;
	bool builtin_switch;
	int i, err;

	am = devm_kzalloc(amdev, sizeof(*am), GFP_KERNEL);
	if (!am)
		return -ENOMEM;

	am->mii_regmap = syscon_regmap_lookup_by_phandle(np, "regmap");
	if (IS_ERR(am->mii_regmap))
		return PTR_ERR(am->mii_regmap);

	mii_bus = devm_mdiobus_alloc(amdev);
	if (!mii_bus)
		return -ENOMEM;

	am->mdio_reset = devm_reset_control_get_exclusive(amdev, "mdio");
	builtin_switch = of_property_read_bool(np, "builtin-switch");

	mii_bus->name = "ag71xx_mdio";
	mii_bus->read = ag71xx_mdio_mii_read;
	mii_bus->write = ag71xx_mdio_mii_write;
	mii_bus->reset = ag71xx_mdio_reset;
	mii_bus->priv = am;
	mii_bus->parent = amdev;
	snprintf(mii_bus->id, MII_BUS_ID_SIZE, "%s.%d", np->name, bus_count++);

	if (!builtin_switch &&
	    of_property_read_u32(np, "phy-mask", &mii_bus->phy_mask))
		mii_bus->phy_mask = 0;

	for (i = 0; i < PHY_MAX_ADDR; i++)
		mii_bus->irq[i] = PHY_POLL;

	if (!IS_ERR(am->mdio_reset)) {
		reset_control_assert(am->mdio_reset);
		msleep(100);
		reset_control_deassert(am->mdio_reset);
		msleep(200);
	}

	err = of_mdiobus_register(mii_bus, np);
	if (err)
		return err;

	am->mii_bus = mii_bus;
	platform_set_drvdata(pdev, am);

	return 0;
}