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
struct omap_video_timings {int dummy; } ;
struct omap_overlay_info {int /*<<< orphan*/  rotation_type; int /*<<< orphan*/  global_alpha; int /*<<< orphan*/  pre_mult_alpha; int /*<<< orphan*/  zorder; int /*<<< orphan*/  mirror; int /*<<< orphan*/  rotation; int /*<<< orphan*/  color_mode; int /*<<< orphan*/  out_height; int /*<<< orphan*/  out_width; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pos_y; int /*<<< orphan*/  pos_x; int /*<<< orphan*/  screen_width; int /*<<< orphan*/  p_uv_addr; int /*<<< orphan*/  paddr; } ;
typedef  enum omap_plane { ____Placeholder_omap_plane } omap_plane ;
typedef  enum omap_overlay_caps { ____Placeholder_omap_overlay_caps } omap_overlay_caps ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int dispc_ovl_get_channel_out (int) ; 
 int dispc_ovl_setup_common (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct omap_video_timings const*,int) ; 
 int dss_feat_get_overlay_caps (int) ; 

int dispc_ovl_setup(enum omap_plane plane, const struct omap_overlay_info *oi,
		bool replication, const struct omap_video_timings *mgr_timings,
		bool mem_to_mem)
{
	int r;
	enum omap_overlay_caps caps = dss_feat_get_overlay_caps(plane);
	enum omap_channel channel;

	channel = dispc_ovl_get_channel_out(plane);

	DSSDBG("dispc_ovl_setup %d, pa %pad, pa_uv %pad, sw %d, %d,%d, %dx%d ->"
		" %dx%d, cmode %x, rot %d, mir %d, chan %d repl %d\n",
		plane, &oi->paddr, &oi->p_uv_addr, oi->screen_width, oi->pos_x,
		oi->pos_y, oi->width, oi->height, oi->out_width, oi->out_height,
		oi->color_mode, oi->rotation, oi->mirror, channel, replication);

	r = dispc_ovl_setup_common(plane, caps, oi->paddr, oi->p_uv_addr,
		oi->screen_width, oi->pos_x, oi->pos_y, oi->width, oi->height,
		oi->out_width, oi->out_height, oi->color_mode, oi->rotation,
		oi->mirror, oi->zorder, oi->pre_mult_alpha, oi->global_alpha,
		oi->rotation_type, replication, mgr_timings, mem_to_mem);

	return r;
}