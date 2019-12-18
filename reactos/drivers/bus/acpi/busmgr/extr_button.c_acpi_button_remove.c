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
struct acpi_device {int dummy; } ;
struct acpi_button {int type; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
#define  ACPI_BUTTON_TYPE_LID 130 
#define  ACPI_BUTTON_TYPE_POWERF 129 
#define  ACPI_BUTTON_TYPE_SLEEPF 128 
 int /*<<< orphan*/  ACPI_DB_ERROR ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 int const ACPI_EVENT_POWER_BUTTON ; 
 int const ACPI_EVENT_SLEEP_BUTTON ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (char*) ; 
 int /*<<< orphan*/  AcpiRemoveFixedEventHandler (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiRemoveNotifyHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (struct acpi_button*,char) ; 
 int /*<<< orphan*/  acpi_button_notify ; 
 int /*<<< orphan*/  acpi_button_notify_fixed ; 
 struct acpi_button* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  return_VALUE (int) ; 

__attribute__((used)) static int
acpi_button_remove (struct acpi_device *device, int type)
{
	ACPI_STATUS		status = 0;
	struct acpi_button	*button = NULL;

	ACPI_FUNCTION_TRACE("acpi_button_remove");

	if (!device || !acpi_driver_data(device))
		return_VALUE(-1);

	button = acpi_driver_data(device);

	/* Unregister for device notifications. */
	switch (button->type) {
	case ACPI_BUTTON_TYPE_POWERF:
		status = AcpiRemoveFixedEventHandler(
			ACPI_EVENT_POWER_BUTTON, acpi_button_notify_fixed);
		break;
	case ACPI_BUTTON_TYPE_SLEEPF:
		status = AcpiRemoveFixedEventHandler(
			ACPI_EVENT_SLEEP_BUTTON, acpi_button_notify_fixed);
		break;
	case ACPI_BUTTON_TYPE_LID:
		status = AcpiRemoveFixedEventHandler(
			ACPI_BUTTON_TYPE_LID, acpi_button_notify_fixed);
		break;
	default:
		status = AcpiRemoveNotifyHandler(button->handle,
			ACPI_DEVICE_NOTIFY, acpi_button_notify);
		break;
	}

	if (ACPI_FAILURE(status))
		ACPI_DEBUG_PRINT((ACPI_DB_ERROR,
			"Error removing notify handler\n"));

	ExFreePoolWithTag(button, 'IPCA');

	return_VALUE(0);
}