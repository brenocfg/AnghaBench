#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rtl8169_private {struct mii_bus* mii_bus; struct pci_dev* pci_dev; } ;
struct phy_device {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; int /*<<< orphan*/  dev; } ;
struct mii_bus {char* name; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  id; int /*<<< orphan*/ * irq; int /*<<< orphan*/ * parent; struct rtl8169_private* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int PCI_DEVID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_IGNORE_INTERRUPT ; 
 struct mii_bus* devm_mdiobus_alloc (int /*<<< orphan*/ *) ; 
 struct phy_device* mdiobus_get_phy (struct mii_bus*,int /*<<< orphan*/ ) ; 
 int mdiobus_register (struct mii_bus*) ; 
 int /*<<< orphan*/  mdiobus_unregister (struct mii_bus*) ; 
 int /*<<< orphan*/  phy_suspend (struct phy_device*) ; 
 int /*<<< orphan*/  r8169_mdio_read_reg ; 
 int /*<<< orphan*/  r8169_mdio_write_reg ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int r8169_mdio_register(struct rtl8169_private *tp)
{
	struct pci_dev *pdev = tp->pci_dev;
	struct phy_device *phydev;
	struct mii_bus *new_bus;
	int ret;

	new_bus = devm_mdiobus_alloc(&pdev->dev);
	if (!new_bus)
		return -ENOMEM;

	new_bus->name = "r8169";
	new_bus->priv = tp;
	new_bus->parent = &pdev->dev;
	new_bus->irq[0] = PHY_IGNORE_INTERRUPT;
	snprintf(new_bus->id, MII_BUS_ID_SIZE, "r8169-%x",
		 PCI_DEVID(pdev->bus->number, pdev->devfn));

	new_bus->read = r8169_mdio_read_reg;
	new_bus->write = r8169_mdio_write_reg;

	ret = mdiobus_register(new_bus);
	if (ret)
		return ret;

	phydev = mdiobus_get_phy(new_bus, 0);
	if (!phydev) {
		mdiobus_unregister(new_bus);
		return -ENODEV;
	}

	/* PHY will be woken up in rtl_open() */
	phy_suspend(phydev);

	tp->mii_bus = new_bus;

	return 0;
}