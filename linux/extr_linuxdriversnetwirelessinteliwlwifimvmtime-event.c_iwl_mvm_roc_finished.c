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
struct iwl_mvm {int /*<<< orphan*/  roc_done_wk; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_roc_finished(struct iwl_mvm *mvm)
{
	/*
	 * Of course, our status bit is just as racy as mac80211, so in
	 * addition, fire off the work struct which will drop all frames
	 * from the hardware queues that made it through the race. First
	 * it will of course synchronize the TX path to make sure that
	 * any *new* TX will be rejected.
	 */
	schedule_work(&mvm->roc_done_wk);
}