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
typedef  int /*<<< orphan*/  u_char ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {scalar_t__ smem_start; } ;
struct TYPE_4__ {int length; scalar_t__ offset; } ;
struct TYPE_5__ {TYPE_1__ red; TYPE_1__ blue; TYPE_1__ green; } ;
struct fb_info {int /*<<< orphan*/  cmap; TYPE_3__ fix; int /*<<< orphan*/ * screen_base; TYPE_2__ var; int /*<<< orphan*/ * fbops; } ;

/* Variables and functions */
 int AD_BLT ; 
 int /*<<< orphan*/  AP_CONTROL_0 ; 
 int /*<<< orphan*/  AP_CONTROL_1 ; 
 int /*<<< orphan*/  AP_CONTROL_2 ; 
 int /*<<< orphan*/  AP_CONTROL_3A ; 
 int /*<<< orphan*/  AP_ROP_1 ; 
 int /*<<< orphan*/  AP_WRITE_ENABLE ; 
 int DST_EQ_SRC ; 
 int ENOMEM ; 
 int NORMAL_MODE ; 
 int NORM_CREG1 ; 
 int RESET_CREG ; 
 int SWAP (int) ; 
 int S_DATA_PLN ; 
 int /*<<< orphan*/  dn_fb_ops ; 
 TYPE_3__ dnfb_fix ; 
 TYPE_2__ dnfb_var ; 
 int fb_alloc_cmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 struct fb_info* framebuffer_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fb_info*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int register_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int dnfb_probe(struct platform_device *dev)
{
	struct fb_info *info;
	int err = 0;

	info = framebuffer_alloc(0, &dev->dev);
	if (!info)
		return -ENOMEM;

	info->fbops = &dn_fb_ops;
	info->fix = dnfb_fix;
	info->var = dnfb_var;
	info->var.red.length = 1;
	info->var.red.offset = 0;
	info->var.green = info->var.blue = info->var.red;
	info->screen_base = (u_char *) info->fix.smem_start;

	err = fb_alloc_cmap(&info->cmap, 2, 0);
	if (err < 0)
		goto release_framebuffer;

	err = register_framebuffer(info);
	if (err < 0) {
		fb_dealloc_cmap(&info->cmap);
		goto release_framebuffer;
	}
	platform_set_drvdata(dev, info);

	/* now we have registered we can safely setup the hardware */
	out_8(AP_CONTROL_3A, RESET_CREG);
	out_be16(AP_WRITE_ENABLE, 0x0);
	out_8(AP_CONTROL_0, NORMAL_MODE);
	out_8(AP_CONTROL_1, (AD_BLT | DST_EQ_SRC | NORM_CREG1));
	out_8(AP_CONTROL_2, S_DATA_PLN);
	out_be16(AP_ROP_1, SWAP(0x3));

	printk("apollo frame buffer alive and kicking !\n");
	return err;

release_framebuffer:
	framebuffer_release(info);
	return err;
}