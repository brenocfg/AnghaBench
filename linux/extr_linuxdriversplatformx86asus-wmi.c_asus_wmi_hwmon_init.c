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
struct device {int dummy; } ;
struct asus_wmi {TYPE_1__* platform_device; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  hwmon_attribute_groups ; 
 struct device* hwmon_device_register_with_groups (int /*<<< orphan*/ *,char*,struct asus_wmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int asus_wmi_hwmon_init(struct asus_wmi *asus)
{
	struct device *hwmon;

	hwmon = hwmon_device_register_with_groups(&asus->platform_device->dev,
						  "asus", asus,
						  hwmon_attribute_groups);
	if (IS_ERR(hwmon)) {
		pr_err("Could not register asus hwmon device\n");
		return PTR_ERR(hwmon);
	}
	return 0;
}