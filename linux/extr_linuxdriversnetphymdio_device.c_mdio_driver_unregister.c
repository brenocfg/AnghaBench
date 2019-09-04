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
struct mdio_driver_common {int /*<<< orphan*/  driver; } ;
struct mdio_driver {struct mdio_driver_common mdiodrv; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_unregister (int /*<<< orphan*/ *) ; 

void mdio_driver_unregister(struct mdio_driver *drv)
{
	struct mdio_driver_common *mdiodrv = &drv->mdiodrv;

	driver_unregister(&mdiodrv->driver);
}