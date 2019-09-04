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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct thermal_zone_device {int type; int temperature; int notify_event; int /*<<< orphan*/  lock; TYPE_1__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int notify_user_space(struct thermal_zone_device *tz, int trip)
{
	char *thermal_prop[5];
	int i;

	mutex_lock(&tz->lock);
	thermal_prop[0] = kasprintf(GFP_KERNEL, "NAME=%s", tz->type);
	thermal_prop[1] = kasprintf(GFP_KERNEL, "TEMP=%d", tz->temperature);
	thermal_prop[2] = kasprintf(GFP_KERNEL, "TRIP=%d", trip);
	thermal_prop[3] = kasprintf(GFP_KERNEL, "EVENT=%d", tz->notify_event);
	thermal_prop[4] = NULL;
	kobject_uevent_env(&tz->device.kobj, KOBJ_CHANGE, thermal_prop);
	for (i = 0; i < 4; ++i)
		kfree(thermal_prop[i]);
	mutex_unlock(&tz->lock);
	return 0;
}