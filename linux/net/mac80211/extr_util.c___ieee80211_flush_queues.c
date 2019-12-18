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
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  flush; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_QUEUE_STOP_REASON_FLUSH ; 
 int /*<<< orphan*/  QUEUE_CONTROL ; 
 int /*<<< orphan*/  drv_flush (struct ieee80211_local*,struct ieee80211_sub_if_data*,unsigned int,int) ; 
 unsigned int ieee80211_get_vif_queues (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_hw_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_stop_queues_by_reason (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_wake_queues_by_reason (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int) ; 

void __ieee80211_flush_queues(struct ieee80211_local *local,
			      struct ieee80211_sub_if_data *sdata,
			      unsigned int queues, bool drop)
{
	if (!local->ops->flush)
		return;

	/*
	 * If no queue was set, or if the HW doesn't support
	 * IEEE80211_HW_QUEUE_CONTROL - flush all queues
	 */
	if (!queues || !ieee80211_hw_check(&local->hw, QUEUE_CONTROL))
		queues = ieee80211_get_vif_queues(local, sdata);

	ieee80211_stop_queues_by_reason(&local->hw, queues,
					IEEE80211_QUEUE_STOP_REASON_FLUSH,
					false);

	drv_flush(local, sdata, queues, drop);

	ieee80211_wake_queues_by_reason(&local->hw, queues,
					IEEE80211_QUEUE_STOP_REASON_FLUSH,
					false);
}