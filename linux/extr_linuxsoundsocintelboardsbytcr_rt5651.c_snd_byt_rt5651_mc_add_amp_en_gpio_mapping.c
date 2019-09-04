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
struct device {int dummy; } ;
struct byt_rt5651_acpi_resource_data {int member_1; int gpio_int_idx; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPANION (struct device*) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_dev_free_resource_list (int /*<<< orphan*/ *) ; 
 int acpi_dev_get_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct byt_rt5651_acpi_resource_data*) ; 
 int /*<<< orphan*/  byt_rt5651_amp_en_first ; 
 int /*<<< orphan*/  byt_rt5651_amp_en_second ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_acpi_dev_add_driver_gpios (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resources ; 
 int /*<<< orphan*/  snd_byt_rt5651_acpi_resource ; 

__attribute__((used)) static void snd_byt_rt5651_mc_add_amp_en_gpio_mapping(struct device *codec)
{
	struct byt_rt5651_acpi_resource_data data = { 0, -1 };
	LIST_HEAD(resources);
	int ret;

	ret = acpi_dev_get_resources(ACPI_COMPANION(codec), &resources,
				     snd_byt_rt5651_acpi_resource, &data);
	if (ret < 0) {
		dev_warn(codec, "Failed to get ACPI resources, not adding external amplifier GPIO mapping\n");
		return;
	}

	/* All info we need is gathered during the walk */
	acpi_dev_free_resource_list(&resources);

	switch (data.gpio_int_idx) {
	case 0:
		devm_acpi_dev_add_driver_gpios(codec, byt_rt5651_amp_en_second);
		break;
	case 1:
		devm_acpi_dev_add_driver_gpios(codec, byt_rt5651_amp_en_first);
		break;
	default:
		dev_warn(codec, "Unknown GpioInt index %d, not adding external amplifier GPIO mapping\n",
			 data.gpio_int_idx);
	}
}