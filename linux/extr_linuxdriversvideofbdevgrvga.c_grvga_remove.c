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
struct platform_device {int /*<<< orphan*/ * resource; int /*<<< orphan*/  dev; } ;
struct grvga_par {int /*<<< orphan*/  fb_alloced; int /*<<< orphan*/  regs; } ;
struct fb_info {scalar_t__ screen_base; int /*<<< orphan*/  cmap; struct grvga_par* par; } ;

/* Variables and functions */
 struct fb_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int grvga_remove(struct platform_device *device)
{
	struct fb_info *info = dev_get_drvdata(&device->dev);
	struct grvga_par *par;

	if (info) {
		par = info->par;
		unregister_framebuffer(info);
		fb_dealloc_cmap(&info->cmap);

		of_iounmap(&device->resource[0], par->regs,
			   resource_size(&device->resource[0]));

		if (!par->fb_alloced)
			iounmap(info->screen_base);
		else
			kfree((void *)info->screen_base);

		framebuffer_release(info);
	}

	return 0;
}