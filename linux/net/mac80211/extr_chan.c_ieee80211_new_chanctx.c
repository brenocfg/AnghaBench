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
struct ieee80211_local {int /*<<< orphan*/  chanctx_list; int /*<<< orphan*/  chanctx_mtx; int /*<<< orphan*/  mtx; } ;
struct ieee80211_chanctx {int /*<<< orphan*/  list; } ;
struct cfg80211_chan_def {int dummy; } ;
typedef  enum ieee80211_chanctx_mode { ____Placeholder_ieee80211_chanctx_mode } ieee80211_chanctx_mode ;

/* Variables and functions */
 int ENOMEM ; 
 struct ieee80211_chanctx* ERR_PTR (int) ; 
 int ieee80211_add_chanctx (struct ieee80211_local*,struct ieee80211_chanctx*) ; 
 struct ieee80211_chanctx* ieee80211_alloc_chanctx (struct ieee80211_local*,struct cfg80211_chan_def const*,int) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_chanctx*) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ieee80211_chanctx *
ieee80211_new_chanctx(struct ieee80211_local *local,
		      const struct cfg80211_chan_def *chandef,
		      enum ieee80211_chanctx_mode mode)
{
	struct ieee80211_chanctx *ctx;
	int err;

	lockdep_assert_held(&local->mtx);
	lockdep_assert_held(&local->chanctx_mtx);

	ctx = ieee80211_alloc_chanctx(local, chandef, mode);
	if (!ctx)
		return ERR_PTR(-ENOMEM);

	err = ieee80211_add_chanctx(local, ctx);
	if (err) {
		kfree(ctx);
		return ERR_PTR(err);
	}

	list_add_rcu(&ctx->list, &local->chanctx_list);
	return ctx;
}