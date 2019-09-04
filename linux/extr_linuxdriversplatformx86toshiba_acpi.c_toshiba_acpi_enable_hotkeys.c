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
typedef  scalar_t__ u32 ;
struct toshiba_acpi_dev {scalar_t__ special_functions; scalar_t__ kbd_function_keys_supported; TYPE_1__* acpi_dev; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  HCI_HOTKEY_ENABLE ; 
 int /*<<< orphan*/  HCI_HOTKEY_EVENT ; 
 int /*<<< orphan*/  HCI_HOTKEY_SPECIAL_FUNCTIONS ; 
 scalar_t__ TOS_FAILURE ; 
 scalar_t__ TOS_NOT_SUPPORTED ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hci_write (struct toshiba_acpi_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int toshiba_acpi_enable_hotkeys(struct toshiba_acpi_dev *dev)
{
	acpi_status status;
	u32 result;

	status = acpi_evaluate_object(dev->acpi_dev->handle,
				      "ENAB", NULL, NULL);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	/*
	 * Enable the "Special Functions" mode only if they are
	 * supported and if they are activated.
	 */
	if (dev->kbd_function_keys_supported && dev->special_functions)
		result = hci_write(dev, HCI_HOTKEY_EVENT,
				   HCI_HOTKEY_SPECIAL_FUNCTIONS);
	else
		result = hci_write(dev, HCI_HOTKEY_EVENT, HCI_HOTKEY_ENABLE);

	if (result == TOS_FAILURE)
		return -EIO;
	else if (result == TOS_NOT_SUPPORTED)
		return -ENODEV;

	return 0;
}