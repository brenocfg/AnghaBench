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
struct TYPE_2__ {int /*<<< orphan*/ * bus; struct module* owner; } ;
struct typec_altmode_driver {TYPE_1__ driver; int /*<<< orphan*/  probe; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  typec_bus ; 

int __typec_altmode_register_driver(struct typec_altmode_driver *drv,
				    struct module *module)
{
	if (!drv->probe)
		return -EINVAL;

	drv->driver.owner = module;
	drv->driver.bus = &typec_bus;

	return driver_register(&drv->driver);
}