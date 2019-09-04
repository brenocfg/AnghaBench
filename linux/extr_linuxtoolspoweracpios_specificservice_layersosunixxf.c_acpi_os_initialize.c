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

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_gbl_output_file ; 
 int /*<<< orphan*/  acpi_gbl_print_lock ; 
 int /*<<< orphan*/  acpi_os_create_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_enter_line_edit_mode () ; 
 int /*<<< orphan*/  stdout ; 

acpi_status acpi_os_initialize(void)
{
	acpi_status status;

	acpi_gbl_output_file = stdout;

	os_enter_line_edit_mode();

	status = acpi_os_create_lock(&acpi_gbl_print_lock);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	return (AE_OK);
}