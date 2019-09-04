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
struct thermal_zone_device {struct st_thermal_sensor* devdata; } ;
struct st_thermal_sensor {TYPE_1__* cdata; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  crit_temp; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int mcelsius (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_thermal_get_trip_temp(struct thermal_zone_device *th,
				    int trip, int *temp)
{
	struct st_thermal_sensor *sensor = th->devdata;
	struct device *dev = sensor->dev;

	switch (trip) {
	case 0:
		*temp = mcelsius(sensor->cdata->crit_temp);
		break;
	default:
		dev_err(dev, "Invalid trip point\n");
		return -EINVAL;
	}

	return 0;
}