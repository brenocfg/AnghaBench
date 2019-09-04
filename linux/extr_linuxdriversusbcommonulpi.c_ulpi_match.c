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
struct ulpi_driver {struct ulpi_device_id* id_table; } ;
struct ulpi_device_id {scalar_t__ vendor; scalar_t__ product; } ;
struct TYPE_2__ {scalar_t__ vendor; scalar_t__ product; } ;
struct ulpi {TYPE_1__ id; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int of_driver_match_device (struct device*,struct device_driver*) ; 
 struct ulpi* to_ulpi_dev (struct device*) ; 
 struct ulpi_driver* to_ulpi_driver (struct device_driver*) ; 

__attribute__((used)) static int ulpi_match(struct device *dev, struct device_driver *driver)
{
	struct ulpi_driver *drv = to_ulpi_driver(driver);
	struct ulpi *ulpi = to_ulpi_dev(dev);
	const struct ulpi_device_id *id;

	/* Some ULPI devices don't have a vendor id so rely on OF match */
	if (ulpi->id.vendor == 0)
		return of_driver_match_device(dev, driver);

	for (id = drv->id_table; id->vendor; id++)
		if (id->vendor == ulpi->id.vendor &&
		    id->product == ulpi->id.product)
			return 1;

	return 0;
}