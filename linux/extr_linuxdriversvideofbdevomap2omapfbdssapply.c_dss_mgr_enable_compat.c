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
struct mgr_priv_data {int enabled; int updating; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apply_lock ; 
 int /*<<< orphan*/  data_lock ; 
 int /*<<< orphan*/  dispc_mgr_enable_sync (int /*<<< orphan*/ ) ; 
 int dss_check_settings (struct omap_overlay_manager*) ; 
 TYPE_1__ dss_data ; 
 int /*<<< orphan*/  dss_register_vsync_isr () ; 
 int /*<<< orphan*/  dss_set_go_bits () ; 
 int /*<<< orphan*/  dss_setup_fifos () ; 
 int /*<<< orphan*/  dss_write_regs () ; 
 struct mgr_priv_data* get_mgr_priv (struct omap_overlay_manager*) ; 
 int /*<<< orphan*/  mgr_manual_update (struct omap_overlay_manager*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ need_isr () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dss_mgr_enable_compat(struct omap_overlay_manager *mgr)
{
	struct mgr_priv_data *mp = get_mgr_priv(mgr);
	unsigned long flags;
	int r;

	mutex_lock(&apply_lock);

	if (mp->enabled)
		goto out;

	spin_lock_irqsave(&data_lock, flags);

	mp->enabled = true;

	r = dss_check_settings(mgr);
	if (r) {
		DSSERR("failed to enable manager %d: check_settings failed\n",
				mgr->id);
		goto err;
	}

	dss_setup_fifos();

	dss_write_regs();
	dss_set_go_bits();

	if (!mgr_manual_update(mgr))
		mp->updating = true;

	if (!dss_data.irq_enabled && need_isr())
		dss_register_vsync_isr();

	spin_unlock_irqrestore(&data_lock, flags);

	if (!mgr_manual_update(mgr))
		dispc_mgr_enable_sync(mgr->id);

out:
	mutex_unlock(&apply_lock);

	return 0;

err:
	mp->enabled = false;
	spin_unlock_irqrestore(&data_lock, flags);
	mutex_unlock(&apply_lock);
	return r;
}