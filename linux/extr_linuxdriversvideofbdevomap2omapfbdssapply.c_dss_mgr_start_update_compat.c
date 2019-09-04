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
struct omap_overlay_manager {int /*<<< orphan*/  id; } ;
struct mgr_priv_data {int updating; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  data_lock ; 
 int /*<<< orphan*/  dispc_mgr_enable_sync (int /*<<< orphan*/ ) ; 
 int dss_check_settings (struct omap_overlay_manager*) ; 
 TYPE_1__ dss_data ; 
 int /*<<< orphan*/  dss_mgr_write_regs (struct omap_overlay_manager*) ; 
 int /*<<< orphan*/  dss_mgr_write_regs_extra (struct omap_overlay_manager*) ; 
 int /*<<< orphan*/  dss_register_vsync_isr () ; 
 struct mgr_priv_data* get_mgr_priv (struct omap_overlay_manager*) ; 
 scalar_t__ need_isr () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void dss_mgr_start_update_compat(struct omap_overlay_manager *mgr)
{
	struct mgr_priv_data *mp = get_mgr_priv(mgr);
	unsigned long flags;
	int r;

	spin_lock_irqsave(&data_lock, flags);

	WARN_ON(mp->updating);

	r = dss_check_settings(mgr);
	if (r) {
		DSSERR("cannot start manual update: illegal configuration\n");
		spin_unlock_irqrestore(&data_lock, flags);
		return;
	}

	dss_mgr_write_regs(mgr);
	dss_mgr_write_regs_extra(mgr);

	mp->updating = true;

	if (!dss_data.irq_enabled && need_isr())
		dss_register_vsync_isr();

	dispc_mgr_enable_sync(mgr->id);

	spin_unlock_irqrestore(&data_lock, flags);
}