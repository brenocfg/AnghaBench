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
struct thermal_zone_device_ops {int dummy; } ;
struct int34x_thermal_zone {unsigned long long aux_trip_nr; struct int34x_thermal_zone* aux_trips; int /*<<< orphan*/  lpat_table; int /*<<< orphan*/  zone; struct thermal_zone_device_ops* override_ops; struct acpi_device* adev; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int BIT (unsigned long long) ; 
 int ENOMEM ; 
 struct int34x_thermal_zone* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_device_bid (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_lpat_free_conversion_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_lpat_get_conversion_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int340x_thermal_params ; 
 unsigned long long int340x_thermal_read_trips (struct int34x_thermal_zone*) ; 
 int /*<<< orphan*/  int340x_thermal_zone_ops ; 
 struct int34x_thermal_zone* kcalloc (unsigned long long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct int34x_thermal_zone*) ; 
 struct int34x_thermal_zone* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_zone_device_register (int /*<<< orphan*/ ,unsigned long long,int,struct int34x_thermal_zone*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct int34x_thermal_zone *int340x_thermal_zone_add(struct acpi_device *adev,
				struct thermal_zone_device_ops *override_ops)
{
	struct int34x_thermal_zone *int34x_thermal_zone;
	acpi_status status;
	unsigned long long trip_cnt;
	int trip_mask = 0;
	int ret;

	int34x_thermal_zone = kzalloc(sizeof(*int34x_thermal_zone),
				      GFP_KERNEL);
	if (!int34x_thermal_zone)
		return ERR_PTR(-ENOMEM);

	int34x_thermal_zone->adev = adev;
	int34x_thermal_zone->override_ops = override_ops;

	status = acpi_evaluate_integer(adev->handle, "PATC", NULL, &trip_cnt);
	if (ACPI_FAILURE(status))
		trip_cnt = 0;
	else {
		int34x_thermal_zone->aux_trips =
			kcalloc(trip_cnt,
				sizeof(*int34x_thermal_zone->aux_trips),
				GFP_KERNEL);
		if (!int34x_thermal_zone->aux_trips) {
			ret = -ENOMEM;
			goto err_trip_alloc;
		}
		trip_mask = BIT(trip_cnt) - 1;
		int34x_thermal_zone->aux_trip_nr = trip_cnt;
	}

	trip_cnt = int340x_thermal_read_trips(int34x_thermal_zone);

	int34x_thermal_zone->lpat_table = acpi_lpat_get_conversion_table(
								adev->handle);

	int34x_thermal_zone->zone = thermal_zone_device_register(
						acpi_device_bid(adev),
						trip_cnt,
						trip_mask, int34x_thermal_zone,
						&int340x_thermal_zone_ops,
						&int340x_thermal_params,
						0, 0);
	if (IS_ERR(int34x_thermal_zone->zone)) {
		ret = PTR_ERR(int34x_thermal_zone->zone);
		goto err_thermal_zone;
	}

	return int34x_thermal_zone;

err_thermal_zone:
	acpi_lpat_free_conversion_table(int34x_thermal_zone->lpat_table);
	kfree(int34x_thermal_zone->aux_trips);
err_trip_alloc:
	kfree(int34x_thermal_zone);
	return ERR_PTR(ret);
}