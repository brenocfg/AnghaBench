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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int toshiba_bluetooth_present(acpi_handle handle)
{
	acpi_status result;
	u64 bt_present;

	/*
	 * Some Toshiba laptops may have a fake TOS6205 device in
	 * their ACPI BIOS, so query the _STA method to see if there
	 * is really anything there.
	 */
	result = acpi_evaluate_integer(handle, "_STA", NULL, &bt_present);
	if (ACPI_FAILURE(result)) {
		pr_err("ACPI call to query Bluetooth presence failed\n");
		return -ENXIO;
	}

	if (!bt_present) {
		pr_info("Bluetooth device not present\n");
		return -ENODEV;
	}

	return 0;
}