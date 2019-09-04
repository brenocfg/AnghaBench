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
struct mdio_device {size_t addr; TYPE_1__* bus; } ;
struct TYPE_2__ {struct mdio_device** mdio_map; } ;

/* Variables and functions */
 int EINVAL ; 

int mdiobus_unregister_device(struct mdio_device *mdiodev)
{
	if (mdiodev->bus->mdio_map[mdiodev->addr] != mdiodev)
		return -EINVAL;

	mdiodev->bus->mdio_map[mdiodev->addr] = NULL;

	return 0;
}