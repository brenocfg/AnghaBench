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
struct asus_laptop {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  METHOD_GPS_STATUS ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int asus_gps_status(struct asus_laptop *asus)
{
	unsigned long long status;
	acpi_status rv;

	rv = acpi_evaluate_integer(asus->handle, METHOD_GPS_STATUS,
				   NULL, &status);
	if (ACPI_FAILURE(rv)) {
		pr_warn("Error reading GPS status\n");
		return -ENODEV;
	}
	return !!status;
}