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
struct ffb_par {int /*<<< orphan*/  dac; int /*<<< orphan*/  fbc; } ;
struct ffb_fbc {int dummy; } ;
struct ffb_dac {int dummy; } ;
struct fb_info {int /*<<< orphan*/  cmap; struct ffb_par* par; } ;

/* Variables and functions */
 struct fb_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int ffb_remove(struct platform_device *op)
{
	struct fb_info *info = dev_get_drvdata(&op->dev);
	struct ffb_par *par = info->par;

	unregister_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);

	of_iounmap(&op->resource[2], par->fbc, sizeof(struct ffb_fbc));
	of_iounmap(&op->resource[1], par->dac, sizeof(struct ffb_dac));

	framebuffer_release(info);

	return 0;
}