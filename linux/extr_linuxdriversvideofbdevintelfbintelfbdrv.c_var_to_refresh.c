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
struct fb_var_screeninfo {int xres; int left_margin; int right_margin; int hsync_len; int yres; int upper_margin; int lower_margin; int vsync_len; int pixclock; } ;

/* Variables and functions */

__attribute__((used)) static __inline__ int var_to_refresh(const struct fb_var_screeninfo *var)
{
	int xtot = var->xres + var->left_margin + var->right_margin +
		   var->hsync_len;
	int ytot = var->yres + var->upper_margin + var->lower_margin +
		   var->vsync_len;

	return (1000000000 / var->pixclock * 1000 + 500) / xtot / ytot;
}