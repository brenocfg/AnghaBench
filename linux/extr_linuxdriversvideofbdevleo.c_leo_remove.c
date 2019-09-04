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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct leo_par {int dummy; } ;
struct fb_info {int /*<<< orphan*/  cmap; struct leo_par* par; } ;

/* Variables and functions */
 struct fb_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  leo_unmap_regs (struct platform_device*,struct fb_info*,struct leo_par*) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int leo_remove(struct platform_device *op)
{
	struct fb_info *info = dev_get_drvdata(&op->dev);
	struct leo_par *par = info->par;

	unregister_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);

	leo_unmap_regs(op, info, par);

	framebuffer_release(info);

	return 0;
}