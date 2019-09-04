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
struct acpi_device {int /*<<< orphan*/  handle; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_execute_simple_method (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int smartconnect_acpi_init(struct acpi_device *acpi)
{
	unsigned long long value;
	acpi_status status;

	status = acpi_evaluate_integer(acpi->handle, "GAOS", NULL, &value);
	if (ACPI_FAILURE(status))
		return -EINVAL;

	if (value & 0x1) {
		dev_info(&acpi->dev, "Disabling Intel Smart Connect\n");
		status = acpi_execute_simple_method(acpi->handle, "SAOS", 0);
	}

	return 0;
}