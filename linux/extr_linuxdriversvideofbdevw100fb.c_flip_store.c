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
struct w100fb_par {int flip; } ;
struct fb_info {struct w100fb_par* par; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  calc_hsync (struct w100fb_par*) ; 
 struct fb_info* dev_get_drvdata (struct device*) ; 
 unsigned int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  w100_set_dispregs (struct w100fb_par*) ; 
 int /*<<< orphan*/  w100_update_disable () ; 
 int /*<<< orphan*/  w100_update_enable () ; 

__attribute__((used)) static ssize_t flip_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned int flip;
	struct fb_info *info = dev_get_drvdata(dev);
	struct w100fb_par *par=info->par;

	flip = simple_strtoul(buf, NULL, 10);

	if (flip > 0)
		par->flip = 1;
	else
		par->flip = 0;

	w100_update_disable();
	w100_set_dispregs(par);
	w100_update_enable();

	calc_hsync(par);

	return count;
}