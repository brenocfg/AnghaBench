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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; } ;
struct fb_info {int /*<<< orphan*/  flags; int /*<<< orphan*/ * par; int /*<<< orphan*/ * pseudo_palette; int /*<<< orphan*/  screen_size; TYPE_1__ fix; int /*<<< orphan*/ * fbops; int /*<<< orphan*/  screen_base; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FBINFO_DEFAULT ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  cobalt_lcd_fbops ; 
 TYPE_1__ cobalt_lcdfb_fix ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_info (struct fb_info*,char*) ; 
 struct fb_info* framebuffer_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  lcd_clear (struct fb_info*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fb_info*) ; 
 int register_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int cobalt_lcdfb_probe(struct platform_device *dev)
{
	struct fb_info *info;
	struct resource *res;
	int retval;

	info = framebuffer_alloc(0, &dev->dev);
	if (!info)
		return -ENOMEM;

	res = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (!res) {
		framebuffer_release(info);
		return -EBUSY;
	}

	info->screen_size = resource_size(res);
	info->screen_base = devm_ioremap(&dev->dev, res->start,
					 info->screen_size);
	if (!info->screen_base) {
		framebuffer_release(info);
		return -ENOMEM;
	}

	info->fbops = &cobalt_lcd_fbops;
	info->fix = cobalt_lcdfb_fix;
	info->fix.smem_start = res->start;
	info->fix.smem_len = info->screen_size;
	info->pseudo_palette = NULL;
	info->par = NULL;
	info->flags = FBINFO_DEFAULT;

	retval = register_framebuffer(info);
	if (retval < 0) {
		framebuffer_release(info);
		return retval;
	}

	platform_set_drvdata(dev, info);

	lcd_clear(info);

	fb_info(info, "Cobalt server LCD frame buffer device\n");

	return 0;
}