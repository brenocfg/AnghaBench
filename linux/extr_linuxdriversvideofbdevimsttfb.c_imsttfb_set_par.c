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
struct imstt_par {int dummy; } ;
struct TYPE_3__ {int length; } ;
struct TYPE_4__ {int pixclock; int /*<<< orphan*/  bits_per_pixel; TYPE_1__ green; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;
struct fb_info {TYPE_2__ var; struct imstt_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  compute_imstt_regvals (struct imstt_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int getclkMHz (struct imstt_par*) ; 
 int /*<<< orphan*/  set_555 (struct imstt_par*) ; 
 int /*<<< orphan*/  set_565 (struct imstt_par*) ; 
 int /*<<< orphan*/  set_imstt_regvals (struct fb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imsttfb_set_par(struct fb_info *info) 
{
	struct imstt_par *par = info->par;
		
	if (!compute_imstt_regvals(par, info->var.xres, info->var.yres))
		return -EINVAL;

	if (info->var.green.length == 6)
		set_565(par);
	else
		set_555(par);
	set_imstt_regvals(info, info->var.bits_per_pixel);
	info->var.pixclock = 1000000 / getclkMHz(par);
	return 0;
}