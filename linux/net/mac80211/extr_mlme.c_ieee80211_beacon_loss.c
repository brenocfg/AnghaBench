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
struct ieee80211_vif {int dummy; } ;
struct TYPE_5__ {int connection_loss; int /*<<< orphan*/  beacon_connection_loss_work; } ;
struct TYPE_6__ {TYPE_2__ mgd; } ;
struct ieee80211_sub_if_data {TYPE_3__ u; TYPE_1__* local; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {struct ieee80211_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_queue_work (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_api_beacon_loss (struct ieee80211_sub_if_data*) ; 
 struct ieee80211_sub_if_data* vif_to_sdata (struct ieee80211_vif*) ; 

void ieee80211_beacon_loss(struct ieee80211_vif *vif)
{
	struct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	struct ieee80211_hw *hw = &sdata->local->hw;

	trace_api_beacon_loss(sdata);

	sdata->u.mgd.connection_loss = false;
	ieee80211_queue_work(hw, &sdata->u.mgd.beacon_connection_loss_work);
}