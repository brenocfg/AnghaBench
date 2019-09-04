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
typedef  int u16 ;
struct omap_video_timings {int interlace; } ;
struct omap_overlay_info {int height; int width; int pos_x; scalar_t__ out_width; scalar_t__ out_height; int /*<<< orphan*/  rotation_type; int /*<<< orphan*/  color_mode; } ;
typedef  enum omap_plane { ____Placeholder_omap_plane } omap_plane ;
typedef  enum omap_overlay_caps { ____Placeholder_omap_overlay_caps } omap_overlay_caps ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*,int,int) ; 
 int EINVAL ; 
 unsigned long dispc_mgr_lclk_rate (int) ; 
 unsigned long dispc_mgr_pclk_rate (int) ; 
 int dispc_ovl_calc_scaling (unsigned long,unsigned long,int,struct omap_video_timings const*,int,int,int,int,int /*<<< orphan*/ ,int*,int*,int*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dss_feat_color_mode_supported (int,int /*<<< orphan*/ ) ; 
 int dss_feat_get_overlay_caps (int) ; 

int dispc_ovl_check(enum omap_plane plane, enum omap_channel channel,
		const struct omap_overlay_info *oi,
		const struct omap_video_timings *timings,
		int *x_predecim, int *y_predecim)
{
	enum omap_overlay_caps caps = dss_feat_get_overlay_caps(plane);
	bool five_taps = true;
	bool fieldmode = false;
	u16 in_height = oi->height;
	u16 in_width = oi->width;
	bool ilace = timings->interlace;
	u16 out_width, out_height;
	int pos_x = oi->pos_x;
	unsigned long pclk = dispc_mgr_pclk_rate(channel);
	unsigned long lclk = dispc_mgr_lclk_rate(channel);

	out_width = oi->out_width == 0 ? oi->width : oi->out_width;
	out_height = oi->out_height == 0 ? oi->height : oi->out_height;

	if (ilace && oi->height == out_height)
		fieldmode = true;

	if (ilace) {
		if (fieldmode)
			in_height /= 2;
		out_height /= 2;

		DSSDBG("adjusting for ilace: height %d, out_height %d\n",
				in_height, out_height);
	}

	if (!dss_feat_color_mode_supported(plane, oi->color_mode))
		return -EINVAL;

	return dispc_ovl_calc_scaling(pclk, lclk, caps, timings, in_width,
			in_height, out_width, out_height, oi->color_mode,
			&five_taps, x_predecim, y_predecim, pos_x,
			oi->rotation_type, false);
}