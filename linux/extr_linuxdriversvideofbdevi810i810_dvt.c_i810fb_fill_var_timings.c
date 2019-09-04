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
typedef  size_t u32 ;
struct fb_var_screeninfo {size_t xres; size_t yres; int pixclock; size_t right_margin; int hsync_len; size_t left_margin; size_t lower_margin; int vsync_len; size_t upper_margin; int /*<<< orphan*/  sync; } ;
struct TYPE_2__ {int cr00; int cr35; int pixclock; int cr04; int cr05; int msr; int cr06; int cr30; int cr10; int cr32; int cr11; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_SYNC_HOR_HIGH_ACT ; 
 int /*<<< orphan*/  FB_SYNC_ON_GREEN ; 
 int /*<<< orphan*/  FB_SYNC_VERT_HIGH_ACT ; 
 size_t i810fb_find_best_mode (size_t,size_t,size_t) ; 
 TYPE_1__* std_modes ; 

void i810fb_fill_var_timings(struct fb_var_screeninfo *var)
{
	u32 total, xres, yres;
	u32 mode, pixclock;

	xres = var->xres;
	yres = var->yres;
	
	pixclock = 1000000000 / var->pixclock;
	mode = i810fb_find_best_mode(xres, yres, pixclock);
	
	total = (std_modes[mode].cr00 | (std_modes[mode].cr35 & 1) << 8) + 3;
	total <<= 3;
	
	var->pixclock = 1000000000 / std_modes[mode].pixclock;
	var->right_margin = (std_modes[mode].cr04 << 3) - xres;
	var->hsync_len = ((std_modes[mode].cr05 & 0x1F) -
			 (std_modes[mode].cr04 & 0x1F)) << 3;
	var->left_margin = (total - (xres + var->right_margin + 
				     var->hsync_len));
	var->sync = FB_SYNC_ON_GREEN;
	if (~(std_modes[mode].msr & (1 << 6)))
		var->sync |= FB_SYNC_HOR_HIGH_ACT;
	if (~(std_modes[mode].msr & (1 << 7)))
		var->sync |= FB_SYNC_VERT_HIGH_ACT;

	total = (std_modes[mode].cr06 | (std_modes[mode].cr30 & 0xF)  << 8) + 2;
	var->lower_margin = (std_modes[mode].cr10 |
			    (std_modes[mode].cr32 & 0x0F) << 8) - yres;
	var->vsync_len = (std_modes[mode].cr11 & 0x0F) -
			 (var->lower_margin & 0x0F);
	var->upper_margin = total - (yres + var->lower_margin + var->vsync_len);
}