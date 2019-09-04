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
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  shutdown; int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; int /*<<< orphan*/ * bus; struct module* owner; } ;
struct siox_driver {TYPE_1__ driver; scalar_t__ shutdown; scalar_t__ remove; scalar_t__ probe; int /*<<< orphan*/  get_data; int /*<<< orphan*/  set_data; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  siox_bus_type ; 
 int /*<<< orphan*/  siox_driver_probe ; 
 int /*<<< orphan*/  siox_driver_remove ; 
 int /*<<< orphan*/  siox_driver_shutdown ; 
 int /*<<< orphan*/  siox_is_registered ; 
 scalar_t__ unlikely (int) ; 

int __siox_driver_register(struct siox_driver *sdriver, struct module *owner)
{
	int ret;

	if (unlikely(!siox_is_registered))
		return -EPROBE_DEFER;

	if (!sdriver->set_data && !sdriver->get_data) {
		pr_err("Driver %s doesn't provide needed callbacks\n",
		       sdriver->driver.name);
		return -EINVAL;
	}

	sdriver->driver.owner = owner;
	sdriver->driver.bus = &siox_bus_type;

	if (sdriver->probe)
		sdriver->driver.probe = siox_driver_probe;
	if (sdriver->remove)
		sdriver->driver.remove = siox_driver_remove;
	if (sdriver->shutdown)
		sdriver->driver.shutdown = siox_driver_shutdown;

	ret = driver_register(&sdriver->driver);
	if (ret)
		pr_err("Failed to register siox driver %s (%d)\n",
		       sdriver->driver.name, ret);

	return ret;
}