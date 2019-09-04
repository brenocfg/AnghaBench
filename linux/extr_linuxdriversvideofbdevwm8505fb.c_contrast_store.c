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
struct wm8505fb_info {unsigned long contrast; } ;
struct fb_info {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct fb_info* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 struct wm8505fb_info* to_wm8505fb_info (struct fb_info*) ; 
 int /*<<< orphan*/  wm8505fb_set_par (struct fb_info*) ; 

__attribute__((used)) static ssize_t contrast_store(struct device *dev,
			      struct device_attribute *attr,
			      const char *buf, size_t count)
{
	struct fb_info *info = dev_get_drvdata(dev);
	struct wm8505fb_info *fbi = to_wm8505fb_info(info);
	unsigned long tmp;

	if (kstrtoul(buf, 10, &tmp) || (tmp > 0xff))
		return -EINVAL;
	fbi->contrast = tmp;

	wm8505fb_set_par(info);

	return count;
}