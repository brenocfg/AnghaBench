#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mxsfb_info {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  smem_start; } ;
struct fb_info {TYPE_2__ fix; int /*<<< orphan*/  screen_base; int /*<<< orphan*/  screen_size; struct mxsfb_info* par; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_wc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxsfb_free_videomem(struct fb_info *fb_info)
{
	struct mxsfb_info *host = fb_info->par;
	struct device *dev = &host->pdev->dev;

	dma_free_wc(dev, fb_info->screen_size, fb_info->screen_base,
		    fb_info->fix.smem_start);
}