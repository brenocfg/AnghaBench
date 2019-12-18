#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ieee80211_local {int /*<<< orphan*/  chanctx_mtx; } ;
struct ieee80211_chanctx {int dummy; } ;
struct cfg80211_chan_def {int dummy; } ;

/* Variables and functions */
 struct cfg80211_chan_def* ieee80211_chanctx_non_reserved_chandef (struct ieee80211_local*,struct ieee80211_chanctx*,struct cfg80211_chan_def const*) ; 
 struct cfg80211_chan_def* ieee80211_chanctx_reserved_chandef (struct ieee80211_local*,struct ieee80211_chanctx*,struct cfg80211_chan_def const*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const struct cfg80211_chan_def *
ieee80211_chanctx_combined_chandef(struct ieee80211_local *local,
				   struct ieee80211_chanctx *ctx,
				   const struct cfg80211_chan_def *compat)
{
	lockdep_assert_held(&local->chanctx_mtx);

	compat = ieee80211_chanctx_reserved_chandef(local, ctx, compat);
	if (!compat)
		return NULL;

	compat = ieee80211_chanctx_non_reserved_chandef(local, ctx, compat);
	if (!compat)
		return NULL;

	return compat;
}