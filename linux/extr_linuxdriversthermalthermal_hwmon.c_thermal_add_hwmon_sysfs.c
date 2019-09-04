#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct thermal_zone_device {int /*<<< orphan*/  device; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int mode; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {TYPE_3__ attr; int /*<<< orphan*/  show; } ;
struct TYPE_7__ {TYPE_4__ attr; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_4__ attr; int /*<<< orphan*/  name; } ;
struct thermal_hwmon_temp {int count; int /*<<< orphan*/  device; TYPE_2__ temp_input; int /*<<< orphan*/  tz_list; int /*<<< orphan*/  hwmon_node; int /*<<< orphan*/  node; TYPE_1__ temp_crit; struct thermal_zone_device* tz; int /*<<< orphan*/  type; } ;
struct thermal_hwmon_device {int count; int /*<<< orphan*/  device; TYPE_2__ temp_input; int /*<<< orphan*/  tz_list; int /*<<< orphan*/  hwmon_node; int /*<<< orphan*/  node; TYPE_1__ temp_crit; struct thermal_zone_device* tz; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THERMAL_NAME_LENGTH ; 
 int device_create_file (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  hwmon_device_register_with_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct thermal_hwmon_temp*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct thermal_hwmon_temp*) ; 
 struct thermal_hwmon_temp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strreplace (int /*<<< orphan*/ ,char,char) ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_3__*) ; 
 int /*<<< orphan*/  temp_crit_show ; 
 int /*<<< orphan*/  temp_input_show ; 
 int /*<<< orphan*/  thermal_hwmon_list ; 
 int /*<<< orphan*/  thermal_hwmon_list_lock ; 
 struct thermal_hwmon_temp* thermal_hwmon_lookup_by_type (struct thermal_zone_device*) ; 
 scalar_t__ thermal_zone_crit_temp_valid (struct thermal_zone_device*) ; 

int thermal_add_hwmon_sysfs(struct thermal_zone_device *tz)
{
	struct thermal_hwmon_device *hwmon;
	struct thermal_hwmon_temp *temp;
	int new_hwmon_device = 1;
	int result;

	hwmon = thermal_hwmon_lookup_by_type(tz);
	if (hwmon) {
		new_hwmon_device = 0;
		goto register_sys_interface;
	}

	hwmon = kzalloc(sizeof(*hwmon), GFP_KERNEL);
	if (!hwmon)
		return -ENOMEM;

	INIT_LIST_HEAD(&hwmon->tz_list);
	strlcpy(hwmon->type, tz->type, THERMAL_NAME_LENGTH);
	strreplace(hwmon->type, '-', '_');
	hwmon->device = hwmon_device_register_with_info(&tz->device, hwmon->type,
							hwmon, NULL, NULL);
	if (IS_ERR(hwmon->device)) {
		result = PTR_ERR(hwmon->device);
		goto free_mem;
	}

 register_sys_interface:
	temp = kzalloc(sizeof(*temp), GFP_KERNEL);
	if (!temp) {
		result = -ENOMEM;
		goto unregister_name;
	}

	temp->tz = tz;
	hwmon->count++;

	snprintf(temp->temp_input.name, sizeof(temp->temp_input.name),
		 "temp%d_input", hwmon->count);
	temp->temp_input.attr.attr.name = temp->temp_input.name;
	temp->temp_input.attr.attr.mode = 0444;
	temp->temp_input.attr.show = temp_input_show;
	sysfs_attr_init(&temp->temp_input.attr.attr);
	result = device_create_file(hwmon->device, &temp->temp_input.attr);
	if (result)
		goto free_temp_mem;

	if (thermal_zone_crit_temp_valid(tz)) {
		snprintf(temp->temp_crit.name,
				sizeof(temp->temp_crit.name),
				"temp%d_crit", hwmon->count);
		temp->temp_crit.attr.attr.name = temp->temp_crit.name;
		temp->temp_crit.attr.attr.mode = 0444;
		temp->temp_crit.attr.show = temp_crit_show;
		sysfs_attr_init(&temp->temp_crit.attr.attr);
		result = device_create_file(hwmon->device,
					    &temp->temp_crit.attr);
		if (result)
			goto unregister_input;
	}

	mutex_lock(&thermal_hwmon_list_lock);
	if (new_hwmon_device)
		list_add_tail(&hwmon->node, &thermal_hwmon_list);
	list_add_tail(&temp->hwmon_node, &hwmon->tz_list);
	mutex_unlock(&thermal_hwmon_list_lock);

	return 0;

 unregister_input:
	device_remove_file(hwmon->device, &temp->temp_input.attr);
 free_temp_mem:
	kfree(temp);
 unregister_name:
	if (new_hwmon_device)
		hwmon_device_unregister(hwmon->device);
 free_mem:
	if (new_hwmon_device)
		kfree(hwmon);

	return result;
}