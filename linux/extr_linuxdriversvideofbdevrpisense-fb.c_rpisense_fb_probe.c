#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rpisense_fb {struct fb_info* info; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {unsigned long smem_start; int /*<<< orphan*/  id; int /*<<< orphan*/  smem_len; } ;
struct fb_info {int flags; int /*<<< orphan*/  deferred_work; TYPE_3__ fix; int /*<<< orphan*/  screen_size; scalar_t__ screen_base; TYPE_4__* fbdefio; int /*<<< orphan*/  var; int /*<<< orphan*/ * fbops; } ;
struct TYPE_9__ {int /*<<< orphan*/  delay; } ;
struct TYPE_7__ {scalar_t__ vmem; int /*<<< orphan*/  gamma; int /*<<< orphan*/  vmemsize; int /*<<< orphan*/  vmem_work; } ;
struct TYPE_6__ {struct rpisense_fb framebuffer; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FBINFO_FLAG_DEFAULT ; 
 int FBINFO_VIRTFB ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_kmalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_deferred_io_init (struct fb_info*) ; 
 int /*<<< orphan*/  fb_info (struct fb_info*,char*,int /*<<< orphan*/ ) ; 
 struct fb_info* framebuffer_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  gamma_low ; 
 scalar_t__ lowlight ; 
 int register_framebuffer (struct fb_info*) ; 
 TYPE_1__* rpisense ; 
 TYPE_4__ rpisense_fb_defio ; 
 TYPE_3__ rpisense_fb_fix ; 
 int /*<<< orphan*/  rpisense_fb_ops ; 
 TYPE_2__ rpisense_fb_param ; 
 int /*<<< orphan*/  rpisense_fb_var ; 
 TYPE_1__* rpisense_get_dev () ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (scalar_t__) ; 
 scalar_t__ vzalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpisense_fb_probe(struct platform_device *pdev)
{
	struct fb_info *info;
	int ret = -ENOMEM;
	struct rpisense_fb *rpisense_fb;

	rpisense = rpisense_get_dev();
	rpisense_fb = &rpisense->framebuffer;

	rpisense_fb_param.vmem = vzalloc(rpisense_fb_param.vmemsize);
	if (!rpisense_fb_param.vmem)
		return ret;

	rpisense_fb_param.vmem_work = devm_kmalloc(&pdev->dev, 193, GFP_KERNEL);
	if (!rpisense_fb_param.vmem_work)
		goto err_malloc;

	info = framebuffer_alloc(0, &pdev->dev);
	if (!info) {
		dev_err(&pdev->dev, "Could not allocate framebuffer.\n");
		goto err_malloc;
	}
	rpisense_fb->info = info;

	rpisense_fb_fix.smem_start = (unsigned long)rpisense_fb_param.vmem;
	rpisense_fb_fix.smem_len = rpisense_fb_param.vmemsize;

	info->fbops = &rpisense_fb_ops;
	info->fix = rpisense_fb_fix;
	info->var = rpisense_fb_var;
	info->fbdefio = &rpisense_fb_defio;
	info->flags = FBINFO_FLAG_DEFAULT | FBINFO_VIRTFB;
	info->screen_base = rpisense_fb_param.vmem;
	info->screen_size = rpisense_fb_param.vmemsize;

	if (lowlight)
		rpisense_fb_param.gamma = gamma_low;

	fb_deferred_io_init(info);

	ret = register_framebuffer(info);
	if (ret < 0) {
		dev_err(&pdev->dev, "Could not register framebuffer.\n");
		goto err_fballoc;
	}

	fb_info(info, "%s frame buffer device\n", info->fix.id);
	schedule_delayed_work(&info->deferred_work, rpisense_fb_defio.delay);
	return 0;
err_fballoc:
	framebuffer_release(info);
err_malloc:
	vfree(rpisense_fb_param.vmem);
	return ret;
}