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
struct rpisense_fb {struct fb_info* info; } ;
struct platform_device {int dummy; } ;
struct fb_info {int dummy; } ;
struct TYPE_4__ {struct rpisense_fb framebuffer; } ;
struct TYPE_3__ {int /*<<< orphan*/  vmem; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_deferred_io_cleanup (struct fb_info*) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 TYPE_2__* rpisense ; 
 TYPE_1__ rpisense_fb_param ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpisense_fb_remove(struct platform_device *pdev)
{
	struct rpisense_fb *rpisense_fb = &rpisense->framebuffer;
	struct fb_info *info = rpisense_fb->info;

	if (info) {
		unregister_framebuffer(info);
		fb_deferred_io_cleanup(info);
		framebuffer_release(info);
		vfree(rpisense_fb_param.vmem);
	}

	return 0;
}