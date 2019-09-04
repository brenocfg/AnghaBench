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
struct omapfb_info {scalar_t__ rotation_type; TYPE_1__* region; } ;
struct fb_var_screeninfo {int bits_per_pixel; int xres_virtual; unsigned long yres_virtual; } ;
struct TYPE_2__ {unsigned long size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int EINVAL ; 
 scalar_t__ OMAP_DSS_ROT_VRFB ; 
 scalar_t__ check_vrfb_fb_size (unsigned long,struct fb_var_screeninfo*) ; 
 unsigned long omap_vrfb_max_height (unsigned long,int,int) ; 
 int /*<<< orphan*/  shrink_height (unsigned long,struct fb_var_screeninfo*) ; 
 int /*<<< orphan*/  shrink_width (unsigned long,struct fb_var_screeninfo*) ; 

__attribute__((used)) static int check_fb_size(const struct omapfb_info *ofbi,
		struct fb_var_screeninfo *var)
{
	unsigned long max_frame_size = ofbi->region->size;
	int bytespp = var->bits_per_pixel >> 3;
	unsigned long line_size = var->xres_virtual * bytespp;

	if (ofbi->rotation_type == OMAP_DSS_ROT_VRFB) {
		/* One needs to check for both VRFB and OMAPFB limitations. */
		if (check_vrfb_fb_size(max_frame_size, var))
			shrink_height(omap_vrfb_max_height(
				max_frame_size, var->xres_virtual, bytespp) *
				line_size, var);

		if (check_vrfb_fb_size(max_frame_size, var)) {
			DBG("cannot fit FB to memory\n");
			return -EINVAL;
		}

		return 0;
	}

	DBG("max frame size %lu, line size %lu\n", max_frame_size, line_size);

	if (line_size * var->yres_virtual > max_frame_size)
		shrink_height(max_frame_size, var);

	if (line_size * var->yres_virtual > max_frame_size) {
		shrink_width(max_frame_size, var);
		line_size = var->xres_virtual * bytespp;
	}

	if (line_size * var->yres_virtual > max_frame_size) {
		DBG("cannot fit FB to memory\n");
		return -EINVAL;
	}

	return 0;
}