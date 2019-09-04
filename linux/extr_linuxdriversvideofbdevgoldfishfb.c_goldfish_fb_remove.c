#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  smem_start; } ;
struct TYPE_5__ {int xres_virtual; int yres_virtual; } ;
struct TYPE_6__ {TYPE_1__ fix; scalar_t__ screen_base; TYPE_2__ var; } ;
struct goldfish_fb {int /*<<< orphan*/  reg_base; TYPE_3__ fb; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct goldfish_fb*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct goldfish_fb*) ; 
 struct goldfish_fb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_framebuffer (TYPE_3__*) ; 

__attribute__((used)) static int goldfish_fb_remove(struct platform_device *pdev)
{
	size_t framesize;
	struct goldfish_fb *fb = platform_get_drvdata(pdev);

	framesize = fb->fb.var.xres_virtual * fb->fb.var.yres_virtual * 2;
	unregister_framebuffer(&fb->fb);
	free_irq(fb->irq, fb);

	dma_free_coherent(&pdev->dev, framesize, (void *)fb->fb.screen_base,
						fb->fb.fix.smem_start);
	iounmap(fb->reg_base);
	kfree(fb);
	return 0;
}