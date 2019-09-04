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
struct tridentfb_par {int dummy; } ;
struct fb_var_screeninfo {int xoffset; int yoffset; } ;
struct TYPE_2__ {int xres_virtual; int bits_per_pixel; } ;
struct fb_info {TYPE_1__ var; struct tridentfb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  set_screen_start (struct tridentfb_par*,unsigned int) ; 

__attribute__((used)) static int tridentfb_pan_display(struct fb_var_screeninfo *var,
				 struct fb_info *info)
{
	struct tridentfb_par *par = info->par;
	unsigned int offset;

	debug("enter\n");
	offset = (var->xoffset + (var->yoffset * info->var.xres_virtual))
		* info->var.bits_per_pixel / 32;
	set_screen_start(par, offset);
	debug("exit\n");
	return 0;
}