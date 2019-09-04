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
struct intel_pinctrl_soc_data {int dummy; } ;
struct acpi_device_id {scalar_t__ driver_data; } ;

/* Variables and functions */
 int ENODEV ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int intel_pinctrl_probe (struct platform_device*,struct intel_pinctrl_soc_data const*) ; 
 int /*<<< orphan*/  spt_pinctrl_acpi_match ; 

__attribute__((used)) static int spt_pinctrl_probe(struct platform_device *pdev)
{
	const struct intel_pinctrl_soc_data *soc_data;
	const struct acpi_device_id *id;

	id = acpi_match_device(spt_pinctrl_acpi_match, &pdev->dev);
	if (!id || !id->driver_data)
		return -ENODEV;

	soc_data = (const struct intel_pinctrl_soc_data *)id->driver_data;
	return intel_pinctrl_probe(pdev, soc_data);
}