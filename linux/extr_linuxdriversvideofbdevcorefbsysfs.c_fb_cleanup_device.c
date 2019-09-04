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
struct fb_info {int class_flag; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int FB_SYSFS_FLAG_ATTR ; 
 int /*<<< orphan*/ * device_attrs ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void fb_cleanup_device(struct fb_info *fb_info)
{
	unsigned int i;

	if (fb_info->class_flag & FB_SYSFS_FLAG_ATTR) {
		for (i = 0; i < ARRAY_SIZE(device_attrs); i++)
			device_remove_file(fb_info->dev, &device_attrs[i]);

		fb_info->class_flag &= ~FB_SYSFS_FLAG_ATTR;
	}
}