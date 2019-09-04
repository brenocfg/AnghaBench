#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* of_node; } ;
struct mdio_device {struct gpio_desc* reset; TYPE_2__ dev; } ;
struct gpio_desc {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 struct gpio_desc* fwnode_get_named_gpiod (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdio_device_reset (struct mdio_device*,int) ; 

__attribute__((used)) static int mdiobus_register_gpiod(struct mdio_device *mdiodev)
{
	struct gpio_desc *gpiod = NULL;

	/* Deassert the optional reset signal */
	if (mdiodev->dev.of_node)
		gpiod = fwnode_get_named_gpiod(&mdiodev->dev.of_node->fwnode,
					       "reset-gpios", 0, GPIOD_OUT_LOW,
					       "PHY reset");
	if (PTR_ERR(gpiod) == -ENOENT ||
	    PTR_ERR(gpiod) == -ENOSYS)
		gpiod = NULL;
	else if (IS_ERR(gpiod))
		return PTR_ERR(gpiod);

	mdiodev->reset = gpiod;

	/* Assert the reset signal again */
	mdio_device_reset(mdiodev, 1);

	return 0;
}