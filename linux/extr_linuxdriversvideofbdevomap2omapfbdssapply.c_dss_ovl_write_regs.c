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
struct omap_overlay_info {int /*<<< orphan*/  color_mode; } ;
struct ovl_priv_data {int enabled; int info_dirty; int shadow_info_dirty; struct omap_overlay_info info; } ;
struct omap_overlay {int /*<<< orphan*/  id; int /*<<< orphan*/  manager; } ;
struct mgr_priv_data {scalar_t__ updating; int /*<<< orphan*/  timings; int /*<<< orphan*/  lcd_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSSERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_ovl_enable (int /*<<< orphan*/ ,int) ; 
 int dispc_ovl_setup (int /*<<< orphan*/ ,struct omap_overlay_info*,int,int /*<<< orphan*/ *,int) ; 
 int dss_ovl_use_replication (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mgr_priv_data* get_mgr_priv (int /*<<< orphan*/ ) ; 
 struct ovl_priv_data* get_ovl_priv (struct omap_overlay*) ; 

__attribute__((used)) static void dss_ovl_write_regs(struct omap_overlay *ovl)
{
	struct ovl_priv_data *op = get_ovl_priv(ovl);
	struct omap_overlay_info *oi;
	bool replication;
	struct mgr_priv_data *mp;
	int r;

	DSSDBG("writing ovl %d regs\n", ovl->id);

	if (!op->enabled || !op->info_dirty)
		return;

	oi = &op->info;

	mp = get_mgr_priv(ovl->manager);

	replication = dss_ovl_use_replication(mp->lcd_config, oi->color_mode);

	r = dispc_ovl_setup(ovl->id, oi, replication, &mp->timings, false);
	if (r) {
		/*
		 * We can't do much here, as this function can be called from
		 * vsync interrupt.
		 */
		DSSERR("dispc_ovl_setup failed for ovl %d\n", ovl->id);

		/* This will leave fifo configurations in a nonoptimal state */
		op->enabled = false;
		dispc_ovl_enable(ovl->id, false);
		return;
	}

	op->info_dirty = false;
	if (mp->updating)
		op->shadow_info_dirty = true;
}