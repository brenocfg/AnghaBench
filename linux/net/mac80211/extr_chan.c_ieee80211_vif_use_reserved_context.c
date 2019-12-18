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
struct ieee80211_sub_if_data {int reserved_ready; struct ieee80211_chanctx* reserved_chanctx; struct ieee80211_local* local; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;
struct ieee80211_local {TYPE_1__ hw; int /*<<< orphan*/  chanctx_mtx; int /*<<< orphan*/  mtx; } ;
struct ieee80211_chanctx {scalar_t__ replace_state; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ IEEE80211_CHANCTX_REPLACES_OTHER ; 
 scalar_t__ IEEE80211_CHANCTX_REPLACE_NONE ; 
 scalar_t__ IEEE80211_CHANCTX_WILL_BE_REPLACED ; 
 scalar_t__ WARN_ON (int) ; 
 struct ieee80211_chanctx* ieee80211_vif_get_chanctx (struct ieee80211_sub_if_data*) ; 
 int ieee80211_vif_use_reserved_assign (struct ieee80211_sub_if_data*) ; 
 int ieee80211_vif_use_reserved_reassign (struct ieee80211_sub_if_data*) ; 
 int ieee80211_vif_use_reserved_switch (struct ieee80211_local*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_info (int /*<<< orphan*/ ,char*,int) ; 

int ieee80211_vif_use_reserved_context(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_chanctx *new_ctx;
	struct ieee80211_chanctx *old_ctx;
	int err;

	lockdep_assert_held(&local->mtx);
	lockdep_assert_held(&local->chanctx_mtx);

	new_ctx = sdata->reserved_chanctx;
	old_ctx = ieee80211_vif_get_chanctx(sdata);

	if (WARN_ON(!new_ctx))
		return -EINVAL;

	if (WARN_ON(new_ctx->replace_state ==
		    IEEE80211_CHANCTX_WILL_BE_REPLACED))
		return -EINVAL;

	if (WARN_ON(sdata->reserved_ready))
		return -EINVAL;

	sdata->reserved_ready = true;

	if (new_ctx->replace_state == IEEE80211_CHANCTX_REPLACE_NONE) {
		if (old_ctx)
			err = ieee80211_vif_use_reserved_reassign(sdata);
		else
			err = ieee80211_vif_use_reserved_assign(sdata);

		if (err)
			return err;
	}

	/*
	 * In-place reservation may need to be finalized now either if:
	 *  a) sdata is taking part in the swapping itself and is the last one
	 *  b) sdata has switched with a re-assign reservation to an existing
	 *     context readying in-place switching of old_ctx
	 *
	 * In case of (b) do not propagate the error up because the requested
	 * sdata already switched successfully. Just spill an extra warning.
	 * The ieee80211_vif_use_reserved_switch() already stops all necessary
	 * interfaces upon failure.
	 */
	if ((old_ctx &&
	     old_ctx->replace_state == IEEE80211_CHANCTX_WILL_BE_REPLACED) ||
	    new_ctx->replace_state == IEEE80211_CHANCTX_REPLACES_OTHER) {
		err = ieee80211_vif_use_reserved_switch(local);
		if (err && err != -EAGAIN) {
			if (new_ctx->replace_state ==
			    IEEE80211_CHANCTX_REPLACES_OTHER)
				return err;

			wiphy_info(local->hw.wiphy,
				   "depending in-place reservation failed (err=%d)\n",
				   err);
		}
	}

	return 0;
}