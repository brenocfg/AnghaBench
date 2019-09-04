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
struct TYPE_2__ {struct attribute_group const** groups; } ;
struct attribute_group {int dummy; } ;
struct thermal_zone_device {TYPE_1__ device; struct attribute_group trips_attribute_group; scalar_t__ trips; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct attribute_group**) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int create_trip_attrs (struct thermal_zone_device*,int) ; 
 struct attribute_group** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct attribute_group const**) ; 
 struct attribute_group** thermal_zone_attribute_groups ; 

int thermal_zone_create_device_groups(struct thermal_zone_device *tz,
				      int mask)
{
	const struct attribute_group **groups;
	int i, size, result;

	/* we need one extra for trips and the NULL to terminate the array */
	size = ARRAY_SIZE(thermal_zone_attribute_groups) + 2;
	/* This also takes care of API requirement to be NULL terminated */
	groups = kcalloc(size, sizeof(*groups), GFP_KERNEL);
	if (!groups)
		return -ENOMEM;

	for (i = 0; i < size - 2; i++)
		groups[i] = thermal_zone_attribute_groups[i];

	if (tz->trips) {
		result = create_trip_attrs(tz, mask);
		if (result) {
			kfree(groups);

			return result;
		}

		groups[size - 2] = &tz->trips_attribute_group;
	}

	tz->device.groups = groups;

	return 0;
}