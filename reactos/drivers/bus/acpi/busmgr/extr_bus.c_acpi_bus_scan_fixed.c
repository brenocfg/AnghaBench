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
struct acpi_device {int dummy; } ;
struct TYPE_2__ {int Flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BITREG_POWER_BUTTON_ENABLE ; 
 int /*<<< orphan*/  ACPI_BITREG_SLEEP_BUTTON_ENABLE ; 
 int /*<<< orphan*/  ACPI_BUS_TYPE_POWER_BUTTON ; 
 int /*<<< orphan*/  ACPI_BUS_TYPE_POWER_BUTTONF ; 
 int /*<<< orphan*/  ACPI_BUS_TYPE_SLEEP_BUTTON ; 
 int /*<<< orphan*/  ACPI_BUS_TYPE_SLEEP_BUTTONF ; 
 int ACPI_FADT_POWER_BUTTON ; 
 int ACPI_FADT_SLEEP_BUTTON ; 
 int AE_NOT_FOUND ; 
 TYPE_1__ AcpiGbl_FADT ; 
 int /*<<< orphan*/  AcpiWriteBitRegister (int /*<<< orphan*/ ,int) ; 
 int acpi_bus_add (struct acpi_device**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_root ; 
 int /*<<< orphan*/  return_VALUE (int) ; 

__attribute__((used)) static int
acpi_bus_scan_fixed (
	struct acpi_device	*root)
{
	int			result = 0;
	struct acpi_device	*device = NULL;

	if (!root)
		return_VALUE(AE_NOT_FOUND);

	/* If ACPI_FADT_POWER_BUTTON is set, then a control
	 * method power button is present. Otherwise, a fixed
	 * power button is present.
	 */
	if (AcpiGbl_FADT.Flags & ACPI_FADT_POWER_BUTTON)
		result = acpi_bus_add(&device, acpi_root,
			NULL, ACPI_BUS_TYPE_POWER_BUTTON);
	else
	{
		/* Enable the fixed power button so we get notified if it is pressed */
		AcpiWriteBitRegister(ACPI_BITREG_POWER_BUTTON_ENABLE, 1);

		result = acpi_bus_add(&device, acpi_root,
			NULL, ACPI_BUS_TYPE_POWER_BUTTONF);
	}

	/* This one is a bit more complicated and we do it wrong
	 * right now. If ACPI_FADT_SLEEP_BUTTON is set but no
	 * device object is present then no sleep button is present, but
	 * if the flags is clear and there is no device object then it is
	 * a fixed sleep button. If the flag is set and there is a device object
	 * the we have a control method button just like above.
	 */
	if (AcpiGbl_FADT.Flags & ACPI_FADT_SLEEP_BUTTON)
		result = acpi_bus_add(&device, acpi_root,
			NULL, ACPI_BUS_TYPE_SLEEP_BUTTON);
	else
	{
		/* Enable the fixed sleep button so we get notified if it is pressed */
		AcpiWriteBitRegister(ACPI_BITREG_SLEEP_BUTTON_ENABLE, 1);

		result = acpi_bus_add(&device, acpi_root,
			NULL, ACPI_BUS_TYPE_SLEEP_BUTTONF);
	}

	return_VALUE(result);
}