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
struct TYPE_2__ {unsigned long ts; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; scalar_t__ paused; scalar_t__ uapsd_nonagg_ts; } ;
struct iwl_mvm {TYPE_1__ tcm; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_MVM_UAPSD_NONAGG_PERIOD ; 
 scalar_t__ MVM_TCM_PERIOD ; 
 unsigned long iwl_mvm_calc_tcm_stats (struct iwl_mvm*,unsigned long,int) ; 
 scalar_t__ iwl_mvm_has_new_rx_api (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_request_statistics (struct iwl_mvm*,int) ; 
 int /*<<< orphan*/  iwl_mvm_tcm_results (struct iwl_mvm*) ; 
 unsigned long jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int time_after (unsigned long,scalar_t__) ; 

void iwl_mvm_recalc_tcm(struct iwl_mvm *mvm)
{
	unsigned long ts = jiffies;
	bool handle_uapsd =
		time_after(ts, mvm->tcm.uapsd_nonagg_ts +
			       msecs_to_jiffies(IWL_MVM_UAPSD_NONAGG_PERIOD));

	spin_lock(&mvm->tcm.lock);
	if (mvm->tcm.paused || !time_after(ts, mvm->tcm.ts + MVM_TCM_PERIOD)) {
		spin_unlock(&mvm->tcm.lock);
		return;
	}
	spin_unlock(&mvm->tcm.lock);

	if (handle_uapsd && iwl_mvm_has_new_rx_api(mvm)) {
		mutex_lock(&mvm->mutex);
		if (iwl_mvm_request_statistics(mvm, true))
			handle_uapsd = false;
		mutex_unlock(&mvm->mutex);
	}

	spin_lock(&mvm->tcm.lock);
	/* re-check if somebody else won the recheck race */
	if (!mvm->tcm.paused && time_after(ts, mvm->tcm.ts + MVM_TCM_PERIOD)) {
		/* calculate statistics */
		unsigned long work_delay = iwl_mvm_calc_tcm_stats(mvm, ts,
								  handle_uapsd);

		/* the memset needs to be visible before the timestamp */
		smp_mb();
		mvm->tcm.ts = ts;
		if (work_delay)
			schedule_delayed_work(&mvm->tcm.work, work_delay);
	}
	spin_unlock(&mvm->tcm.lock);

	iwl_mvm_tcm_results(mvm);
}