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
struct platform_device {int dummy; } ;
struct fb_info {int /*<<< orphan*/  cmap; struct ep93xx_fbi* par; } ;
struct ep93xx_fbi {TYPE_1__* mach_info; int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* teardown ) (struct platform_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep93xxfb_dealloc_videomem (struct fb_info*) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct fb_info*) ; 
 struct fb_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int ep93xxfb_remove(struct platform_device *pdev)
{
	struct fb_info *info = platform_get_drvdata(pdev);
	struct ep93xx_fbi *fbi = info->par;

	unregister_framebuffer(info);
	clk_disable(fbi->clk);
	ep93xxfb_dealloc_videomem(info);
	fb_dealloc_cmap(&info->cmap);

	if (fbi->mach_info->teardown)
		fbi->mach_info->teardown(pdev);

	kfree(info);

	return 0;
}