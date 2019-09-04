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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hid_sensor_hub_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_USAGE_SENSOR_TIME ; 
 struct hid_sensor_hub_device* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sensor_hub_device_close (struct hid_sensor_hub_device*) ; 
 int /*<<< orphan*/  sensor_hub_remove_callback (struct hid_sensor_hub_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hid_time_remove(struct platform_device *pdev)
{
	struct hid_sensor_hub_device *hsdev = dev_get_platdata(&pdev->dev);

	sensor_hub_device_close(hsdev);
	sensor_hub_remove_callback(hsdev, HID_USAGE_SENSOR_TIME);

	return 0;
}