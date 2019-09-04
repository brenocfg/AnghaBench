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
struct savagefb_par {scalar_t__ dacSpeedBpp; scalar_t__* clock; scalar_t__ maxClock; int minClock; int /*<<< orphan*/  state; } ;
struct fb_var_screeninfo {int bits_per_pixel; } ;
struct fb_info {int /*<<< orphan*/  cmap; struct fb_var_screeninfo var; struct savagefb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  SavagePrintRegs (struct savagefb_par*) ; 
 int /*<<< orphan*/  fb_set_cmap (int /*<<< orphan*/ *,struct fb_info*) ; 
 int savagefb_decode_var (struct fb_var_screeninfo*,struct savagefb_par*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  savagefb_set_clip (struct fb_info*) ; 
 int /*<<< orphan*/  savagefb_set_fix (struct fb_info*) ; 
 int /*<<< orphan*/  savagefb_set_par_int (struct savagefb_par*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int savagefb_set_par(struct fb_info *info)
{
	struct savagefb_par *par = info->par;
	struct fb_var_screeninfo *var = &info->var;
	int err;

	DBG("savagefb_set_par");
	err = savagefb_decode_var(var, par, &par->state);
	if (err)
		return err;

	if (par->dacSpeedBpp <= 0) {
		if (var->bits_per_pixel > 24)
			par->dacSpeedBpp = par->clock[3];
		else if (var->bits_per_pixel >= 24)
			par->dacSpeedBpp = par->clock[2];
		else if ((var->bits_per_pixel > 8) && (var->bits_per_pixel < 24))
			par->dacSpeedBpp = par->clock[1];
		else if (var->bits_per_pixel <= 8)
			par->dacSpeedBpp = par->clock[0];
	}

	/* Set ramdac limits */
	par->maxClock = par->dacSpeedBpp;
	par->minClock = 10000;

	savagefb_set_par_int(par, &par->state);
	fb_set_cmap(&info->cmap, info);
	savagefb_set_fix(info);
	savagefb_set_clip(info);

	SavagePrintRegs(par);
	return 0;
}