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
struct device_driver {int /*<<< orphan*/ * bus; } ;
struct ccw_driver {struct device_driver driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccw_bus_type ; 
 int driver_register (struct device_driver*) ; 

int ccw_driver_register(struct ccw_driver *cdriver)
{
	struct device_driver *drv = &cdriver->driver;

	drv->bus = &ccw_bus_type;

	return driver_register(drv);
}