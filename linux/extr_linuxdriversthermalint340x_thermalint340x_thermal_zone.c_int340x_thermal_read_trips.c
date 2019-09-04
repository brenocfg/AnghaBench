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
struct int34x_thermal_zone {int aux_trip_nr; int crt_trip_id; int hot_trip_id; int psv_trip_id; TYPE_2__* act_trips; TYPE_1__* adev; int /*<<< orphan*/  psv_temp; int /*<<< orphan*/  hot_temp; int /*<<< orphan*/  crt_temp; } ;
struct TYPE_4__ {int valid; int /*<<< orphan*/  id; int /*<<< orphan*/  temp; } ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int INT340X_THERMAL_MAX_ACT_TRIP_COUNT ; 
 scalar_t__ int340x_thermal_get_trip_config (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

int int340x_thermal_read_trips(struct int34x_thermal_zone *int34x_zone)
{
	int trip_cnt = int34x_zone->aux_trip_nr;
	int i;

	int34x_zone->crt_trip_id = -1;
	if (!int340x_thermal_get_trip_config(int34x_zone->adev->handle, "_CRT",
					     &int34x_zone->crt_temp))
		int34x_zone->crt_trip_id = trip_cnt++;

	int34x_zone->hot_trip_id = -1;
	if (!int340x_thermal_get_trip_config(int34x_zone->adev->handle, "_HOT",
					     &int34x_zone->hot_temp))
		int34x_zone->hot_trip_id = trip_cnt++;

	int34x_zone->psv_trip_id = -1;
	if (!int340x_thermal_get_trip_config(int34x_zone->adev->handle, "_PSV",
					     &int34x_zone->psv_temp))
		int34x_zone->psv_trip_id = trip_cnt++;

	for (i = 0; i < INT340X_THERMAL_MAX_ACT_TRIP_COUNT; i++) {
		char name[5] = { '_', 'A', 'C', '0' + i, '\0' };

		if (int340x_thermal_get_trip_config(int34x_zone->adev->handle,
					name,
					&int34x_zone->act_trips[i].temp))
			break;

		int34x_zone->act_trips[i].id = trip_cnt++;
		int34x_zone->act_trips[i].valid = true;
	}

	return trip_cnt;
}