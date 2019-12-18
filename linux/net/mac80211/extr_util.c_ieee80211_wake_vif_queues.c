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
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; } ;
typedef  enum queue_stop_reason { ____Placeholder_queue_stop_reason } queue_stop_reason ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_get_vif_queues (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_wake_queues_by_reason (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

void ieee80211_wake_vif_queues(struct ieee80211_local *local,
			       struct ieee80211_sub_if_data *sdata,
			       enum queue_stop_reason reason)
{
	ieee80211_wake_queues_by_reason(&local->hw,
					ieee80211_get_vif_queues(local, sdata),
					reason, true);
}