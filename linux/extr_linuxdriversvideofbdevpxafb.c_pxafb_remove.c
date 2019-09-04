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
struct TYPE_2__ {scalar_t__ len; } ;
struct fb_info {TYPE_1__ cmap; } ;
struct pxafb_info {int /*<<< orphan*/  dma_buff_phys; int /*<<< orphan*/  dma_buff; int /*<<< orphan*/  dma_buff_size; int /*<<< orphan*/  video_mem_size; int /*<<< orphan*/  video_mem; struct fb_info fb; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (TYPE_1__*) ; 
 int /*<<< orphan*/  free_pages_exact (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pxafb_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pxafb_disable_controller (struct pxafb_info*) ; 
 int /*<<< orphan*/  pxafb_overlay_exit (struct pxafb_info*) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int pxafb_remove(struct platform_device *dev)
{
	struct pxafb_info *fbi = platform_get_drvdata(dev);
	struct fb_info *info;

	if (!fbi)
		return 0;

	info = &fbi->fb;

	pxafb_overlay_exit(fbi);
	unregister_framebuffer(info);

	pxafb_disable_controller(fbi);

	if (fbi->fb.cmap.len)
		fb_dealloc_cmap(&fbi->fb.cmap);

	free_pages_exact(fbi->video_mem, fbi->video_mem_size);

	dma_free_wc(&dev->dev, fbi->dma_buff_size, fbi->dma_buff,
		    fbi->dma_buff_phys);

	return 0;
}