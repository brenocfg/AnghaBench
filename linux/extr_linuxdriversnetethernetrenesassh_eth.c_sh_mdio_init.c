#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sh_eth_private {TYPE_1__* mii_bus; scalar_t__* reg_offset; scalar_t__ addr; struct platform_device* pdev; } ;
struct sh_eth_plat_data {scalar_t__ phy_irq; size_t phy; int /*<<< orphan*/  set_mdio_gate; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {char* name; int id; struct device dev; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ops; } ;
struct bb_info {TYPE_4__ ctrl; int /*<<< orphan*/  set_gate; scalar_t__ addr; } ;
struct TYPE_5__ {char* name; scalar_t__* irq; int /*<<< orphan*/  id; struct device* parent; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 size_t PIR ; 
 TYPE_1__* alloc_mdio_bitbang (TYPE_4__*) ; 
 int /*<<< orphan*/  bb_ops ; 
 struct bb_info* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_mdio_bitbang (TYPE_1__*) ; 
 int of_mdiobus_register (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static int sh_mdio_init(struct sh_eth_private *mdp,
			struct sh_eth_plat_data *pd)
{
	int ret;
	struct bb_info *bitbang;
	struct platform_device *pdev = mdp->pdev;
	struct device *dev = &mdp->pdev->dev;

	/* create bit control struct for PHY */
	bitbang = devm_kzalloc(dev, sizeof(struct bb_info), GFP_KERNEL);
	if (!bitbang)
		return -ENOMEM;

	/* bitbang init */
	bitbang->addr = mdp->addr + mdp->reg_offset[PIR];
	bitbang->set_gate = pd->set_mdio_gate;
	bitbang->ctrl.ops = &bb_ops;

	/* MII controller setting */
	mdp->mii_bus = alloc_mdio_bitbang(&bitbang->ctrl);
	if (!mdp->mii_bus)
		return -ENOMEM;

	/* Hook up MII support for ethtool */
	mdp->mii_bus->name = "sh_mii";
	mdp->mii_bus->parent = dev;
	snprintf(mdp->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		 pdev->name, pdev->id);

	/* register MDIO bus */
	if (pd->phy_irq > 0)
		mdp->mii_bus->irq[pd->phy] = pd->phy_irq;

	ret = of_mdiobus_register(mdp->mii_bus, dev->of_node);
	if (ret)
		goto out_free_bus;

	return 0;

out_free_bus:
	free_mdio_bitbang(mdp->mii_bus);
	return ret;
}