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
struct omap_overlay_info {scalar_t__ out_width; scalar_t__ width; scalar_t__ out_height; scalar_t__ height; int color_mode; scalar_t__ zorder; scalar_t__ rotation_type; } ;
struct omap_overlay {int caps; scalar_t__ id; int supported_modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,scalar_t__,...) ; 
 int EINVAL ; 
 int OMAP_DSS_OVL_CAP_SCALE ; 
 scalar_t__ dss_feat_rotation_type_supported (scalar_t__) ; 
 scalar_t__ omap_dss_get_num_overlays () ; 

int dss_ovl_simple_check(struct omap_overlay *ovl,
		const struct omap_overlay_info *info)
{
	if ((ovl->caps & OMAP_DSS_OVL_CAP_SCALE) == 0) {
		if (info->out_width != 0 && info->width != info->out_width) {
			DSSERR("check_overlay: overlay %d doesn't support "
					"scaling\n", ovl->id);
			return -EINVAL;
		}

		if (info->out_height != 0 && info->height != info->out_height) {
			DSSERR("check_overlay: overlay %d doesn't support "
					"scaling\n", ovl->id);
			return -EINVAL;
		}
	}

	if ((ovl->supported_modes & info->color_mode) == 0) {
		DSSERR("check_overlay: overlay %d doesn't support mode %d\n",
				ovl->id, info->color_mode);
		return -EINVAL;
	}

	if (info->zorder >= omap_dss_get_num_overlays()) {
		DSSERR("check_overlay: zorder %d too high\n", info->zorder);
		return -EINVAL;
	}

	if (dss_feat_rotation_type_supported(info->rotation_type) == 0) {
		DSSERR("check_overlay: rotation type %d not supported\n",
				info->rotation_type);
		return -EINVAL;
	}

	return 0;
}