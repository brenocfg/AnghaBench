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
struct omapfb_colormode {scalar_t__ nonstd; int dssmode; } ;
struct fb_var_screeninfo {scalar_t__ nonstd; int bits_per_pixel; } ;
typedef  enum omap_color_mode { ____Placeholder_omap_color_mode } omap_color_mode ;

/* Variables and functions */
 int ARRAY_SIZE (struct omapfb_colormode*) ; 
 int EINVAL ; 
 int OMAP_DSS_COLOR_CLUT1 ; 
 int OMAP_DSS_COLOR_CLUT2 ; 
 int OMAP_DSS_COLOR_CLUT4 ; 
 int OMAP_DSS_COLOR_CLUT8 ; 
 int OMAP_DSS_COLOR_RGB12U ; 
 int OMAP_DSS_COLOR_RGB16 ; 
 int OMAP_DSS_COLOR_RGB24P ; 
 int OMAP_DSS_COLOR_RGB24U ; 
 int /*<<< orphan*/  assign_colormode_to_var (struct fb_var_screeninfo*,struct omapfb_colormode*) ; 
 scalar_t__ cmp_var_to_colormode (struct fb_var_screeninfo*,struct omapfb_colormode*) ; 
 struct omapfb_colormode* omapfb_colormodes ; 

__attribute__((used)) static int fb_mode_to_dss_mode(struct fb_var_screeninfo *var,
		enum omap_color_mode *mode)
{
	enum omap_color_mode dssmode;
	int i;

	/* first match with nonstd field */
	if (var->nonstd) {
		for (i = 0; i < ARRAY_SIZE(omapfb_colormodes); ++i) {
			struct omapfb_colormode *m = &omapfb_colormodes[i];
			if (var->nonstd == m->nonstd) {
				assign_colormode_to_var(var, m);
				*mode = m->dssmode;
				return 0;
			}
		}

		return -EINVAL;
	}

	/* then try exact match of bpp and colors */
	for (i = 0; i < ARRAY_SIZE(omapfb_colormodes); ++i) {
		struct omapfb_colormode *m = &omapfb_colormodes[i];
		if (cmp_var_to_colormode(var, m)) {
			assign_colormode_to_var(var, m);
			*mode = m->dssmode;
			return 0;
		}
	}

	/* match with bpp if user has not filled color fields
	 * properly */
	switch (var->bits_per_pixel) {
	case 1:
		dssmode = OMAP_DSS_COLOR_CLUT1;
		break;
	case 2:
		dssmode = OMAP_DSS_COLOR_CLUT2;
		break;
	case 4:
		dssmode = OMAP_DSS_COLOR_CLUT4;
		break;
	case 8:
		dssmode = OMAP_DSS_COLOR_CLUT8;
		break;
	case 12:
		dssmode = OMAP_DSS_COLOR_RGB12U;
		break;
	case 16:
		dssmode = OMAP_DSS_COLOR_RGB16;
		break;
	case 24:
		dssmode = OMAP_DSS_COLOR_RGB24P;
		break;
	case 32:
		dssmode = OMAP_DSS_COLOR_RGB24U;
		break;
	default:
		return -EINVAL;
	}

	for (i = 0; i < ARRAY_SIZE(omapfb_colormodes); ++i) {
		struct omapfb_colormode *m = &omapfb_colormodes[i];
		if (dssmode == m->dssmode) {
			assign_colormode_to_var(var, m);
			*mode = m->dssmode;
			return 0;
		}
	}

	return -EINVAL;
}