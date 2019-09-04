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
typedef  int /*<<< orphan*/  u32 ;
struct omap_overlay_manager {int /*<<< orphan*/  id; } ;
struct mgr_priv_data {int info_dirty; int shadow_info_dirty; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,int /*<<< orphan*/ ) ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  data_lock ; 
 int /*<<< orphan*/  dispc_mgr_get_vsync_irq (int /*<<< orphan*/ ) ; 
 int dispc_runtime_get () ; 
 int /*<<< orphan*/  dispc_runtime_put () ; 
 struct mgr_priv_data* get_mgr_priv (struct omap_overlay_manager*) ; 
 scalar_t__ mgr_manual_update (struct omap_overlay_manager*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int omap_dispc_wait_for_irq_interruptible_timeout (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dss_mgr_wait_for_go(struct omap_overlay_manager *mgr)
{
	unsigned long timeout = msecs_to_jiffies(500);
	struct mgr_priv_data *mp = get_mgr_priv(mgr);
	u32 irq;
	unsigned long flags;
	int r;
	int i;

	spin_lock_irqsave(&data_lock, flags);

	if (mgr_manual_update(mgr)) {
		spin_unlock_irqrestore(&data_lock, flags);
		return 0;
	}

	if (!mp->enabled) {
		spin_unlock_irqrestore(&data_lock, flags);
		return 0;
	}

	spin_unlock_irqrestore(&data_lock, flags);

	r = dispc_runtime_get();
	if (r)
		return r;

	irq = dispc_mgr_get_vsync_irq(mgr->id);

	i = 0;
	while (1) {
		bool shadow_dirty, dirty;

		spin_lock_irqsave(&data_lock, flags);
		dirty = mp->info_dirty;
		shadow_dirty = mp->shadow_info_dirty;
		spin_unlock_irqrestore(&data_lock, flags);

		if (!dirty && !shadow_dirty) {
			r = 0;
			break;
		}

		/* 4 iterations is the worst case:
		 * 1 - initial iteration, dirty = true (between VFP and VSYNC)
		 * 2 - first VSYNC, dirty = true
		 * 3 - dirty = false, shadow_dirty = true
		 * 4 - shadow_dirty = false */
		if (i++ == 3) {
			DSSERR("mgr(%d)->wait_for_go() not finishing\n",
					mgr->id);
			r = 0;
			break;
		}

		r = omap_dispc_wait_for_irq_interruptible_timeout(irq, timeout);
		if (r == -ERESTARTSYS)
			break;

		if (r) {
			DSSERR("mgr(%d)->wait_for_go() timeout\n", mgr->id);
			break;
		}
	}

	dispc_runtime_put();

	return r;
}