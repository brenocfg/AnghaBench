#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  monitor_work; } ;
struct TYPE_8__ {TYPE_3__ mgd; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct ieee80211_sub_if_data {TYPE_4__ u; TYPE_2__* local; TYPE_1__ vif; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTION_MONITOR ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  __ieee80211_stop_poll (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_hw_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ieee80211_restart_sta_timer(struct ieee80211_sub_if_data *sdata)
{
	if (sdata->vif.type == NL80211_IFTYPE_STATION) {
		__ieee80211_stop_poll(sdata);

		/* let's probe the connection once */
		if (!ieee80211_hw_check(&sdata->local->hw, CONNECTION_MONITOR))
			ieee80211_queue_work(&sdata->local->hw,
					     &sdata->u.mgd.monitor_work);
	}
}