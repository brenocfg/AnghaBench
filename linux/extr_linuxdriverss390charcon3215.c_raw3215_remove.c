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
struct raw3215_info {int dummy; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int NR_3215 ; 
 int /*<<< orphan*/  ccw_device_set_offline (struct ccw_device*) ; 
 struct raw3215_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct raw3215_info** raw3215 ; 
 int /*<<< orphan*/  raw3215_device_lock ; 
 int /*<<< orphan*/  raw3215_free_info (struct raw3215_info*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raw3215_remove (struct ccw_device *cdev)
{
	struct raw3215_info *raw;
	unsigned int line;

	ccw_device_set_offline(cdev);
	raw = dev_get_drvdata(&cdev->dev);
	if (raw) {
		spin_lock(&raw3215_device_lock);
		for (line = 0; line < NR_3215; line++)
			if (raw3215[line] == raw)
				break;
		raw3215[line] = NULL;
		spin_unlock(&raw3215_device_lock);
		dev_set_drvdata(&cdev->dev, NULL);
		raw3215_free_info(raw);
	}
}