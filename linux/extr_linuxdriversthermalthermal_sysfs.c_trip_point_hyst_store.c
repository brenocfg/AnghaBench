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
struct thermal_zone_device {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_2__ attr; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int (* set_trip_hyst ) (struct thermal_zone_device*,int,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ kstrtoint (char const*,int,int*) ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*) ; 
 int stub1 (struct thermal_zone_device*,int,int) ; 
 int /*<<< orphan*/  thermal_zone_set_trips (struct thermal_zone_device*) ; 
 struct thermal_zone_device* to_thermal_zone (struct device*) ; 

__attribute__((used)) static ssize_t
trip_point_hyst_store(struct device *dev, struct device_attribute *attr,
		      const char *buf, size_t count)
{
	struct thermal_zone_device *tz = to_thermal_zone(dev);
	int trip, ret;
	int temperature;

	if (!tz->ops->set_trip_hyst)
		return -EPERM;

	if (sscanf(attr->attr.name, "trip_point_%d_hyst", &trip) != 1)
		return -EINVAL;

	if (kstrtoint(buf, 10, &temperature))
		return -EINVAL;

	/*
	 * We are not doing any check on the 'temperature' value
	 * here. The driver implementing 'set_trip_hyst' has to
	 * take care of this.
	 */
	ret = tz->ops->set_trip_hyst(tz, trip, temperature);

	if (!ret)
		thermal_zone_set_trips(tz);

	return ret ? ret : count;
}