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
struct fb_videomode {int /*<<< orphan*/  sync; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  left_margin; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; int /*<<< orphan*/  pixclock; } ;
struct fb_var_screeninfo {int /*<<< orphan*/  sync; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  left_margin; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; int /*<<< orphan*/  pixclock; } ;

/* Variables and functions */

void viafb_fill_var_timing_info(struct fb_var_screeninfo *var,
	const struct fb_videomode *mode)
{
	var->pixclock = mode->pixclock;
	var->xres = mode->xres;
	var->yres = mode->yres;
	var->left_margin = mode->left_margin;
	var->right_margin = mode->right_margin;
	var->hsync_len = mode->hsync_len;
	var->upper_margin = mode->upper_margin;
	var->lower_margin = mode->lower_margin;
	var->vsync_len = mode->vsync_len;
	var->sync = mode->sync;
}