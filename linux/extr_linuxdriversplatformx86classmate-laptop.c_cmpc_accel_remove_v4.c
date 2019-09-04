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
struct input_dev {int /*<<< orphan*/  dev; } ;
struct cmpc_accel {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmpc_accel_g_select_attr_v4 ; 
 int /*<<< orphan*/  cmpc_accel_sensitivity_attr_v4 ; 
 int cmpc_remove_acpi_notify_device (struct acpi_device*) ; 
 void* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmpc_accel_remove_v4(struct acpi_device *acpi)
{
	struct input_dev *inputdev;
	struct cmpc_accel *accel;

	inputdev = dev_get_drvdata(&acpi->dev);
	accel = dev_get_drvdata(&inputdev->dev);

	device_remove_file(&acpi->dev, &cmpc_accel_sensitivity_attr_v4);
	device_remove_file(&acpi->dev, &cmpc_accel_g_select_attr_v4);
	return cmpc_remove_acpi_notify_device(acpi);
}