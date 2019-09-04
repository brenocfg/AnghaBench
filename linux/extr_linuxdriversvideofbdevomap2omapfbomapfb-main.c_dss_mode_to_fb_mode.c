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
struct omapfb_colormode {int dssmode; } ;
struct fb_var_screeninfo {int dummy; } ;
typedef  enum omap_color_mode { ____Placeholder_omap_color_mode } omap_color_mode ;

/* Variables and functions */
 int ARRAY_SIZE (struct omapfb_colormode*) ; 
 int ENOENT ; 
 int /*<<< orphan*/  assign_colormode_to_var (struct fb_var_screeninfo*,struct omapfb_colormode*) ; 
 struct omapfb_colormode* omapfb_colormodes ; 

int dss_mode_to_fb_mode(enum omap_color_mode dssmode,
			struct fb_var_screeninfo *var)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(omapfb_colormodes); ++i) {
		struct omapfb_colormode *mode = &omapfb_colormodes[i];
		if (dssmode == mode->dssmode) {
			assign_colormode_to_var(var, mode);
			return 0;
		}
	}
	return -ENOENT;
}