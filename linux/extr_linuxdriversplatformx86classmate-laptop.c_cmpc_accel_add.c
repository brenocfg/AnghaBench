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
struct cmpc_accel {int /*<<< orphan*/  sensitivity; } ;
struct acpi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMPC_ACCEL_SENSITIVITY_DEFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cmpc_accel_idev_init ; 
 int /*<<< orphan*/  cmpc_accel_sensitivity_attr ; 
 int /*<<< orphan*/  cmpc_accel_set_sensitivity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cmpc_add_acpi_notify_device (struct acpi_device*,char*,int /*<<< orphan*/ ) ; 
 struct input_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct cmpc_accel*) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cmpc_accel*) ; 
 struct cmpc_accel* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmpc_accel_add(struct acpi_device *acpi)
{
	int error;
	struct input_dev *inputdev;
	struct cmpc_accel *accel;

	accel = kmalloc(sizeof(*accel), GFP_KERNEL);
	if (!accel)
		return -ENOMEM;

	accel->sensitivity = CMPC_ACCEL_SENSITIVITY_DEFAULT;
	cmpc_accel_set_sensitivity(acpi->handle, accel->sensitivity);

	error = device_create_file(&acpi->dev, &cmpc_accel_sensitivity_attr);
	if (error)
		goto failed_file;

	error = cmpc_add_acpi_notify_device(acpi, "cmpc_accel",
					    cmpc_accel_idev_init);
	if (error)
		goto failed_input;

	inputdev = dev_get_drvdata(&acpi->dev);
	dev_set_drvdata(&inputdev->dev, accel);

	return 0;

failed_input:
	device_remove_file(&acpi->dev, &cmpc_accel_sensitivity_attr);
failed_file:
	kfree(accel);
	return error;
}