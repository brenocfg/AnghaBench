#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct byt_rt5651_acpi_resource_data {int /*<<< orphan*/  gpio_count; int /*<<< orphan*/  gpio_int_idx; } ;
struct TYPE_3__ {scalar_t__ connection_type; } ;
struct TYPE_4__ {TYPE_1__ gpio; } ;
struct acpi_resource {scalar_t__ type; TYPE_2__ data; } ;

/* Variables and functions */
 scalar_t__ ACPI_RESOURCE_GPIO_TYPE_INT ; 
 scalar_t__ ACPI_RESOURCE_TYPE_GPIO ; 

__attribute__((used)) static int snd_byt_rt5651_acpi_resource(struct acpi_resource *ares, void *arg)
{
	struct byt_rt5651_acpi_resource_data *data = arg;

	if (ares->type != ACPI_RESOURCE_TYPE_GPIO)
		return 0;

	if (ares->data.gpio.connection_type == ACPI_RESOURCE_GPIO_TYPE_INT)
		data->gpio_int_idx = data->gpio_count;

	data->gpio_count++;
	return 0;
}