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
struct sh7760fb_par {scalar_t__ irq; TYPE_1__* ioarea; int /*<<< orphan*/  base; int /*<<< orphan*/  vsync; } ;
struct platform_device {int dummy; } ;
struct fb_info {int /*<<< orphan*/  cmap; struct sh7760fb_par* par; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct fb_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 
 int /*<<< orphan*/  sh7760fb_blank (int /*<<< orphan*/ ,struct fb_info*) ; 
 int /*<<< orphan*/  sh7760fb_free_mem (struct fb_info*) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int sh7760fb_remove(struct platform_device *dev)
{
	struct fb_info *info = platform_get_drvdata(dev);
	struct sh7760fb_par *par = info->par;

	sh7760fb_blank(FB_BLANK_POWERDOWN, info);
	unregister_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);
	sh7760fb_free_mem(info);
	if (par->irq >= 0)
		free_irq(par->irq, &par->vsync);
	iounmap(par->base);
	release_mem_region(par->ioarea->start, resource_size(par->ioarea));
	framebuffer_release(info);

	return 0;
}