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
struct fb_var_screeninfo {scalar_t__ xres; scalar_t__ yres; scalar_t__ bits_per_pixel; scalar_t__ xres_virtual; scalar_t__ yres_virtual; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HVFB_HEIGHT_MIN ; 
 scalar_t__ HVFB_WIDTH_MIN ; 
 scalar_t__ screen_depth ; 
 scalar_t__ screen_height ; 
 scalar_t__ screen_width ; 

__attribute__((used)) static int hvfb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	if (var->xres < HVFB_WIDTH_MIN || var->yres < HVFB_HEIGHT_MIN ||
	    var->xres > screen_width || var->yres >  screen_height ||
	    var->bits_per_pixel != screen_depth)
		return -EINVAL;

	var->xres_virtual = var->xres;
	var->yres_virtual = var->yres;

	return 0;
}