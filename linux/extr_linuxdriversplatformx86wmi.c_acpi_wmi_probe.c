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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ADR_SPACE_EC ; 
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  acpi_install_address_space_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_install_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_remove_address_space_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_wmi_ec_space_handler ; 
 int /*<<< orphan*/  acpi_wmi_notify_handler ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct device*) ; 
 struct device* device_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int parse_wdg (struct device*,struct acpi_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  wmi_bus_class ; 

__attribute__((used)) static int acpi_wmi_probe(struct platform_device *device)
{
	struct acpi_device *acpi_device;
	struct device *wmi_bus_dev;
	acpi_status status;
	int error;

	acpi_device = ACPI_COMPANION(&device->dev);
	if (!acpi_device) {
		dev_err(&device->dev, "ACPI companion is missing\n");
		return -ENODEV;
	}

	status = acpi_install_address_space_handler(acpi_device->handle,
						    ACPI_ADR_SPACE_EC,
						    &acpi_wmi_ec_space_handler,
						    NULL, NULL);
	if (ACPI_FAILURE(status)) {
		dev_err(&device->dev, "Error installing EC region handler\n");
		return -ENODEV;
	}

	status = acpi_install_notify_handler(acpi_device->handle,
					     ACPI_DEVICE_NOTIFY,
					     acpi_wmi_notify_handler,
					     NULL);
	if (ACPI_FAILURE(status)) {
		dev_err(&device->dev, "Error installing notify handler\n");
		error = -ENODEV;
		goto err_remove_ec_handler;
	}

	wmi_bus_dev = device_create(&wmi_bus_class, &device->dev, MKDEV(0, 0),
				    NULL, "wmi_bus-%s", dev_name(&device->dev));
	if (IS_ERR(wmi_bus_dev)) {
		error = PTR_ERR(wmi_bus_dev);
		goto err_remove_notify_handler;
	}
	dev_set_drvdata(&device->dev, wmi_bus_dev);

	error = parse_wdg(wmi_bus_dev, acpi_device);
	if (error) {
		pr_err("Failed to parse WDG method\n");
		goto err_remove_busdev;
	}

	return 0;

err_remove_busdev:
	device_destroy(&wmi_bus_class, MKDEV(0, 0));

err_remove_notify_handler:
	acpi_remove_notify_handler(acpi_device->handle, ACPI_DEVICE_NOTIFY,
				   acpi_wmi_notify_handler);

err_remove_ec_handler:
	acpi_remove_address_space_handler(acpi_device->handle,
					  ACPI_ADR_SPACE_EC,
					  &acpi_wmi_ec_space_handler);

	return error;
}