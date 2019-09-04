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
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  acpi_execute_simple_method (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int toshiba_haps_protection_level(acpi_handle handle, int level)
{
	acpi_status status;

	status = acpi_execute_simple_method(handle, "PTLV", level);
	if (ACPI_FAILURE(status)) {
		pr_err("Error while setting the protection level\n");
		return -EIO;
	}

	pr_debug("HDD protection level set to: %d\n", level);

	return 0;
}