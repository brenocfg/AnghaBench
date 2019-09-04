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
struct fbtft_par {int /*<<< orphan*/  debug; } ;
struct fb_info {struct fbtft_par* par; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct fb_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  fbtft_expand_debug_value (int /*<<< orphan*/ *) ; 
 int kstrtoul (char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t store_debug(struct device *device,
			   struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct fb_info *fb_info = dev_get_drvdata(device);
	struct fbtft_par *par = fb_info->par;
	int ret;

	ret = kstrtoul(buf, 10, &par->debug);
	if (ret)
		return ret;
	fbtft_expand_debug_value(&par->debug);

	return count;
}