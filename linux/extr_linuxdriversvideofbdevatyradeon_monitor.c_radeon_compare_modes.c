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
struct fb_videomode {int yres; int xres; } ;
struct fb_var_screeninfo {int yres; int xres; } ;

/* Variables and functions */

__attribute__((used)) static int radeon_compare_modes(const struct fb_var_screeninfo *var,
				const struct fb_videomode *mode)
{
	int distance = 0;

	distance = mode->yres - var->yres;
	distance += (mode->xres - var->xres)/2;
	return distance;
}