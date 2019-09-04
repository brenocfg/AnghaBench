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
struct sh_mobile_lcdc_overlay {int pos_x; int pos_y; scalar_t__ enabled; } ;
struct fb_info {struct sh_mobile_lcdc_overlay* par; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct fb_info* dev_get_drvdata (struct device*) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_overlay_setup (struct sh_mobile_lcdc_overlay*) ; 
 int simple_strtol (char const*,char**,int) ; 

__attribute__((used)) static ssize_t
overlay_position_store(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	struct fb_info *info = dev_get_drvdata(dev);
	struct sh_mobile_lcdc_overlay *ovl = info->par;
	char *endp;
	int pos_x;
	int pos_y;

	pos_x = simple_strtol(buf, &endp, 10);
	if (*endp != ',')
		return -EINVAL;

	pos_y = simple_strtol(endp + 1, &endp, 10);
	if (isspace(*endp))
		endp++;

	if (endp - buf != count)
		return -EINVAL;

	if (ovl->pos_x != pos_x || ovl->pos_y != pos_y) {
		ovl->pos_x = pos_x;
		ovl->pos_y = pos_y;

		if (ovl->enabled)
			sh_mobile_lcdc_overlay_setup(ovl);
	}

	return count;
}