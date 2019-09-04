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
typedef  int u32 ;
struct pm3_par {int /*<<< orphan*/  base; } ;
struct fb_var_screeninfo {int const yoffset; scalar_t__ xoffset; } ;
struct TYPE_2__ {int xres; int /*<<< orphan*/  bits_per_pixel; } ;
struct fb_info {TYPE_1__ var; struct pm3_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM3ScreenBase ; 
 int /*<<< orphan*/  PM3_WAIT (struct pm3_par*,int) ; 
 int /*<<< orphan*/  PM3_WRITE_REG (struct pm3_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm3fb_shift_bpp (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pm3fb_pan_display(struct fb_var_screeninfo *var,
				 struct fb_info *info)
{
	struct pm3_par *par = info->par;
	const u32 xres = (info->var.xres + 31) & ~31;

	par->base = pm3fb_shift_bpp(info->var.bits_per_pixel,
					(var->yoffset * xres)
					+ var->xoffset);
	PM3_WAIT(par, 1);
	PM3_WRITE_REG(par, PM3ScreenBase, par->base);
	return 0;
}