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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct input_dev {TYPE_1__ dev; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  cmpc_start_accel (int /*<<< orphan*/ ) ; 
 struct acpi_device* to_acpi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmpc_accel_open(struct input_dev *input)
{
	struct acpi_device *acpi;

	acpi = to_acpi_device(input->dev.parent);
	if (ACPI_SUCCESS(cmpc_start_accel(acpi->handle)))
		return 0;
	return -EIO;
}