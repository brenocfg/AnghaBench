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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  chandef; } ;
struct TYPE_4__ {int csa_active; TYPE_1__ bss_conf; } ;
struct ieee80211_sub_if_data {int csa_block_tx; int /*<<< orphan*/  csa_chandef; int /*<<< orphan*/  dev; TYPE_2__ vif; scalar_t__ reserved_ready; scalar_t__ reserved_chanctx; struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  chanctx_mtx; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IEEE80211_QUEUE_STOP_REASON_CSA ; 
 int /*<<< orphan*/  cfg80211_ch_switch_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfg80211_chandef_identical (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drv_post_channel_switch (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int ieee80211_set_after_csa_beacon (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *) ; 
 int ieee80211_vif_use_reserved_context (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_wake_vif_queues (struct ieee80211_local*,struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdata_assert_lock (struct ieee80211_sub_if_data*) ; 

__attribute__((used)) static int __ieee80211_csa_finalize(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_local *local = sdata->local;
	u32 changed = 0;
	int err;

	sdata_assert_lock(sdata);
	lockdep_assert_held(&local->mtx);
	lockdep_assert_held(&local->chanctx_mtx);

	/*
	 * using reservation isn't immediate as it may be deferred until later
	 * with multi-vif. once reservation is complete it will re-schedule the
	 * work with no reserved_chanctx so verify chandef to check if it
	 * completed successfully
	 */

	if (sdata->reserved_chanctx) {
		/*
		 * with multi-vif csa driver may call ieee80211_csa_finish()
		 * many times while waiting for other interfaces to use their
		 * reservations
		 */
		if (sdata->reserved_ready)
			return 0;

		return ieee80211_vif_use_reserved_context(sdata);
	}

	if (!cfg80211_chandef_identical(&sdata->vif.bss_conf.chandef,
					&sdata->csa_chandef))
		return -EINVAL;

	sdata->vif.csa_active = false;

	err = ieee80211_set_after_csa_beacon(sdata, &changed);
	if (err)
		return err;

	ieee80211_bss_info_change_notify(sdata, changed);

	if (sdata->csa_block_tx) {
		ieee80211_wake_vif_queues(local, sdata,
					  IEEE80211_QUEUE_STOP_REASON_CSA);
		sdata->csa_block_tx = false;
	}

	err = drv_post_channel_switch(sdata);
	if (err)
		return err;

	cfg80211_ch_switch_notify(sdata->dev, &sdata->csa_chandef);

	return 0;
}