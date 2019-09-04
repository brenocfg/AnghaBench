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
struct omapfb_plane_info {int /*<<< orphan*/  out_height; int /*<<< orphan*/  out_width; int /*<<< orphan*/  mem_idx; scalar_t__ mirror; scalar_t__ channel_out; int /*<<< orphan*/  enabled; int /*<<< orphan*/  pos_y; int /*<<< orphan*/  pos_x; } ;
struct omapfb_info {scalar_t__ num_overlays; struct omap_overlay** overlays; } ;
struct omap_overlay_info {int /*<<< orphan*/  out_height; int /*<<< orphan*/  out_width; int /*<<< orphan*/  pos_y; int /*<<< orphan*/  pos_x; } ;
struct omap_overlay {int /*<<< orphan*/  (* is_enabled ) (struct omap_overlay*) ;int /*<<< orphan*/  (* get_overlay_info ) (struct omap_overlay*,struct omap_overlay_info*) ;} ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 int /*<<< orphan*/  get_mem_idx (struct omapfb_info*) ; 
 int /*<<< orphan*/  memset (struct omapfb_plane_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct omap_overlay*,struct omap_overlay_info*) ; 
 int /*<<< orphan*/  stub2 (struct omap_overlay*) ; 

__attribute__((used)) static int omapfb_query_plane(struct fb_info *fbi, struct omapfb_plane_info *pi)
{
	struct omapfb_info *ofbi = FB2OFB(fbi);

	if (ofbi->num_overlays == 0) {
		memset(pi, 0, sizeof(*pi));
	} else {
		struct omap_overlay *ovl;
		struct omap_overlay_info ovli;

		ovl = ofbi->overlays[0];
		ovl->get_overlay_info(ovl, &ovli);

		pi->pos_x = ovli.pos_x;
		pi->pos_y = ovli.pos_y;
		pi->enabled = ovl->is_enabled(ovl);
		pi->channel_out = 0; /* xxx */
		pi->mirror = 0;
		pi->mem_idx = get_mem_idx(ofbi);
		pi->out_width = ovli.out_width;
		pi->out_height = ovli.out_height;
	}

	return 0;
}