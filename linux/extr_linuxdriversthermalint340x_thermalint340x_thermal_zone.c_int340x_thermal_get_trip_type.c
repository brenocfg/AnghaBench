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
struct int34x_thermal_zone {int aux_trip_nr; int crt_trip_id; int hot_trip_id; int psv_trip_id; TYPE_2__* act_trips; TYPE_1__* override_ops; } ;
typedef  enum thermal_trip_type { ____Placeholder_thermal_trip_type } thermal_trip_type ;
struct TYPE_4__ {int id; scalar_t__ valid; } ;
struct TYPE_3__ {int (* get_trip_type ) (struct thermal_zone_device*,int,int*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int INT340X_THERMAL_MAX_ACT_TRIP_COUNT ; 
 int THERMAL_TRIP_ACTIVE ; 
 int THERMAL_TRIP_CRITICAL ; 
 int THERMAL_TRIP_HOT ; 
 int THERMAL_TRIP_PASSIVE ; 
 int stub1 (struct thermal_zone_device*,int,int*) ; 

__attribute__((used)) static int int340x_thermal_get_trip_type(struct thermal_zone_device *zone,
					 int trip,
					 enum thermal_trip_type *type)
{
	struct int34x_thermal_zone *d = zone->devdata;
	int i;

	if (d->override_ops && d->override_ops->get_trip_type)
		return d->override_ops->get_trip_type(zone, trip, type);

	if (trip < d->aux_trip_nr)
		*type = THERMAL_TRIP_PASSIVE;
	else if (trip == d->crt_trip_id)
		*type = THERMAL_TRIP_CRITICAL;
	else if (trip == d->hot_trip_id)
		*type = THERMAL_TRIP_HOT;
	else if (trip == d->psv_trip_id)
		*type = THERMAL_TRIP_PASSIVE;
	else {
		for (i = 0; i < INT340X_THERMAL_MAX_ACT_TRIP_COUNT; i++) {
			if (d->act_trips[i].valid &&
			    d->act_trips[i].id == trip) {
				*type = THERMAL_TRIP_ACTIVE;
				break;
			}
		}
		if (i == INT340X_THERMAL_MAX_ACT_TRIP_COUNT)
			return -EINVAL;
	}

	return 0;
}