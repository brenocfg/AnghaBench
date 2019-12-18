#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* hw_queue; int cab_queue; } ;
struct ieee80211_sub_if_data {TYPE_2__ vif; TYPE_1__* local; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_6__ {int queues; } ;
struct TYPE_4__ {TYPE_3__ hw; } ;

/* Variables and functions */
 int EINVAL ; 
 int IEEE80211_INVAL_HW_QUEUE ; 
 int IEEE80211_NUM_ACS ; 
 int NL80211_IFTYPE_AP ; 
 int NL80211_IFTYPE_MESH_POINT ; 
 int NL80211_IFTYPE_NAN ; 
 int NL80211_IFTYPE_P2P_DEVICE ; 
 int NL80211_IFTYPE_P2P_GO ; 
 int /*<<< orphan*/  QUEUE_CONTROL ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ieee80211_hw_check (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee80211_check_queues(struct ieee80211_sub_if_data *sdata,
				  enum nl80211_iftype iftype)
{
	int n_queues = sdata->local->hw.queues;
	int i;

	if (iftype == NL80211_IFTYPE_NAN)
		return 0;

	if (iftype != NL80211_IFTYPE_P2P_DEVICE) {
		for (i = 0; i < IEEE80211_NUM_ACS; i++) {
			if (WARN_ON_ONCE(sdata->vif.hw_queue[i] ==
					 IEEE80211_INVAL_HW_QUEUE))
				return -EINVAL;
			if (WARN_ON_ONCE(sdata->vif.hw_queue[i] >=
					 n_queues))
				return -EINVAL;
		}
	}

	if ((iftype != NL80211_IFTYPE_AP &&
	     iftype != NL80211_IFTYPE_P2P_GO &&
	     iftype != NL80211_IFTYPE_MESH_POINT) ||
	    !ieee80211_hw_check(&sdata->local->hw, QUEUE_CONTROL)) {
		sdata->vif.cab_queue = IEEE80211_INVAL_HW_QUEUE;
		return 0;
	}

	if (WARN_ON_ONCE(sdata->vif.cab_queue == IEEE80211_INVAL_HW_QUEUE))
		return -EINVAL;

	if (WARN_ON_ONCE(sdata->vif.cab_queue >= n_queues))
		return -EINVAL;

	return 0;
}