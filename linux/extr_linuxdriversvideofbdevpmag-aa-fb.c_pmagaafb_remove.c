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
struct TYPE_2__ {scalar_t__ end; scalar_t__ start; } ;
struct tc_dev {TYPE_1__ resource; } ;
struct fb_info {int /*<<< orphan*/  screen_base; struct aafb_par* par; } ;
struct device {int dummy; } ;
struct aafb_par {int /*<<< orphan*/  mmio; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 struct fb_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,scalar_t__) ; 
 struct tc_dev* to_tc_dev (struct device*) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int pmagaafb_remove(struct device *dev)
{
	struct tc_dev *tdev = to_tc_dev(dev);
	struct fb_info *info = dev_get_drvdata(dev);
	struct aafb_par *par = info->par;
	resource_size_t start, len;

	put_device(dev);
	unregister_framebuffer(info);
	iounmap(info->screen_base);
	iounmap(par->mmio);
	start = tdev->resource.start;
	len = tdev->resource.end - start + 1;
	release_mem_region(start, len);
	framebuffer_release(info);
	return 0;
}