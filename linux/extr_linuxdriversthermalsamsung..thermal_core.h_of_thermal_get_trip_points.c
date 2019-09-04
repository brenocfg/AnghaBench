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
struct thermal_zone_device {int dummy; } ;
struct thermal_trip {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline const struct thermal_trip *
of_thermal_get_trip_points(struct thermal_zone_device *tz)
{
	return NULL;
}