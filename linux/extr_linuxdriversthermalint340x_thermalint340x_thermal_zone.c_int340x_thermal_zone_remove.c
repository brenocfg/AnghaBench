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
struct int34x_thermal_zone {struct int34x_thermal_zone* aux_trips; int /*<<< orphan*/  lpat_table; int /*<<< orphan*/  zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_lpat_free_conversion_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct int34x_thermal_zone*) ; 
 int /*<<< orphan*/  thermal_zone_device_unregister (int /*<<< orphan*/ ) ; 

void int340x_thermal_zone_remove(struct int34x_thermal_zone
				 *int34x_thermal_zone)
{
	thermal_zone_device_unregister(int34x_thermal_zone->zone);
	acpi_lpat_free_conversion_table(int34x_thermal_zone->lpat_table);
	kfree(int34x_thermal_zone->aux_trips);
	kfree(int34x_thermal_zone);
}