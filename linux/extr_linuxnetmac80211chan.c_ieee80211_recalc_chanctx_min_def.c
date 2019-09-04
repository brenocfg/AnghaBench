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
struct ieee80211_local {int /*<<< orphan*/  chanctx_mtx; } ;
struct cfg80211_chan_def {scalar_t__ width; } ;
struct TYPE_2__ {struct cfg80211_chan_def min_def; struct cfg80211_chan_def def; scalar_t__ radar_enabled; } ;
struct ieee80211_chanctx {int /*<<< orphan*/  driver_present; TYPE_1__ conf; } ;
typedef  enum nl80211_chan_width { ____Placeholder_nl80211_chan_width } nl80211_chan_width ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHANCTX_CHANGE_MIN_WIDTH ; 
 scalar_t__ NL80211_CHAN_WIDTH_10 ; 
 scalar_t__ NL80211_CHAN_WIDTH_5 ; 
 scalar_t__ cfg80211_chandef_identical (struct cfg80211_chan_def*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  drv_change_chanctx (struct ieee80211_local*,struct ieee80211_chanctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_chandef_downgrade (struct cfg80211_chan_def*) ; 
 int ieee80211_get_chanctx_max_required_bw (struct ieee80211_local*,TYPE_1__*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void ieee80211_recalc_chanctx_min_def(struct ieee80211_local *local,
				      struct ieee80211_chanctx *ctx)
{
	enum nl80211_chan_width max_bw;
	struct cfg80211_chan_def min_def;

	lockdep_assert_held(&local->chanctx_mtx);

	/* don't optimize 5MHz, 10MHz, and radar_enabled confs */
	if (ctx->conf.def.width == NL80211_CHAN_WIDTH_5 ||
	    ctx->conf.def.width == NL80211_CHAN_WIDTH_10 ||
	    ctx->conf.radar_enabled) {
		ctx->conf.min_def = ctx->conf.def;
		return;
	}

	max_bw = ieee80211_get_chanctx_max_required_bw(local, &ctx->conf);

	/* downgrade chandef up to max_bw */
	min_def = ctx->conf.def;
	while (min_def.width > max_bw)
		ieee80211_chandef_downgrade(&min_def);

	if (cfg80211_chandef_identical(&ctx->conf.min_def, &min_def))
		return;

	ctx->conf.min_def = min_def;
	if (!ctx->driver_present)
		return;

	drv_change_chanctx(local, ctx, IEEE80211_CHANCTX_CHANGE_MIN_WIDTH);
}