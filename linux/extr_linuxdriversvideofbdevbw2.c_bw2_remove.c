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
struct platform_device {int /*<<< orphan*/ * resource; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int smem_len; } ;
struct fb_info {TYPE_1__ fix; int /*<<< orphan*/  screen_base; struct bw2_par* par; } ;
struct bw2_regs {int dummy; } ;
struct bw2_par {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 struct fb_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int bw2_remove(struct platform_device *op)
{
	struct fb_info *info = dev_get_drvdata(&op->dev);
	struct bw2_par *par = info->par;

	unregister_framebuffer(info);

	of_iounmap(&op->resource[0], par->regs, sizeof(struct bw2_regs));
	of_iounmap(&op->resource[0], info->screen_base, info->fix.smem_len);

	framebuffer_release(info);

	return 0;
}