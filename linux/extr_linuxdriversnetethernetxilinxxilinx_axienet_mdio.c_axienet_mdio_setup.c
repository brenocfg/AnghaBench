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
typedef  int u32 ;
struct resource {scalar_t__ start; } ;
struct mii_bus {char* name; int /*<<< orphan*/  parent; int /*<<< orphan*/  write; int /*<<< orphan*/  read; struct axienet_local* priv; int /*<<< orphan*/  id; } ;
struct device_node {int dummy; } ;
struct axienet_local {struct mii_bus* mii_bus; int /*<<< orphan*/  dev; int /*<<< orphan*/  phy_node; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int DEFAULT_CLOCK_DIVISOR ; 
 int ENOMEM ; 
 int MAX_MDIO_FREQ ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int XAE_MDIO_MC_MDIOEN_MASK ; 
 int /*<<< orphan*/  XAE_MDIO_MC_OFFSET ; 
 int /*<<< orphan*/  axienet_iow (struct axienet_local*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  axienet_mdio_read ; 
 int axienet_mdio_wait_until_ready (struct axienet_local*) ; 
 int /*<<< orphan*/  axienet_mdio_write ; 
 struct mii_bus* mdiobus_alloc () ; 
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 struct device_node* of_find_node_by_name (int /*<<< orphan*/ *,char*) ; 
 struct device_node* of_get_parent (int /*<<< orphan*/ ) ; 
 int of_mdiobus_register (struct mii_bus*,struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned long long) ; 

int axienet_mdio_setup(struct axienet_local *lp, struct device_node *np)
{
	int ret;
	u32 clk_div, host_clock;
	struct mii_bus *bus;
	struct resource res;
	struct device_node *np1;

	/* clk_div can be calculated by deriving it from the equation:
	 * fMDIO = fHOST / ((1 + clk_div) * 2)
	 *
	 * Where fMDIO <= 2500000, so we get:
	 * fHOST / ((1 + clk_div) * 2) <= 2500000
	 *
	 * Then we get:
	 * 1 / ((1 + clk_div) * 2) <= (2500000 / fHOST)
	 *
	 * Then we get:
	 * 1 / (1 + clk_div) <= ((2500000 * 2) / fHOST)
	 *
	 * Then we get:
	 * 1 / (1 + clk_div) <= (5000000 / fHOST)
	 *
	 * So:
	 * (1 + clk_div) >= (fHOST / 5000000)
	 *
	 * And finally:
	 * clk_div >= (fHOST / 5000000) - 1
	 *
	 * fHOST can be read from the flattened device tree as property
	 * "clock-frequency" from the CPU
	 */

	np1 = of_find_node_by_name(NULL, "cpu");
	if (!np1) {
		netdev_warn(lp->ndev, "Could not find CPU device node.\n");
		netdev_warn(lp->ndev,
			    "Setting MDIO clock divisor to default %d\n",
			    DEFAULT_CLOCK_DIVISOR);
		clk_div = DEFAULT_CLOCK_DIVISOR;
		goto issue;
	}
	if (of_property_read_u32(np1, "clock-frequency", &host_clock)) {
		netdev_warn(lp->ndev, "clock-frequency property not found.\n");
		netdev_warn(lp->ndev,
			    "Setting MDIO clock divisor to default %d\n",
			    DEFAULT_CLOCK_DIVISOR);
		clk_div = DEFAULT_CLOCK_DIVISOR;
		of_node_put(np1);
		goto issue;
	}

	clk_div = (host_clock / (MAX_MDIO_FREQ * 2)) - 1;
	/* If there is any remainder from the division of
	 * fHOST / (MAX_MDIO_FREQ * 2), then we need to add
	 * 1 to the clock divisor or we will surely be above 2.5 MHz
	 */
	if (host_clock % (MAX_MDIO_FREQ * 2))
		clk_div++;

	netdev_dbg(lp->ndev,
		   "Setting MDIO clock divisor to %u/%u Hz host clock.\n",
		   clk_div, host_clock);

	of_node_put(np1);
issue:
	axienet_iow(lp, XAE_MDIO_MC_OFFSET,
		    (((u32) clk_div) | XAE_MDIO_MC_MDIOEN_MASK));

	ret = axienet_mdio_wait_until_ready(lp);
	if (ret < 0)
		return ret;

	bus = mdiobus_alloc();
	if (!bus)
		return -ENOMEM;

	np1 = of_get_parent(lp->phy_node);
	of_address_to_resource(np1, 0, &res);
	snprintf(bus->id, MII_BUS_ID_SIZE, "%.8llx",
		 (unsigned long long) res.start);

	bus->priv = lp;
	bus->name = "Xilinx Axi Ethernet MDIO";
	bus->read = axienet_mdio_read;
	bus->write = axienet_mdio_write;
	bus->parent = lp->dev;
	lp->mii_bus = bus;

	ret = of_mdiobus_register(bus, np1);
	if (ret) {
		mdiobus_free(bus);
		lp->mii_bus = NULL;
		return ret;
	}
	return 0;
}