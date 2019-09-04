#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int /*<<< orphan*/  radar_enabled; } ;
struct TYPE_5__ {TYPE_1__ conf; } ;
struct ieee80211_local {int /*<<< orphan*/  _oper_chandef; int /*<<< orphan*/  use_chanctx; TYPE_2__ hw; int /*<<< orphan*/  chanctx_mtx; int /*<<< orphan*/  mtx; } ;
struct TYPE_6__ {int /*<<< orphan*/  def; int /*<<< orphan*/  radar_enabled; } ;
struct ieee80211_chanctx {TYPE_3__ conf; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_CONF_CHANGE_CHANNEL ; 
 int drv_add_chanctx (struct ieee80211_local*,struct ieee80211_chanctx*) ; 
 int /*<<< orphan*/  ieee80211_hw_config (struct ieee80211_local*,scalar_t__) ; 
 scalar_t__ ieee80211_idle_off (struct ieee80211_local*) ; 
 int /*<<< orphan*/  ieee80211_recalc_idle (struct ieee80211_local*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ieee80211_add_chanctx(struct ieee80211_local *local,
				 struct ieee80211_chanctx *ctx)
{
	u32 changed;
	int err;

	lockdep_assert_held(&local->mtx);
	lockdep_assert_held(&local->chanctx_mtx);

	if (!local->use_chanctx)
		local->hw.conf.radar_enabled = ctx->conf.radar_enabled;

	/* turn idle off *before* setting channel -- some drivers need that */
	changed = ieee80211_idle_off(local);
	if (changed)
		ieee80211_hw_config(local, changed);

	if (!local->use_chanctx) {
		local->_oper_chandef = ctx->conf.def;
		ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_CHANNEL);
	} else {
		err = drv_add_chanctx(local, ctx);
		if (err) {
			ieee80211_recalc_idle(local);
			return err;
		}
	}

	return 0;
}