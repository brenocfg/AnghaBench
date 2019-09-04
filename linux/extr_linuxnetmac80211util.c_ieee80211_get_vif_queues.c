#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* hw_queue; scalar_t__ cab_queue; } ;
struct ieee80211_sub_if_data {TYPE_1__ vif; } ;
struct TYPE_4__ {scalar_t__ queues; } ;
struct ieee80211_local {TYPE_2__ hw; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 scalar_t__ IEEE80211_INVAL_HW_QUEUE ; 
 int IEEE80211_NUM_ACS ; 
 int /*<<< orphan*/  QUEUE_CONTROL ; 
 scalar_t__ ieee80211_hw_check (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
ieee80211_get_vif_queues(struct ieee80211_local *local,
			 struct ieee80211_sub_if_data *sdata)
{
	unsigned int queues;

	if (sdata && ieee80211_hw_check(&local->hw, QUEUE_CONTROL)) {
		int ac;

		queues = 0;

		for (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
			queues |= BIT(sdata->vif.hw_queue[ac]);
		if (sdata->vif.cab_queue != IEEE80211_INVAL_HW_QUEUE)
			queues |= BIT(sdata->vif.cab_queue);
	} else {
		/* all queues */
		queues = BIT(local->hw.queues) - 1;
	}

	return queues;
}