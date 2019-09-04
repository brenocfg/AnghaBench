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
typedef  enum omap_plane { ____Placeholder_omap_plane } omap_plane ;
typedef  enum omap_dss_rotation_type { ____Placeholder_omap_dss_rotation_type } omap_dss_rotation_type ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES (int) ; 
 int /*<<< orphan*/  FEAT_BURST_2D ; 
 int OMAP_DSS_ROT_TILER ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ dss_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispc_ovl_configure_burst_type(enum omap_plane plane,
		enum omap_dss_rotation_type rotation_type)
{
	if (dss_has_feature(FEAT_BURST_2D) == 0)
		return;

	if (rotation_type == OMAP_DSS_ROT_TILER)
		REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), 1, 29, 29);
	else
		REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), 0, 29, 29);
}