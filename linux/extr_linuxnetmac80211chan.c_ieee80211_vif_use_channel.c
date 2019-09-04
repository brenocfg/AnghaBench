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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  iftype; } ;
struct ieee80211_sub_if_data {int radar_required; TYPE_2__ wdev; scalar_t__ dev; struct ieee80211_local* local; } ;
struct TYPE_3__ {int /*<<< orphan*/  wiphy; } ;
struct ieee80211_local {int /*<<< orphan*/  chanctx_mtx; TYPE_1__ hw; int /*<<< orphan*/  mtx; } ;
struct ieee80211_chanctx {int dummy; } ;
struct cfg80211_chan_def {int /*<<< orphan*/  width; } ;
typedef  enum ieee80211_chanctx_mode { ____Placeholder_ieee80211_chanctx_mode } ieee80211_chanctx_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct ieee80211_chanctx*) ; 
 int PTR_ERR (struct ieee80211_chanctx*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __ieee80211_vif_release_channel (struct ieee80211_sub_if_data*) ; 
 int cfg80211_chandef_dfs_required (int /*<<< orphan*/ ,struct cfg80211_chan_def const*,int /*<<< orphan*/ ) ; 
 int ieee80211_assign_vif_chanctx (struct ieee80211_sub_if_data*,struct ieee80211_chanctx*) ; 
 scalar_t__ ieee80211_chanctx_refcount (struct ieee80211_local*,struct ieee80211_chanctx*) ; 
 int ieee80211_check_combinations (struct ieee80211_sub_if_data*,struct cfg80211_chan_def const*,int,int /*<<< orphan*/ ) ; 
 struct ieee80211_chanctx* ieee80211_find_chanctx (struct ieee80211_local*,struct cfg80211_chan_def const*,int) ; 
 int /*<<< orphan*/  ieee80211_free_chanctx (struct ieee80211_local*,struct ieee80211_chanctx*) ; 
 struct ieee80211_chanctx* ieee80211_new_chanctx (struct ieee80211_local*,struct cfg80211_chan_def const*,int) ; 
 int /*<<< orphan*/  ieee80211_recalc_radar_chanctx (struct ieee80211_local*,struct ieee80211_chanctx*) ; 
 int /*<<< orphan*/  ieee80211_recalc_smps_chanctx (struct ieee80211_local*,struct ieee80211_chanctx*) ; 
 int /*<<< orphan*/  ieee80211_vif_update_chandef (struct ieee80211_sub_if_data*,struct cfg80211_chan_def const*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ netif_carrier_ok (scalar_t__) ; 

int ieee80211_vif_use_channel(struct ieee80211_sub_if_data *sdata,
			      const struct cfg80211_chan_def *chandef,
			      enum ieee80211_chanctx_mode mode)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_chanctx *ctx;
	u8 radar_detect_width = 0;
	int ret;

	lockdep_assert_held(&local->mtx);

	WARN_ON(sdata->dev && netif_carrier_ok(sdata->dev));

	mutex_lock(&local->chanctx_mtx);

	ret = cfg80211_chandef_dfs_required(local->hw.wiphy,
					    chandef,
					    sdata->wdev.iftype);
	if (ret < 0)
		goto out;
	if (ret > 0)
		radar_detect_width = BIT(chandef->width);

	sdata->radar_required = ret;

	ret = ieee80211_check_combinations(sdata, chandef, mode,
					   radar_detect_width);
	if (ret < 0)
		goto out;

	__ieee80211_vif_release_channel(sdata);

	ctx = ieee80211_find_chanctx(local, chandef, mode);
	if (!ctx)
		ctx = ieee80211_new_chanctx(local, chandef, mode);
	if (IS_ERR(ctx)) {
		ret = PTR_ERR(ctx);
		goto out;
	}

	ieee80211_vif_update_chandef(sdata, chandef);

	ret = ieee80211_assign_vif_chanctx(sdata, ctx);
	if (ret) {
		/* if assign fails refcount stays the same */
		if (ieee80211_chanctx_refcount(local, ctx) == 0)
			ieee80211_free_chanctx(local, ctx);
		goto out;
	}

	ieee80211_recalc_smps_chanctx(local, ctx);
	ieee80211_recalc_radar_chanctx(local, ctx);
 out:
	if (ret)
		sdata->radar_required = false;

	mutex_unlock(&local->chanctx_mtx);
	return ret;
}