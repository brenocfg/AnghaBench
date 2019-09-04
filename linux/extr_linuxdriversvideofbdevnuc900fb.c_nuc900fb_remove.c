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
struct platform_device {int dummy; } ;
struct nuc900fb_info {int /*<<< orphan*/  mem; int /*<<< orphan*/  io; } ;
struct fb_info {struct nuc900fb_info* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  free_irq (int,struct nuc900fb_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  nuc900fb_cpufreq_deregister (struct nuc900fb_info*) ; 
 int /*<<< orphan*/  nuc900fb_stop_lcd (struct fb_info*) ; 
 int /*<<< orphan*/  nuc900fb_unmap_video_memory (struct fb_info*) ; 
 struct fb_info* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int nuc900fb_remove(struct platform_device *pdev)
{
	struct fb_info *fbinfo = platform_get_drvdata(pdev);
	struct nuc900fb_info *fbi = fbinfo->par;
	int irq;

	nuc900fb_stop_lcd(fbinfo);
	msleep(1);

	unregister_framebuffer(fbinfo);
	nuc900fb_cpufreq_deregister(fbi);
	nuc900fb_unmap_video_memory(fbinfo);

	iounmap(fbi->io);

	irq = platform_get_irq(pdev, 0);
	free_irq(irq, fbi);

	release_resource(fbi->mem);
	kfree(fbi->mem);

	framebuffer_release(fbinfo);

	return 0;
}