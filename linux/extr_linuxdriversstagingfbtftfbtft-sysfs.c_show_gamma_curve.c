#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  curves; } ;
struct fbtft_par {TYPE_1__ gamma; } ;
struct fb_info {struct fbtft_par* par; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct fb_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf_gamma (struct fbtft_par*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t show_gamma_curve(struct device *device,
				struct device_attribute *attr, char *buf)
{
	struct fb_info *fb_info = dev_get_drvdata(device);
	struct fbtft_par *par = fb_info->par;

	return sprintf_gamma(par, par->gamma.curves, buf);
}