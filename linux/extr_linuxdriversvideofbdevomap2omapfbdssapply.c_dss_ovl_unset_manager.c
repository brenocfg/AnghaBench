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
struct ovl_priv_data {scalar_t__ extra_info_dirty; scalar_t__ enabled; } ;
struct omap_overlay {int /*<<< orphan*/  list; int /*<<< orphan*/ * manager; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  apply_lock ; 
 int /*<<< orphan*/  data_lock ; 
 struct ovl_priv_data* get_ovl_priv (struct omap_overlay*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ovl_manual_update (struct omap_overlay*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_pending_extra_info_updates () ; 

__attribute__((used)) static int dss_ovl_unset_manager(struct omap_overlay *ovl)
{
	struct ovl_priv_data *op = get_ovl_priv(ovl);
	unsigned long flags;
	int r;

	mutex_lock(&apply_lock);

	if (!ovl->manager) {
		DSSERR("failed to detach overlay: manager not set\n");
		r = -EINVAL;
		goto err;
	}

	spin_lock_irqsave(&data_lock, flags);

	if (op->enabled) {
		spin_unlock_irqrestore(&data_lock, flags);
		DSSERR("overlay has to be disabled to unset the manager\n");
		r = -EINVAL;
		goto err;
	}

	spin_unlock_irqrestore(&data_lock, flags);

	/* wait for pending extra_info updates to ensure the ovl is disabled */
	wait_pending_extra_info_updates();

	/*
	 * For a manual update display, there is no guarantee that the overlay
	 * is really disabled in HW, we may need an extra update from this
	 * manager before the configurations can go in. Return an error if the
	 * overlay needed an update from the manager.
	 *
	 * TODO: Instead of returning an error, try to do a dummy manager update
	 * here to disable the overlay in hardware. Use the *GATED fields in
	 * the DISPC_CONFIG registers to do a dummy update.
	 */
	spin_lock_irqsave(&data_lock, flags);

	if (ovl_manual_update(ovl) && op->extra_info_dirty) {
		spin_unlock_irqrestore(&data_lock, flags);
		DSSERR("need an update to change the manager\n");
		r = -EINVAL;
		goto err;
	}

	ovl->manager = NULL;
	list_del(&ovl->list);

	spin_unlock_irqrestore(&data_lock, flags);

	mutex_unlock(&apply_lock);

	return 0;
err:
	mutex_unlock(&apply_lock);
	return r;
}