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
struct fb_var_screeninfo {int vmode; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int FB_VMODE_DOUBLE ; 
 int FB_VMODE_MASK ; 
 int FB_VMODE_NONINTERLACED ; 
 scalar_t__ IS_DVT ; 
 int i810_check_params (struct fb_var_screeninfo*,struct fb_info*) ; 
 int /*<<< orphan*/  i810_round_off (struct fb_var_screeninfo*) ; 
 int /*<<< orphan*/  i810fb_fill_var_timings (struct fb_var_screeninfo*) ; 
 int /*<<< orphan*/  set_color_bitfields (struct fb_var_screeninfo*) ; 

__attribute__((used)) static int i810fb_check_var(struct fb_var_screeninfo *var, 
			    struct fb_info *info)
{
	int err;

	if (IS_DVT) {
		var->vmode &= ~FB_VMODE_MASK;
		var->vmode |= FB_VMODE_NONINTERLACED;
	}
	if (var->vmode & FB_VMODE_DOUBLE) {
		var->vmode &= ~FB_VMODE_MASK;
		var->vmode |= FB_VMODE_NONINTERLACED;
	}

	i810_round_off(var);
	if ((err = i810_check_params(var, info)))
		return err;

	i810fb_fill_var_timings(var);
	set_color_bitfields(var);
	return 0;
}