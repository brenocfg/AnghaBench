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
struct mii_bus {int dummy; } ;
struct TYPE_2__ {void* platform_data; } ;
struct mdio_device {TYPE_1__ dev; int /*<<< orphan*/  bus_match; int /*<<< orphan*/  modalias; } ;
struct mdio_board_info {scalar_t__ platform_data; int /*<<< orphan*/  modalias; int /*<<< orphan*/  mdio_addr; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct mdio_device*) ; 
 int /*<<< orphan*/  mdio_device_bus_match ; 
 struct mdio_device* mdio_device_create (struct mii_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_device_free (struct mdio_device*) ; 
 int mdio_device_register (struct mdio_device*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mdiobus_create_device(struct mii_bus *bus,
				 struct mdio_board_info *bi)
{
	struct mdio_device *mdiodev;
	int ret = 0;

	mdiodev = mdio_device_create(bus, bi->mdio_addr);
	if (IS_ERR(mdiodev))
		return -ENODEV;

	strncpy(mdiodev->modalias, bi->modalias,
		sizeof(mdiodev->modalias));
	mdiodev->bus_match = mdio_device_bus_match;
	mdiodev->dev.platform_data = (void *)bi->platform_data;

	ret = mdio_device_register(mdiodev);
	if (ret)
		mdio_device_free(mdiodev);

	return ret;
}