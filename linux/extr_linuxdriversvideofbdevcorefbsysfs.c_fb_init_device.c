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
struct fb_info {int /*<<< orphan*/  class_flag; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FB_SYSFS_FLAG_ATTR ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,struct fb_info*) ; 
 int /*<<< orphan*/ * device_attrs ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int fb_init_device(struct fb_info *fb_info)
{
	int i, error = 0;

	dev_set_drvdata(fb_info->dev, fb_info);

	fb_info->class_flag |= FB_SYSFS_FLAG_ATTR;

	for (i = 0; i < ARRAY_SIZE(device_attrs); i++) {
		error = device_create_file(fb_info->dev, &device_attrs[i]);

		if (error)
			break;
	}

	if (error) {
		while (--i >= 0)
			device_remove_file(fb_info->dev, &device_attrs[i]);
		fb_info->class_flag &= ~FB_SYSFS_FLAG_ATTR;
	}

	return 0;
}