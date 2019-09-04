#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ieee80211_vif_chanctx_switch {int /*<<< orphan*/ * new_ctx; int /*<<< orphan*/ * old_ctx; TYPE_3__* vif; } ;
struct TYPE_9__ {scalar_t__ width; } ;
struct TYPE_6__ {scalar_t__ width; } ;
struct TYPE_7__ {TYPE_1__ chandef; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_2__ bss_conf; int /*<<< orphan*/  chanctx_conf; } ;
struct ieee80211_sub_if_data {TYPE_4__ reserved_chandef; TYPE_3__ vif; int /*<<< orphan*/  assigned_chanctx_list; struct ieee80211_chanctx* reserved_chanctx; int /*<<< orphan*/  reserved_chanctx_list; int /*<<< orphan*/  reserved_ready; struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  chanctx_mtx; int /*<<< orphan*/  mtx; } ;
struct ieee80211_chanctx {scalar_t__ replace_state; int /*<<< orphan*/  conf; int /*<<< orphan*/  assigned_vifs; } ;
struct cfg80211_chan_def {int dummy; } ;

/* Variables and functions */
 scalar_t__ BSS_CHANGED_BANDWIDTH ; 
 int /*<<< orphan*/  CHANCTX_SWMODE_REASSIGN_VIF ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ IEEE80211_CHANCTX_REPLACES_OTHER ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __ieee80211_vif_copy_chanctx_to_vlans (struct ieee80211_sub_if_data*,int) ; 
 int drv_switch_vif_chanctx (struct ieee80211_local*,struct ieee80211_vif_chanctx_switch*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,scalar_t__) ; 
 struct cfg80211_chan_def* ieee80211_chanctx_non_reserved_chandef (struct ieee80211_local*,struct ieee80211_chanctx*,TYPE_4__*) ; 
 scalar_t__ ieee80211_chanctx_refcount (struct ieee80211_local*,struct ieee80211_chanctx*) ; 
 int /*<<< orphan*/  ieee80211_change_chanctx (struct ieee80211_local*,struct ieee80211_chanctx*,struct cfg80211_chan_def const*) ; 
 int /*<<< orphan*/  ieee80211_check_fast_xmit_iface (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_free_chanctx (struct ieee80211_local*,struct ieee80211_chanctx*) ; 
 int /*<<< orphan*/  ieee80211_recalc_chanctx_min_def (struct ieee80211_local*,struct ieee80211_chanctx*) ; 
 int /*<<< orphan*/  ieee80211_recalc_radar_chanctx (struct ieee80211_local*,struct ieee80211_chanctx*) ; 
 int /*<<< orphan*/  ieee80211_recalc_smps_chanctx (struct ieee80211_local*,struct ieee80211_chanctx*) ; 
 int /*<<< orphan*/  ieee80211_vif_chanctx_reservation_complete (struct ieee80211_sub_if_data*) ; 
 struct ieee80211_chanctx* ieee80211_vif_get_chanctx (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_vif_update_chandef (struct ieee80211_sub_if_data*,TYPE_4__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ieee80211_vif_use_reserved_reassign(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_vif_chanctx_switch vif_chsw[1] = {};
	struct ieee80211_chanctx *old_ctx, *new_ctx;
	const struct cfg80211_chan_def *chandef;
	u32 changed = 0;
	int err;

	lockdep_assert_held(&local->mtx);
	lockdep_assert_held(&local->chanctx_mtx);

	new_ctx = sdata->reserved_chanctx;
	old_ctx = ieee80211_vif_get_chanctx(sdata);

	if (WARN_ON(!sdata->reserved_ready))
		return -EBUSY;

	if (WARN_ON(!new_ctx))
		return -EINVAL;

	if (WARN_ON(!old_ctx))
		return -EINVAL;

	if (WARN_ON(new_ctx->replace_state ==
		    IEEE80211_CHANCTX_REPLACES_OTHER))
		return -EINVAL;

	chandef = ieee80211_chanctx_non_reserved_chandef(local, new_ctx,
				&sdata->reserved_chandef);
	if (WARN_ON(!chandef))
		return -EINVAL;

	ieee80211_change_chanctx(local, new_ctx, chandef);

	vif_chsw[0].vif = &sdata->vif;
	vif_chsw[0].old_ctx = &old_ctx->conf;
	vif_chsw[0].new_ctx = &new_ctx->conf;

	list_del(&sdata->reserved_chanctx_list);
	sdata->reserved_chanctx = NULL;

	err = drv_switch_vif_chanctx(local, vif_chsw, 1,
				     CHANCTX_SWMODE_REASSIGN_VIF);
	if (err) {
		if (ieee80211_chanctx_refcount(local, new_ctx) == 0)
			ieee80211_free_chanctx(local, new_ctx);

		goto out;
	}

	list_move(&sdata->assigned_chanctx_list, &new_ctx->assigned_vifs);
	rcu_assign_pointer(sdata->vif.chanctx_conf, &new_ctx->conf);

	if (sdata->vif.type == NL80211_IFTYPE_AP)
		__ieee80211_vif_copy_chanctx_to_vlans(sdata, false);

	ieee80211_check_fast_xmit_iface(sdata);

	if (ieee80211_chanctx_refcount(local, old_ctx) == 0)
		ieee80211_free_chanctx(local, old_ctx);

	if (sdata->vif.bss_conf.chandef.width != sdata->reserved_chandef.width)
		changed = BSS_CHANGED_BANDWIDTH;

	ieee80211_vif_update_chandef(sdata, &sdata->reserved_chandef);

	ieee80211_recalc_smps_chanctx(local, new_ctx);
	ieee80211_recalc_radar_chanctx(local, new_ctx);
	ieee80211_recalc_chanctx_min_def(local, new_ctx);

	if (changed)
		ieee80211_bss_info_change_notify(sdata, changed);

out:
	ieee80211_vif_chanctx_reservation_complete(sdata);
	return err;
}