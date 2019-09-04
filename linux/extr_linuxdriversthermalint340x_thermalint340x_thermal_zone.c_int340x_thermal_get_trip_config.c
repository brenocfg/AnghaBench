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
 int DECI_KELVIN_TO_MILLICELSIUS (unsigned long long) ; 
 int EIO ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 

__attribute__((used)) static int int340x_thermal_get_trip_config(acpi_handle handle, char *name,
				      int *temp)
{
	unsigned long long r;
	acpi_status status;

	status = acpi_evaluate_integer(handle, name, NULL, &r);
	if (ACPI_FAILURE(status))
		return -EIO;

	*temp = DECI_KELVIN_TO_MILLICELSIUS(r);

	return 0;
}