#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {int id; TYPE_1__ dev; } ;
struct mii_bus {int dummy; } ;
struct mdio_gpio_info {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 struct mdio_gpio_info* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_gpio_bus_deinit (TYPE_1__*) ; 
 struct mii_bus* mdio_gpio_bus_init (TYPE_1__*,struct mdio_gpio_info*,int) ; 
 int mdio_gpio_get_data (TYPE_1__*,struct mdio_gpio_info*) ; 
 int of_alias_get_id (int /*<<< orphan*/ ,char*) ; 
 int of_mdiobus_register (struct mii_bus*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdio_gpio_probe(struct platform_device *pdev)
{
	struct mdio_gpio_info *bitbang;
	struct mii_bus *new_bus;
	int ret, bus_id;

	bitbang = devm_kzalloc(&pdev->dev, sizeof(*bitbang), GFP_KERNEL);
	if (!bitbang)
		return -ENOMEM;

	ret = mdio_gpio_get_data(&pdev->dev, bitbang);
	if (ret)
		return ret;

	if (pdev->dev.of_node) {
		bus_id = of_alias_get_id(pdev->dev.of_node, "mdio-gpio");
		if (bus_id < 0) {
			dev_warn(&pdev->dev, "failed to get alias id\n");
			bus_id = 0;
		}
	} else {
		bus_id = pdev->id;
	}

	new_bus = mdio_gpio_bus_init(&pdev->dev, bitbang, bus_id);
	if (!new_bus)
		return -ENODEV;

	ret = of_mdiobus_register(new_bus, pdev->dev.of_node);
	if (ret)
		mdio_gpio_bus_deinit(&pdev->dev);

	return ret;
}