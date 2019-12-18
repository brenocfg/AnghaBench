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
struct TYPE_3__ {scalar_t__ chanctx_data_size; } ;
struct ieee80211_local {TYPE_1__ hw; int /*<<< orphan*/  chanctx_mtx; } ;
struct cfg80211_chan_def {int dummy; } ;
struct TYPE_4__ {int rx_chains_static; int rx_chains_dynamic; int radar_enabled; struct cfg80211_chan_def def; } ;
struct ieee80211_chanctx {int mode; TYPE_2__ conf; int /*<<< orphan*/  reserved_vifs; int /*<<< orphan*/  assigned_vifs; } ;
typedef  enum ieee80211_chanctx_mode { ____Placeholder_ieee80211_chanctx_mode } ieee80211_chanctx_mode ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_recalc_chanctx_min_def (struct ieee80211_local*,struct ieee80211_chanctx*) ; 
 struct ieee80211_chanctx* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ieee80211_chanctx *
ieee80211_alloc_chanctx(struct ieee80211_local *local,
			const struct cfg80211_chan_def *chandef,
			enum ieee80211_chanctx_mode mode)
{
	struct ieee80211_chanctx *ctx;

	lockdep_assert_held(&local->chanctx_mtx);

	ctx = kzalloc(sizeof(*ctx) + local->hw.chanctx_data_size, GFP_KERNEL);
	if (!ctx)
		return NULL;

	INIT_LIST_HEAD(&ctx->assigned_vifs);
	INIT_LIST_HEAD(&ctx->reserved_vifs);
	ctx->conf.def = *chandef;
	ctx->conf.rx_chains_static = 1;
	ctx->conf.rx_chains_dynamic = 1;
	ctx->mode = mode;
	ctx->conf.radar_enabled = false;
	ieee80211_recalc_chanctx_min_def(local, ctx);

	return ctx;
}