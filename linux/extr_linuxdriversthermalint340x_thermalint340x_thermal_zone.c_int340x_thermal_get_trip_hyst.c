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
struct thermal_zone_device {struct int34x_thermal_zone* devdata; } ;
struct int34x_thermal_zone {TYPE_1__* adev; TYPE_2__* override_ops; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_4__ {int (* get_trip_hyst ) (struct thermal_zone_device*,int,int*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int stub1 (struct thermal_zone_device*,int,int*) ; 

__attribute__((used)) static int int340x_thermal_get_trip_hyst(struct thermal_zone_device *zone,
		int trip, int *temp)
{
	struct int34x_thermal_zone *d = zone->devdata;
	acpi_status status;
	unsigned long long hyst;

	if (d->override_ops && d->override_ops->get_trip_hyst)
		return d->override_ops->get_trip_hyst(zone, trip, temp);

	status = acpi_evaluate_integer(d->adev->handle, "GTSH", NULL, &hyst);
	if (ACPI_FAILURE(status))
		*temp = 0;
	else
		*temp = hyst * 100;

	return 0;
}