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
typedef  enum omap_plane { ____Placeholder_omap_plane } omap_plane ;
typedef  enum omap_color_mode { ____Placeholder_omap_color_mode } omap_color_mode ;
struct TYPE_2__ {int* supported_color_modes; } ;

/* Variables and functions */
 TYPE_1__* omap_current_dss_features ; 

bool dss_feat_color_mode_supported(enum omap_plane plane,
		enum omap_color_mode color_mode)
{
	return omap_current_dss_features->supported_color_modes[plane] &
			color_mode;
}