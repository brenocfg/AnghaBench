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
struct omap_overlay_manager {int /*<<< orphan*/  id; } ;
struct mgr_priv_data {int extra_info_dirty; int shadow_extra_info_dirty; scalar_t__ updating; int /*<<< orphan*/  lcd_config; int /*<<< orphan*/  timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_set_lcd_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispc_mgr_set_timings (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dss_mgr_is_lcd (int /*<<< orphan*/ ) ; 
 struct mgr_priv_data* get_mgr_priv (struct omap_overlay_manager*) ; 

__attribute__((used)) static void dss_mgr_write_regs_extra(struct omap_overlay_manager *mgr)
{
	struct mgr_priv_data *mp = get_mgr_priv(mgr);

	DSSDBG("writing mgr %d regs extra\n", mgr->id);

	if (!mp->extra_info_dirty)
		return;

	dispc_mgr_set_timings(mgr->id, &mp->timings);

	/* lcd_config parameters */
	if (dss_mgr_is_lcd(mgr->id))
		dispc_mgr_set_lcd_config(mgr->id, &mp->lcd_config);

	mp->extra_info_dirty = false;
	if (mp->updating)
		mp->shadow_extra_info_dirty = true;
}