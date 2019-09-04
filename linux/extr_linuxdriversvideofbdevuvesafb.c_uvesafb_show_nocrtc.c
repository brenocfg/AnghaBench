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
struct uvesafb_par {int nocrtc; } ;
struct fb_info {struct uvesafb_par* par; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct fb_info* platform_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  to_platform_device (struct device*) ; 

__attribute__((used)) static ssize_t uvesafb_show_nocrtc(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct fb_info *info = platform_get_drvdata(to_platform_device(dev));
	struct uvesafb_par *par = info->par;

	return snprintf(buf, PAGE_SIZE, "%d\n", par->nocrtc);
}