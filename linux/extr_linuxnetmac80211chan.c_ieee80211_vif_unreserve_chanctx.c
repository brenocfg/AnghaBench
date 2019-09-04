#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_sub_if_data {TYPE_2__* local; struct ieee80211_chanctx* reserved_chanctx; int /*<<< orphan*/  reserved_chanctx_list; } ;
struct ieee80211_chanctx {scalar_t__ replace_state; int /*<<< orphan*/  list; TYPE_1__* replace_ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  chanctx_mtx; } ;
struct TYPE_4__ {scalar_t__ replace_state; struct ieee80211_chanctx* replace_ctx; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IEEE80211_CHANCTX_REPLACES_OTHER ; 
 scalar_t__ IEEE80211_CHANCTX_REPLACE_NONE ; 
 scalar_t__ IEEE80211_CHANCTX_WILL_BE_REPLACED ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ ieee80211_chanctx_refcount (TYPE_2__*,struct ieee80211_chanctx*) ; 
 int /*<<< orphan*/  ieee80211_free_chanctx (TYPE_2__*,struct ieee80211_chanctx*) ; 
 int /*<<< orphan*/  kfree_rcu (struct ieee80211_chanctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_head ; 

int ieee80211_vif_unreserve_chanctx(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_chanctx *ctx = sdata->reserved_chanctx;

	lockdep_assert_held(&sdata->local->chanctx_mtx);

	if (WARN_ON(!ctx))
		return -EINVAL;

	list_del(&sdata->reserved_chanctx_list);
	sdata->reserved_chanctx = NULL;

	if (ieee80211_chanctx_refcount(sdata->local, ctx) == 0) {
		if (ctx->replace_state == IEEE80211_CHANCTX_REPLACES_OTHER) {
			if (WARN_ON(!ctx->replace_ctx))
				return -EINVAL;

			WARN_ON(ctx->replace_ctx->replace_state !=
			        IEEE80211_CHANCTX_WILL_BE_REPLACED);
			WARN_ON(ctx->replace_ctx->replace_ctx != ctx);

			ctx->replace_ctx->replace_ctx = NULL;
			ctx->replace_ctx->replace_state =
					IEEE80211_CHANCTX_REPLACE_NONE;

			list_del_rcu(&ctx->list);
			kfree_rcu(ctx, rcu_head);
		} else {
			ieee80211_free_chanctx(sdata->local, ctx);
		}
	}

	return 0;
}