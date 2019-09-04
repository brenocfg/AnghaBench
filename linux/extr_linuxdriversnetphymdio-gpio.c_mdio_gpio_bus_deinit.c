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
struct mii_bus {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct mii_bus* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  free_mdio_bitbang (struct mii_bus*) ; 

__attribute__((used)) static void mdio_gpio_bus_deinit(struct device *dev)
{
	struct mii_bus *bus = dev_get_drvdata(dev);

	free_mdio_bitbang(bus);
}