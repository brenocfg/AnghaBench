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
struct thermal_zone_device {int /*<<< orphan*/  lock; } ;
struct thermal_governor {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct thermal_governor* __find_governor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strim (char*) ; 
 int /*<<< orphan*/  thermal_governor_lock ; 
 int thermal_set_governor (struct thermal_zone_device*,struct thermal_governor*) ; 

int thermal_zone_device_set_policy(struct thermal_zone_device *tz,
				   char *policy)
{
	struct thermal_governor *gov;
	int ret = -EINVAL;

	mutex_lock(&thermal_governor_lock);
	mutex_lock(&tz->lock);

	gov = __find_governor(strim(policy));
	if (!gov)
		goto exit;

	ret = thermal_set_governor(tz, gov);

exit:
	mutex_unlock(&tz->lock);
	mutex_unlock(&thermal_governor_lock);

	return ret;
}