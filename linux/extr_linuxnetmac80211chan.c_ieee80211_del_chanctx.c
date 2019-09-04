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
struct TYPE_5__ {int radar_enabled; } ;
struct TYPE_6__ {TYPE_2__ conf; } ;
struct cfg80211_chan_def {scalar_t__ center_freq2; TYPE_1__* chan; int /*<<< orphan*/  center_freq1; int /*<<< orphan*/  width; } ;
struct ieee80211_local {TYPE_3__ hw; int /*<<< orphan*/  chanctx_list; struct cfg80211_chan_def _oper_chandef; int /*<<< orphan*/  use_chanctx; int /*<<< orphan*/  chanctx_mtx; } ;
struct ieee80211_chanctx {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CONF_CHANGE_CHANNEL ; 
 int /*<<< orphan*/  NL80211_CHAN_WIDTH_20_NOHT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drv_remove_chanctx (struct ieee80211_local*,struct ieee80211_chanctx*) ; 
 int /*<<< orphan*/  ieee80211_hw_config (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_recalc_idle (struct ieee80211_local*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ieee80211_del_chanctx(struct ieee80211_local *local,
				  struct ieee80211_chanctx *ctx)
{
	lockdep_assert_held(&local->chanctx_mtx);

	if (!local->use_chanctx) {
		struct cfg80211_chan_def *chandef = &local->_oper_chandef;
		chandef->width = NL80211_CHAN_WIDTH_20_NOHT;
		chandef->center_freq1 = chandef->chan->center_freq;
		chandef->center_freq2 = 0;

		/* NOTE: Disabling radar is only valid here for
		 * single channel context. To be sure, check it ...
		 */
		WARN_ON(local->hw.conf.radar_enabled &&
			!list_empty(&local->chanctx_list));

		local->hw.conf.radar_enabled = false;

		ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_CHANNEL);
	} else {
		drv_remove_chanctx(local, ctx);
	}

	ieee80211_recalc_idle(local);
}