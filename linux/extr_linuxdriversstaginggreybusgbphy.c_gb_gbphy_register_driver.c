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
struct module {int dummy; } ;
struct TYPE_2__ {char const* mod_name; struct module* owner; int /*<<< orphan*/  name; int /*<<< orphan*/ * bus; } ;
struct gbphy_driver {int /*<<< orphan*/  name; TYPE_1__ driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  gbphy_bus_type ; 
 scalar_t__ greybus_disabled () ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

int gb_gbphy_register_driver(struct gbphy_driver *driver,
			     struct module *owner, const char *mod_name)
{
	int retval;

	if (greybus_disabled())
		return -ENODEV;

	driver->driver.bus = &gbphy_bus_type;
	driver->driver.name = driver->name;
	driver->driver.owner = owner;
	driver->driver.mod_name = mod_name;

	retval = driver_register(&driver->driver);
	if (retval)
		return retval;

	pr_info("registered new driver %s\n", driver->name);
	return 0;
}