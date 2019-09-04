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
struct fb_var_screeninfo {int yoffset; int xoffset; int bits_per_pixel; } ;
struct fb_fix_screeninfo {int line_length; } ;

/* Variables and functions */

__attribute__((used)) static unsigned calc_rotation_offset_dma(const struct fb_var_screeninfo *var,
		const struct fb_fix_screeninfo *fix, int rotation)
{
	unsigned offset;

	offset = var->yoffset * fix->line_length +
		var->xoffset * (var->bits_per_pixel >> 3);

	return offset;
}