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
struct TYPE_2__ {char const* mod_name; int /*<<< orphan*/ * bus; struct module* owner; int /*<<< orphan*/  name; } ;
struct umc_driver {TYPE_1__ driver; int /*<<< orphan*/  name; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  umc_bus_type ; 

int __umc_driver_register(struct umc_driver *umc_drv, struct module *module,
			  const char *mod_name)
{
	umc_drv->driver.name     = umc_drv->name;
	umc_drv->driver.owner    = module;
	umc_drv->driver.mod_name = mod_name;
	umc_drv->driver.bus      = &umc_bus_type;

	return driver_register(&umc_drv->driver);
}