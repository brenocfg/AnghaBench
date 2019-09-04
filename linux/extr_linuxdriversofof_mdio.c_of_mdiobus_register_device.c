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
typedef  int /*<<< orphan*/  u32 ;
struct mii_bus {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  fwnode; struct device_node* of_node; } ;
struct mdio_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mdio_device*) ; 
 int PTR_ERR (struct mdio_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct device_node*,int /*<<< orphan*/ ) ; 
 struct mdio_device* mdio_device_create (struct mii_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_device_free (struct mdio_device*) ; 
 int mdio_device_register (struct mdio_device*) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int of_mdiobus_register_device(struct mii_bus *mdio,
				      struct device_node *child, u32 addr)
{
	struct mdio_device *mdiodev;
	int rc;

	mdiodev = mdio_device_create(mdio, addr);
	if (IS_ERR(mdiodev))
		return PTR_ERR(mdiodev);

	/* Associate the OF node with the device structure so it
	 * can be looked up later.
	 */
	of_node_get(child);
	mdiodev->dev.of_node = child;
	mdiodev->dev.fwnode = of_fwnode_handle(child);

	/* All data is now stored in the mdiodev struct; register it. */
	rc = mdio_device_register(mdiodev);
	if (rc) {
		mdio_device_free(mdiodev);
		of_node_put(child);
		return rc;
	}

	dev_dbg(&mdio->dev, "registered mdio device %pOFn at address %i\n",
		child, addr);
	return 0;
}