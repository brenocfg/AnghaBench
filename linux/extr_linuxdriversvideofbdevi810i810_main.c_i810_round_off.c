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
typedef  int u32 ;
struct fb_var_screeninfo {int xres; int yres; int xres_virtual; int yres_virtual; int bits_per_pixel; int left_margin; int right_margin; int hsync_len; int vmode; int upper_margin; int vsync_len; int lower_margin; scalar_t__ accel_flags; } ;

/* Variables and functions */
 int FB_VMODE_INTERLACED ; 
 int /*<<< orphan*/  round_off_xres (int*) ; 
 int /*<<< orphan*/  round_off_yres (int*,int*) ; 

__attribute__((used)) static void i810_round_off(struct fb_var_screeninfo *var)
{
	u32 xres, yres, vxres, vyres;

	/*
	 *  Presently supports only these configurations 
	 */

	xres = var->xres;
	yres = var->yres;
	vxres = var->xres_virtual;
	vyres = var->yres_virtual;

	var->bits_per_pixel += 7;
	var->bits_per_pixel &= ~7;
	
	if (var->bits_per_pixel < 8)
		var->bits_per_pixel = 8;
	if (var->bits_per_pixel > 32) 
		var->bits_per_pixel = 32;

	round_off_xres(&xres);
	if (xres < 40)
		xres = 40;
	if (xres > 2048) 
		xres = 2048;
	xres = (xres + 7) & ~7;

	if (vxres < xres) 
		vxres = xres;

	round_off_yres(&xres, &yres);
	if (yres < 1)
		yres = 1;
	if (yres >= 2048)
		yres = 2048;

	if (vyres < yres) 
		vyres = yres;

	if (var->bits_per_pixel == 32)
		var->accel_flags = 0;

	/* round of horizontal timings to nearest 8 pixels */
	var->left_margin = (var->left_margin + 4) & ~7;
	var->right_margin = (var->right_margin + 4) & ~7;
	var->hsync_len = (var->hsync_len + 4) & ~7;

	if (var->vmode & FB_VMODE_INTERLACED) {
		if (!((yres + var->upper_margin + var->vsync_len + 
		       var->lower_margin) & 1))
			var->upper_margin++;
	}
	
	var->xres = xres;
	var->yres = yres;
	var->xres_virtual = vxres;
	var->yres_virtual = vyres;
}