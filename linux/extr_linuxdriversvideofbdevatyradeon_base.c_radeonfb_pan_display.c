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
struct radeonfb_info {scalar_t__ asleep; } ;
struct fb_var_screeninfo {int xoffset; int yoffset; } ;
struct TYPE_4__ {scalar_t__ xres; scalar_t__ xres_virtual; scalar_t__ yres; scalar_t__ yres_virtual; int bits_per_pixel; } ;
struct TYPE_3__ {int line_length; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ fix; struct radeonfb_info* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_OFFSET ; 
 int EINVAL ; 
 int /*<<< orphan*/  OUTREG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_fifo_wait (int) ; 

__attribute__((used)) static int radeonfb_pan_display (struct fb_var_screeninfo *var,
                                 struct fb_info *info)
{
        struct radeonfb_info *rinfo = info->par;

	if ((var->xoffset + info->var.xres > info->var.xres_virtual)
	    || (var->yoffset + info->var.yres > info->var.yres_virtual))
		return -EINVAL;
                
        if (rinfo->asleep)
        	return 0;

	radeon_fifo_wait(2);
	OUTREG(CRTC_OFFSET, (var->yoffset * info->fix.line_length +
			     var->xoffset * info->var.bits_per_pixel / 8) & ~7);
        return 0;
}