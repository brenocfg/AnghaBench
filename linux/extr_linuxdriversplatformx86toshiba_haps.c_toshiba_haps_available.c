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
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int toshiba_haps_available(acpi_handle handle)
{
	acpi_status status;
	u64 hdd_present;

	/*
	 * A non existent device as well as having (only)
	 * Solid State Drives can cause the call to fail.
	 */
	status = acpi_evaluate_integer(handle, "_STA", NULL, &hdd_present);
	if (ACPI_FAILURE(status)) {
		pr_err("ACPI call to query HDD protection failed\n");
		return 0;
	}

	if (!hdd_present) {
		pr_info("HDD protection not available or using SSD\n");
		return 0;
	}

	return 1;
}