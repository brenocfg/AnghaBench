#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct vbe_mode_ib {int dummy; } ;
struct TYPE_5__ {int total_memory; } ;
struct uvesafb_par {struct vbe_mode_ib* vbe_modes; TYPE_1__ vbe_ib; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_4__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  modedb; } ;
struct TYPE_6__ {int smem_len; int /*<<< orphan*/  smem_start; int /*<<< orphan*/  id; } ;
struct fb_info {int /*<<< orphan*/  cmap; TYPE_3__ monspecs; int /*<<< orphan*/  modelist; TYPE_2__ fix; int /*<<< orphan*/  screen_base; int /*<<< orphan*/ * fbops; struct uvesafb_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int ENXIO ; 
 scalar_t__ fb_alloc_cmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_destroy_modedb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_destroy_modelist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_info (struct fb_info*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_warn (struct fb_info*,char*) ; 
 struct fb_info* framebuffer_alloc (int,TYPE_4__*) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vbe_mode_ib*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fb_info*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ register_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_region (int,int) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  request_region (int,int,char*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvesafb_dev_attgrp ; 
 int /*<<< orphan*/  uvesafb_init_info (struct fb_info*,struct vbe_mode_ib*) ; 
 int /*<<< orphan*/  uvesafb_init_mtrr (struct fb_info*) ; 
 int /*<<< orphan*/  uvesafb_ioremap (struct fb_info*) ; 
 int /*<<< orphan*/  uvesafb_ops ; 
 int uvesafb_vbe_init (struct fb_info*) ; 
 int uvesafb_vbe_init_mode (struct fb_info*) ; 

__attribute__((used)) static int uvesafb_probe(struct platform_device *dev)
{
	struct fb_info *info;
	struct vbe_mode_ib *mode = NULL;
	struct uvesafb_par *par;
	int err = 0, i;

	info = framebuffer_alloc(sizeof(*par) +	sizeof(u32) * 256, &dev->dev);
	if (!info)
		return -ENOMEM;

	par = info->par;

	err = uvesafb_vbe_init(info);
	if (err) {
		pr_err("vbe_init() failed with %d\n", err);
		goto out;
	}

	info->fbops = &uvesafb_ops;

	i = uvesafb_vbe_init_mode(info);
	if (i < 0) {
		err = -EINVAL;
		goto out;
	} else {
		mode = &par->vbe_modes[i];
	}

	if (fb_alloc_cmap(&info->cmap, 256, 0) < 0) {
		err = -ENXIO;
		goto out;
	}

	uvesafb_init_info(info, mode);

	if (!request_region(0x3c0, 32, "uvesafb")) {
		pr_err("request region 0x3c0-0x3e0 failed\n");
		err = -EIO;
		goto out_mode;
	}

	if (!request_mem_region(info->fix.smem_start, info->fix.smem_len,
				"uvesafb")) {
		pr_err("cannot reserve video memory at 0x%lx\n",
		       info->fix.smem_start);
		err = -EIO;
		goto out_reg;
	}

	uvesafb_init_mtrr(info);
	uvesafb_ioremap(info);

	if (!info->screen_base) {
		pr_err("abort, cannot ioremap 0x%x bytes of video memory at 0x%lx\n",
		       info->fix.smem_len, info->fix.smem_start);
		err = -EIO;
		goto out_mem;
	}

	platform_set_drvdata(dev, info);

	if (register_framebuffer(info) < 0) {
		pr_err("failed to register framebuffer device\n");
		err = -EINVAL;
		goto out_unmap;
	}

	pr_info("framebuffer at 0x%lx, mapped to 0x%p, using %dk, total %dk\n",
		info->fix.smem_start, info->screen_base,
		info->fix.smem_len / 1024, par->vbe_ib.total_memory * 64);
	fb_info(info, "%s frame buffer device\n", info->fix.id);

	err = sysfs_create_group(&dev->dev.kobj, &uvesafb_dev_attgrp);
	if (err != 0)
		fb_warn(info, "failed to register attributes\n");

	return 0;

out_unmap:
	iounmap(info->screen_base);
out_mem:
	release_mem_region(info->fix.smem_start, info->fix.smem_len);
out_reg:
	release_region(0x3c0, 32);
out_mode:
	if (!list_empty(&info->modelist))
		fb_destroy_modelist(&info->modelist);
	fb_destroy_modedb(info->monspecs.modedb);
	fb_dealloc_cmap(&info->cmap);
out:
	kfree(par->vbe_modes);

	framebuffer_release(info);
	return err;
}