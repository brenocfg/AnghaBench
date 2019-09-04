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
struct s3c2410fb_info {TYPE_1__* mem; int /*<<< orphan*/  io; int /*<<< orphan*/ * clk; } ;
struct platform_device {int dummy; } ;
struct fb_info {struct s3c2410fb_info* par; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  free_irq (int,struct s3c2410fb_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct fb_info* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 
 int /*<<< orphan*/  s3c2410fb_cpufreq_deregister (struct s3c2410fb_info*) ; 
 int /*<<< orphan*/  s3c2410fb_lcd_enable (struct s3c2410fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c2410fb_unmap_video_memory (struct fb_info*) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int s3c2410fb_remove(struct platform_device *pdev)
{
	struct fb_info *fbinfo = platform_get_drvdata(pdev);
	struct s3c2410fb_info *info = fbinfo->par;
	int irq;

	unregister_framebuffer(fbinfo);
	s3c2410fb_cpufreq_deregister(info);

	s3c2410fb_lcd_enable(info, 0);
	usleep_range(1000, 1100);

	s3c2410fb_unmap_video_memory(fbinfo);

	if (info->clk) {
		clk_disable_unprepare(info->clk);
		clk_put(info->clk);
		info->clk = NULL;
	}

	irq = platform_get_irq(pdev, 0);
	free_irq(irq, info);

	iounmap(info->io);

	release_mem_region(info->mem->start, resource_size(info->mem));

	framebuffer_release(fbinfo);

	return 0;
}