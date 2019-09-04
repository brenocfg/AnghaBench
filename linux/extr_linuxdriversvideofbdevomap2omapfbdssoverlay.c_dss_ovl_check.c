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
typedef  scalar_t__ u16 ;
struct omap_video_timings {scalar_t__ x_res; scalar_t__ y_res; } ;
struct omap_overlay_info {scalar_t__ width; scalar_t__ height; scalar_t__ out_width; scalar_t__ out_height; scalar_t__ pos_x; scalar_t__ pos_y; } ;
struct omap_overlay {int caps; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int EINVAL ; 
 int OMAP_DSS_OVL_CAP_SCALE ; 

int dss_ovl_check(struct omap_overlay *ovl, struct omap_overlay_info *info,
		const struct omap_video_timings *mgr_timings)
{
	u16 outw, outh;
	u16 dw, dh;

	dw = mgr_timings->x_res;
	dh = mgr_timings->y_res;

	if ((ovl->caps & OMAP_DSS_OVL_CAP_SCALE) == 0) {
		outw = info->width;
		outh = info->height;
	} else {
		if (info->out_width == 0)
			outw = info->width;
		else
			outw = info->out_width;

		if (info->out_height == 0)
			outh = info->height;
		else
			outh = info->out_height;
	}

	if (dw < info->pos_x + outw) {
		DSSERR("overlay %d horizontally not inside the display area "
				"(%d + %d >= %d)\n",
				ovl->id, info->pos_x, outw, dw);
		return -EINVAL;
	}

	if (dh < info->pos_y + outh) {
		DSSERR("overlay %d vertically not inside the display area "
				"(%d + %d >= %d)\n",
				ovl->id, info->pos_y, outh, dh);
		return -EINVAL;
	}

	return 0;
}