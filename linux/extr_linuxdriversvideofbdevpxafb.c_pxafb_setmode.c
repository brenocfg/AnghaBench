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
struct pxafb_mode_info {int /*<<< orphan*/  depth; int /*<<< orphan*/  transparency; int /*<<< orphan*/  cmap_greyscale; int /*<<< orphan*/  sync; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  left_margin; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  pixclock; int /*<<< orphan*/  bpp; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;
struct fb_var_screeninfo {TYPE_1__ transp; int /*<<< orphan*/  grayscale; int /*<<< orphan*/  sync; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  left_margin; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  pixclock; int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;

/* Variables and functions */
 int /*<<< orphan*/  pxafb_set_pixfmt (struct fb_var_screeninfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pxafb_setmode(struct fb_var_screeninfo *var,
			  struct pxafb_mode_info *mode)
{
	var->xres		= mode->xres;
	var->yres		= mode->yres;
	var->bits_per_pixel	= mode->bpp;
	var->pixclock		= mode->pixclock;
	var->hsync_len		= mode->hsync_len;
	var->left_margin	= mode->left_margin;
	var->right_margin	= mode->right_margin;
	var->vsync_len		= mode->vsync_len;
	var->upper_margin	= mode->upper_margin;
	var->lower_margin	= mode->lower_margin;
	var->sync		= mode->sync;
	var->grayscale		= mode->cmap_greyscale;
	var->transp.length	= mode->transparency;

	/* set the initial RGBA bitfields */
	pxafb_set_pixfmt(var, mode->depth);
}