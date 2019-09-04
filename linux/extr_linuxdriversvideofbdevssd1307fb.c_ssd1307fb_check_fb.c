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
struct fb_info {struct backlight_device* bl_dev; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int ssd1307fb_check_fb(struct backlight_device *bdev,
				   struct fb_info *info)
{
	return (info->bl_dev == bdev);
}