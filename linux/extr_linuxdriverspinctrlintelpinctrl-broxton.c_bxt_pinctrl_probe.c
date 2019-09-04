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
struct platform_device_id {scalar_t__ driver_data; } ;
struct platform_device {size_t id; int /*<<< orphan*/  dev; } ;
struct intel_pinctrl_soc_data {int /*<<< orphan*/  uid; } ;
struct acpi_device_id {scalar_t__ driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  unique_id; } ;
struct acpi_device {TYPE_1__ pnp; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bxt_pinctrl_acpi_match ; 
 int intel_pinctrl_probe (struct platform_device*,struct intel_pinctrl_soc_data const*) ; 
 struct platform_device_id* platform_get_device_id (struct platform_device*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bxt_pinctrl_probe(struct platform_device *pdev)
{
	const struct intel_pinctrl_soc_data *soc_data = NULL;
	const struct intel_pinctrl_soc_data **soc_table;
	struct acpi_device *adev;
	int i;

	adev = ACPI_COMPANION(&pdev->dev);
	if (adev) {
		const struct acpi_device_id *id;

		id = acpi_match_device(bxt_pinctrl_acpi_match, &pdev->dev);
		if (!id)
			return -ENODEV;

		soc_table = (const struct intel_pinctrl_soc_data **)
			id->driver_data;

		for (i = 0; soc_table[i]; i++) {
			if (!strcmp(adev->pnp.unique_id, soc_table[i]->uid)) {
				soc_data = soc_table[i];
				break;
			}
		}
	} else {
		const struct platform_device_id *pid;

		pid = platform_get_device_id(pdev);
		if (!pid)
			return -ENODEV;

		soc_table = (const struct intel_pinctrl_soc_data **)
			pid->driver_data;
		soc_data = soc_table[pdev->id];
	}

	if (!soc_data)
		return -ENODEV;

	return intel_pinctrl_probe(pdev, soc_data);
}