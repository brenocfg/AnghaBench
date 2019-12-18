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
struct TYPE_3__ {int csa_active; } ;
struct ieee80211_sub_if_data {int csa_block_tx; TYPE_1__ vif; struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  mtx; int /*<<< orphan*/  chanctx_mtx; TYPE_2__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  abort_channel_switch; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_QUEUE_STOP_REASON_CSA ; 
 int /*<<< orphan*/  drv_abort_channel_switch (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_vif_unreserve_chanctx (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_wake_vif_queues (struct ieee80211_local*,struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ieee80211_sta_abort_chanswitch(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_local *local = sdata->local;

	if (!local->ops->abort_channel_switch)
		return;

	mutex_lock(&local->mtx);

	mutex_lock(&local->chanctx_mtx);
	ieee80211_vif_unreserve_chanctx(sdata);
	mutex_unlock(&local->chanctx_mtx);

	if (sdata->csa_block_tx)
		ieee80211_wake_vif_queues(local, sdata,
					  IEEE80211_QUEUE_STOP_REASON_CSA);

	sdata->csa_block_tx = false;
	sdata->vif.csa_active = false;

	mutex_unlock(&local->mtx);

	drv_abort_channel_switch(sdata);
}