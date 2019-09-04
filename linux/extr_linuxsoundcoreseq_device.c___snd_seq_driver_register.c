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
struct TYPE_2__ {struct module* owner; int /*<<< orphan*/ * bus; int /*<<< orphan*/  name; } ;
struct snd_seq_driver {TYPE_1__ driver; int /*<<< orphan*/  id; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_seq_bus_type ; 

int __snd_seq_driver_register(struct snd_seq_driver *drv, struct module *mod)
{
	if (WARN_ON(!drv->driver.name || !drv->id))
		return -EINVAL;
	drv->driver.bus = &snd_seq_bus_type;
	drv->driver.owner = mod;
	return driver_register(&drv->driver);
}