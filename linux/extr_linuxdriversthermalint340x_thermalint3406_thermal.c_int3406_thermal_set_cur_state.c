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
struct thermal_cooling_device {struct int3406_thermal_data* devdata; } ;
struct int3406_thermal_data {unsigned long upper_limit; unsigned long lower_limit; int /*<<< orphan*/  raw_bd; TYPE_1__* br; } ;
struct TYPE_2__ {int* levels; } ;

/* Variables and functions */
 int ACPI_TO_RAW (int,struct int3406_thermal_data*) ; 
 int EINVAL ; 
 int backlight_device_set_brightness (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
int3406_thermal_set_cur_state(struct thermal_cooling_device *cooling_dev,
			      unsigned long state)
{
	struct int3406_thermal_data *d = cooling_dev->devdata;
	int acpi_level, raw_level;

	if (state > d->upper_limit - d->lower_limit)
		return -EINVAL;

	acpi_level = d->br->levels[d->upper_limit - state];

	raw_level = ACPI_TO_RAW(acpi_level, d);

	return backlight_device_set_brightness(d->raw_bd, raw_level);
}