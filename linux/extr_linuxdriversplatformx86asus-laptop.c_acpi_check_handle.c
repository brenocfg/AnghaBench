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
typedef  scalar_t__ acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ AE_OK ; 
 int ENODEV ; 
 scalar_t__ acpi_get_handle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*) ; 

__attribute__((used)) static int acpi_check_handle(acpi_handle handle, const char *method,
			     acpi_handle *ret)
{
	acpi_status status;

	if (method == NULL)
		return -ENODEV;

	if (ret)
		status = acpi_get_handle(handle, (char *)method,
					 ret);
	else {
		acpi_handle dummy;

		status = acpi_get_handle(handle, (char *)method,
					 &dummy);
	}

	if (status != AE_OK) {
		if (ret)
			pr_warn("Error finding %s\n", method);
		return -ENODEV;
	}
	return 0;
}