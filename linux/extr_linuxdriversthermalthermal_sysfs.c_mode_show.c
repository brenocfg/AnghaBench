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
struct thermal_zone_device {TYPE_1__* ops; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  enum thermal_device_mode { ____Placeholder_thermal_device_mode } thermal_device_mode ;
struct TYPE_2__ {int (* get_mode ) (struct thermal_zone_device*,int*) ;} ;

/* Variables and functions */
 int EPERM ; 
 int THERMAL_DEVICE_ENABLED ; 
 int sprintf (char*,char*,char*) ; 
 int stub1 (struct thermal_zone_device*,int*) ; 
 struct thermal_zone_device* to_thermal_zone (struct device*) ; 

__attribute__((used)) static ssize_t
mode_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct thermal_zone_device *tz = to_thermal_zone(dev);
	enum thermal_device_mode mode;
	int result;

	if (!tz->ops->get_mode)
		return -EPERM;

	result = tz->ops->get_mode(tz, &mode);
	if (result)
		return result;

	return sprintf(buf, "%s\n", mode == THERMAL_DEVICE_ENABLED ? "enabled"
		       : "disabled");
}