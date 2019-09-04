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
typedef  int /*<<< orphan*/  supported_modes ;
struct omapfb_ovl_colormode {int overlay_idx; int mode_idx; int /*<<< orphan*/  transp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; int /*<<< orphan*/  nonstd; int /*<<< orphan*/  bits_per_pixel; } ;
struct omapfb2_device {int num_overlays; struct omap_overlay** overlays; } ;
struct omap_overlay {int supported_modes; } ;
struct fb_var_screeninfo {int /*<<< orphan*/  transp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; int /*<<< orphan*/  nonstd; int /*<<< orphan*/  bits_per_pixel; } ;
typedef  enum omap_color_mode { ____Placeholder_omap_color_mode } omap_color_mode ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 scalar_t__ dss_mode_to_fb_mode (int,struct fb_var_screeninfo*) ; 

__attribute__((used)) static int omapfb_get_ovl_colormode(struct omapfb2_device *fbdev,
			     struct omapfb_ovl_colormode *mode)
{
	int ovl_idx = mode->overlay_idx;
	int mode_idx = mode->mode_idx;
	struct omap_overlay *ovl;
	enum omap_color_mode supported_modes;
	struct fb_var_screeninfo var;
	int i;

	if (ovl_idx >= fbdev->num_overlays)
		return -ENODEV;
	ovl = fbdev->overlays[ovl_idx];
	supported_modes = ovl->supported_modes;

	mode_idx = mode->mode_idx;

	for (i = 0; i < sizeof(supported_modes) * 8; i++) {
		if (!(supported_modes & (1 << i)))
			continue;
		/*
		 * It's possible that the FB doesn't support a mode
		 * that is supported by the overlay, so call the
		 * following here.
		 */
		if (dss_mode_to_fb_mode(1 << i, &var) < 0)
			continue;

		mode_idx--;
		if (mode_idx < 0)
			break;
	}

	if (i == sizeof(supported_modes) * 8)
		return -ENOENT;

	mode->bits_per_pixel = var.bits_per_pixel;
	mode->nonstd = var.nonstd;
	mode->red = var.red;
	mode->green = var.green;
	mode->blue = var.blue;
	mode->transp = var.transp;

	return 0;
}