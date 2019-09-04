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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ screen_base; } ;
struct bcm2708_fb {int /*<<< orphan*/  dma_irq; int /*<<< orphan*/  dma_chan; int /*<<< orphan*/  cb_handle; int /*<<< orphan*/  cb_base; TYPE_1__ fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  SZ_64K ; 
 int /*<<< orphan*/  bcm2708_fb_debugfs_deinit (struct bcm2708_fb*) ; 
 int /*<<< orphan*/  bcm_dma_chan_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_writecombine (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bcm2708_fb*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct bcm2708_fb*) ; 
 struct bcm2708_fb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_framebuffer (TYPE_1__*) ; 

__attribute__((used)) static int bcm2708_fb_remove(struct platform_device *dev)
{
	struct bcm2708_fb *fb = platform_get_drvdata(dev);

	platform_set_drvdata(dev, NULL);

	if (fb->fb.screen_base)
		iounmap(fb->fb.screen_base);
	unregister_framebuffer(&fb->fb);

	dma_free_writecombine(&dev->dev, SZ_64K, fb->cb_base, fb->cb_handle);
	bcm_dma_chan_free(fb->dma_chan);

	bcm2708_fb_debugfs_deinit(fb);

	free_irq(fb->dma_irq, fb);

	kfree(fb);

	return 0;
}