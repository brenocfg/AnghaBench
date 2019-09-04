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
typedef  int u8 ;
typedef  enum omap_plane { ____Placeholder_omap_plane } omap_plane ;
typedef  enum omap_dss_rotation_type { ____Placeholder_omap_dss_rotation_type } omap_dss_rotation_type ;
typedef  enum omap_color_mode { ____Placeholder_omap_color_mode } omap_color_mode ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES (int) ; 
 int /*<<< orphan*/  FEAT_ROWREPEATENABLE ; 
 int OMAP_DSS_COLOR_NV12 ; 
 int OMAP_DSS_COLOR_UYVY ; 
 int OMAP_DSS_COLOR_YUV2 ; 
#define  OMAP_DSS_ROT_0 131 
#define  OMAP_DSS_ROT_180 130 
#define  OMAP_DSS_ROT_270 129 
#define  OMAP_DSS_ROT_90 128 
 int OMAP_DSS_ROT_TILER ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ dss_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispc_ovl_set_rotation_attrs(enum omap_plane plane, u8 rotation,
		enum omap_dss_rotation_type rotation_type,
		bool mirroring, enum omap_color_mode color_mode)
{
	bool row_repeat = false;
	int vidrot = 0;

	if (color_mode == OMAP_DSS_COLOR_YUV2 ||
			color_mode == OMAP_DSS_COLOR_UYVY) {

		if (mirroring) {
			switch (rotation) {
			case OMAP_DSS_ROT_0:
				vidrot = 2;
				break;
			case OMAP_DSS_ROT_90:
				vidrot = 1;
				break;
			case OMAP_DSS_ROT_180:
				vidrot = 0;
				break;
			case OMAP_DSS_ROT_270:
				vidrot = 3;
				break;
			}
		} else {
			switch (rotation) {
			case OMAP_DSS_ROT_0:
				vidrot = 0;
				break;
			case OMAP_DSS_ROT_90:
				vidrot = 1;
				break;
			case OMAP_DSS_ROT_180:
				vidrot = 2;
				break;
			case OMAP_DSS_ROT_270:
				vidrot = 3;
				break;
			}
		}

		if (rotation == OMAP_DSS_ROT_90 || rotation == OMAP_DSS_ROT_270)
			row_repeat = true;
		else
			row_repeat = false;
	}

	/*
	 * OMAP4/5 Errata i631:
	 * NV12 in 1D mode must use ROTATION=1. Otherwise DSS will fetch extra
	 * rows beyond the framebuffer, which may cause OCP error.
	 */
	if (color_mode == OMAP_DSS_COLOR_NV12 &&
			rotation_type != OMAP_DSS_ROT_TILER)
		vidrot = 1;

	REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), vidrot, 13, 12);
	if (dss_has_feature(FEAT_ROWREPEATENABLE))
		REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane),
			row_repeat ? 1 : 0, 18, 18);

	if (color_mode == OMAP_DSS_COLOR_NV12) {
		bool doublestride = (rotation_type == OMAP_DSS_ROT_TILER) &&
					(rotation == OMAP_DSS_ROT_0 ||
					rotation == OMAP_DSS_ROT_180);
		/* DOUBLESTRIDE */
		REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), doublestride, 22, 22);
	}

}