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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct intel_pinctrl_soc_data {int /*<<< orphan*/  uid; } ;
struct TYPE_2__ {int /*<<< orphan*/  unique_id; } ;
struct acpi_device {TYPE_1__ pnp; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 struct intel_pinctrl_soc_data** glk_pinctrl_soc_data ; 
 int intel_pinctrl_probe (struct platform_device*,struct intel_pinctrl_soc_data const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int glk_pinctrl_probe(struct platform_device *pdev)
{
	const struct intel_pinctrl_soc_data *soc_data = NULL;
	struct acpi_device *adev;
	int i;

	adev = ACPI_COMPANION(&pdev->dev);
	if (!adev)
		return -ENODEV;

	for (i = 0; glk_pinctrl_soc_data[i]; i++) {
		if (!strcmp(adev->pnp.unique_id,
			    glk_pinctrl_soc_data[i]->uid)) {
			soc_data = glk_pinctrl_soc_data[i];
			break;
		}
	}

	if (!soc_data)
		return -ENODEV;

	return intel_pinctrl_probe(pdev, soc_data);
}