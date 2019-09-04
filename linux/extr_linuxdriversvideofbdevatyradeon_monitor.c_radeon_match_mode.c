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
struct radeonfb_info {int mon1_dbsize; scalar_t__ mon1_type; int /*<<< orphan*/  info; struct fb_videomode* mon1_modedb; } ;
struct fb_videomode {scalar_t__ yres; scalar_t__ xres; } ;
struct fb_var_screeninfo {int activate; scalar_t__ yres; scalar_t__ xres; } ;

/* Variables and functions */
 int EINVAL ; 
 int FB_ACTIVATE_MASK ; 
 int FB_ACTIVATE_NOW ; 
 int FB_ACTIVATE_TEST ; 
 int INT_MAX ; 
 scalar_t__ MT_DFP ; 
 scalar_t__ MT_LCD ; 
 scalar_t__ fb_validate_mode (struct fb_var_screeninfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct fb_var_screeninfo*,struct fb_var_screeninfo const*,int) ; 
 int radeon_compare_modes (struct fb_var_screeninfo const*,struct fb_videomode const*) ; 
 int /*<<< orphan*/  radeon_videomode_to_var (struct fb_var_screeninfo*,struct fb_videomode const*) ; 
 struct fb_videomode* vesa_modes ; 

int  radeon_match_mode(struct radeonfb_info *rinfo,
		       struct fb_var_screeninfo *dest,
		       const struct fb_var_screeninfo *src)
{
	const struct fb_videomode	*db = vesa_modes;
	int				i, dbsize = 34;
	int				has_rmx, native_db = 0;
	int				distance = INT_MAX;
	const struct fb_videomode	*candidate = NULL;

	/* Start with a copy of the requested mode */
	memcpy(dest, src, sizeof(struct fb_var_screeninfo));

	/* Check if we have a modedb built from EDID */
	if (rinfo->mon1_modedb) {
		db = rinfo->mon1_modedb;
		dbsize = rinfo->mon1_dbsize;
		native_db = 1;
	}

	/* Check if we have a scaler allowing any fancy mode */
	has_rmx = rinfo->mon1_type == MT_LCD || rinfo->mon1_type == MT_DFP;

	/* If we have a scaler and are passed FB_ACTIVATE_TEST or
	 * FB_ACTIVATE_NOW, just do basic checking and return if the
	 * mode match
	 */
	if ((src->activate & FB_ACTIVATE_MASK) == FB_ACTIVATE_TEST ||
	    (src->activate & FB_ACTIVATE_MASK) == FB_ACTIVATE_NOW) {
		/* We don't have an RMX, validate timings. If we don't have
	 	 * monspecs, we should be paranoid and not let use go above
		 * 640x480-60, but I assume userland knows what it's doing here
		 * (though I may be proven wrong...)
		 */
		if (has_rmx == 0 && rinfo->mon1_modedb)
			if (fb_validate_mode((struct fb_var_screeninfo *)src, rinfo->info))
				return -EINVAL;
		return 0;
	}

	/* Now look for a mode in the database */
	while (db) {
		for (i = 0; i < dbsize; i++) {
			int d;

			if (db[i].yres < src->yres)
				continue;	
			if (db[i].xres < src->xres)
				continue;
			d = radeon_compare_modes(src, &db[i]);
			/* If the new mode is at least as good as the previous one,
			 * then it's our new candidate
			 */
			if (d < distance) {
				candidate = &db[i];
				distance = d;
			}
		}
		db = NULL;
		/* If we have a scaler, we allow any mode from the database */
		if (native_db && has_rmx) {
			db = vesa_modes;
			dbsize = 34;
			native_db = 0;
		}
	}

	/* If we have found a match, return it */
	if (candidate != NULL) {
		radeon_videomode_to_var(dest, candidate);
		return 0;
	}

	/* If we haven't and don't have a scaler, fail */
	if (!has_rmx)
		return -EINVAL;

	return 0;
}