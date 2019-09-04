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
struct sh_mobile_lcdc_overlay {unsigned int rop3; scalar_t__ mode; scalar_t__ enabled; } ;
struct fb_info {struct sh_mobile_lcdc_overlay* par; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ LCDC_OVERLAY_ROP3 ; 
 struct fb_info* dev_get_drvdata (struct device*) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_overlay_setup (struct sh_mobile_lcdc_overlay*) ; 
 unsigned int simple_strtoul (char const*,char**,int) ; 

__attribute__((used)) static ssize_t
overlay_rop3_store(struct device *dev, struct device_attribute *attr,
		    const char *buf, size_t count)
{
	struct fb_info *info = dev_get_drvdata(dev);
	struct sh_mobile_lcdc_overlay *ovl = info->par;
	unsigned int rop3;
	char *endp;

	rop3 = simple_strtoul(buf, &endp, 10);
	if (isspace(*endp))
		endp++;

	if (endp - buf != count)
		return -EINVAL;

	if (rop3 > 255)
		return -EINVAL;

	if (ovl->rop3 != rop3) {
		ovl->rop3 = rop3;

		if (ovl->mode == LCDC_OVERLAY_ROP3 && ovl->enabled)
			sh_mobile_lcdc_overlay_setup(ovl);
	}

	return count;
}