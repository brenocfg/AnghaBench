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
struct ovl_priv_data {int extra_info_dirty; int shadow_extra_info_dirty; int /*<<< orphan*/  fifo_high; int /*<<< orphan*/  fifo_low; int /*<<< orphan*/  enabled; } ;
struct omap_overlay {int /*<<< orphan*/  manager; int /*<<< orphan*/  id; } ;
struct mgr_priv_data {scalar_t__ updating; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_ovl_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_ovl_set_fifo_threshold (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mgr_priv_data* get_mgr_priv (int /*<<< orphan*/ ) ; 
 struct ovl_priv_data* get_ovl_priv (struct omap_overlay*) ; 

__attribute__((used)) static void dss_ovl_write_regs_extra(struct omap_overlay *ovl)
{
	struct ovl_priv_data *op = get_ovl_priv(ovl);
	struct mgr_priv_data *mp;

	DSSDBG("writing ovl %d regs extra\n", ovl->id);

	if (!op->extra_info_dirty)
		return;

	/* note: write also when op->enabled == false, so that the ovl gets
	 * disabled */

	dispc_ovl_enable(ovl->id, op->enabled);
	dispc_ovl_set_fifo_threshold(ovl->id, op->fifo_low, op->fifo_high);

	mp = get_mgr_priv(ovl->manager);

	op->extra_info_dirty = false;
	if (mp->updating)
		op->shadow_extra_info_dirty = true;
}