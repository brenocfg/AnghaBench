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
struct int3402_thermal_data {int /*<<< orphan*/  handle; int /*<<< orphan*/  int340x_zone; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_has_method (int /*<<< orphan*/ ,char*) ; 
 int acpi_install_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct int3402_thermal_data*) ; 
 struct int3402_thermal_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int3402_notify ; 
 int /*<<< orphan*/  int340x_thermal_zone_add (struct acpi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  int340x_thermal_zone_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct int3402_thermal_data*) ; 

__attribute__((used)) static int int3402_thermal_probe(struct platform_device *pdev)
{
	struct acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	struct int3402_thermal_data *d;
	int ret;

	if (!acpi_has_method(adev->handle, "_TMP"))
		return -ENODEV;

	d = devm_kzalloc(&pdev->dev, sizeof(*d), GFP_KERNEL);
	if (!d)
		return -ENOMEM;

	d->int340x_zone = int340x_thermal_zone_add(adev, NULL);
	if (IS_ERR(d->int340x_zone))
		return PTR_ERR(d->int340x_zone);

	ret = acpi_install_notify_handler(adev->handle,
					  ACPI_DEVICE_NOTIFY,
					  int3402_notify,
					  d);
	if (ret) {
		int340x_thermal_zone_remove(d->int340x_zone);
		return ret;
	}

	d->handle = adev->handle;
	platform_set_drvdata(pdev, d);

	return 0;
}