#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct acpi_driver {int /*<<< orphan*/  references; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  present; } ;
struct acpi_device {TYPE_2__ pnp; TYPE_1__ status; scalar_t__ driver; } ;

/* Variables and functions */
 int AE_BAD_PARAMETER ; 
 int AE_NOT_FOUND ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int acpi_bus_driver_init (struct acpi_device*,struct acpi_driver*) ; 
 int /*<<< orphan*/  acpi_bus_drivers_lock ; 
 int acpi_bus_match (struct acpi_device*,struct acpi_driver*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_VALUE (int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
acpi_bus_attach (
	struct acpi_device	*device,
	int			level,
	void			*data)
{
	int			result = 0;
	struct acpi_driver	*driver = NULL;

	if (!device || !data)
		return_VALUE(AE_BAD_PARAMETER);

	driver = (struct acpi_driver *) data;

	if (device->driver)
		return_VALUE(-9);

	if (!device->status.present)
		return_VALUE(AE_NOT_FOUND);

	result = acpi_bus_match(device, driver);
	if (result)
		return_VALUE(result);

	DPRINT("Found driver [%s] for device [%s]\n",
		driver->name, device->pnp.bus_id);

	result = acpi_bus_driver_init(device, driver);
	if (result)
		return_VALUE(result);

	down(&acpi_bus_drivers_lock);
	++driver->references;
	up(&acpi_bus_drivers_lock);

	return_VALUE(0);
}