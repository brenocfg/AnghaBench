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
typedef  int u32 ;
struct wiphy {int coverage_class; scalar_t__ retry_short; scalar_t__ retry_long; int /*<<< orphan*/  rts_threshold; int /*<<< orphan*/  frag_threshold; } ;
struct TYPE_3__ {scalar_t__ short_frame_max_tx_count; scalar_t__ long_frame_max_tx_count; } ;
struct TYPE_4__ {TYPE_1__ conf; } ;
struct ieee80211_local {TYPE_2__ hw; } ;
typedef  int s16 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IEEE80211_CONF_CHANGE_RETRY_LIMITS ; 
 scalar_t__ IEEE80211_MAX_TX_RETRY ; 
 int WIPHY_PARAM_COVERAGE_CLASS ; 
 int WIPHY_PARAM_DYN_ACK ; 
 int WIPHY_PARAM_FRAG_THRESHOLD ; 
 int WIPHY_PARAM_RETRY_LONG ; 
 int WIPHY_PARAM_RETRY_SHORT ; 
 int WIPHY_PARAM_RTS_THRESHOLD ; 
 int WIPHY_PARAM_TXQ_LIMIT ; 
 int WIPHY_PARAM_TXQ_MEMORY_LIMIT ; 
 int WIPHY_PARAM_TXQ_QUANTUM ; 
 int drv_set_coverage_class (struct ieee80211_local*,int) ; 
 int drv_set_frag_threshold (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int drv_set_rts_threshold (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_check_fast_xmit_all (struct ieee80211_local*) ; 
 int /*<<< orphan*/  ieee80211_hw_config (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_txq_set_params (struct ieee80211_local*) ; 
 struct ieee80211_local* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int ieee80211_set_wiphy_params(struct wiphy *wiphy, u32 changed)
{
	struct ieee80211_local *local = wiphy_priv(wiphy);
	int err;

	if (changed & WIPHY_PARAM_FRAG_THRESHOLD) {
		ieee80211_check_fast_xmit_all(local);

		err = drv_set_frag_threshold(local, wiphy->frag_threshold);

		if (err) {
			ieee80211_check_fast_xmit_all(local);
			return err;
		}
	}

	if ((changed & WIPHY_PARAM_COVERAGE_CLASS) ||
	    (changed & WIPHY_PARAM_DYN_ACK)) {
		s16 coverage_class;

		coverage_class = changed & WIPHY_PARAM_COVERAGE_CLASS ?
					wiphy->coverage_class : -1;
		err = drv_set_coverage_class(local, coverage_class);

		if (err)
			return err;
	}

	if (changed & WIPHY_PARAM_RTS_THRESHOLD) {
		err = drv_set_rts_threshold(local, wiphy->rts_threshold);

		if (err)
			return err;
	}

	if (changed & WIPHY_PARAM_RETRY_SHORT) {
		if (wiphy->retry_short > IEEE80211_MAX_TX_RETRY)
			return -EINVAL;
		local->hw.conf.short_frame_max_tx_count = wiphy->retry_short;
	}
	if (changed & WIPHY_PARAM_RETRY_LONG) {
		if (wiphy->retry_long > IEEE80211_MAX_TX_RETRY)
			return -EINVAL;
		local->hw.conf.long_frame_max_tx_count = wiphy->retry_long;
	}
	if (changed &
	    (WIPHY_PARAM_RETRY_SHORT | WIPHY_PARAM_RETRY_LONG))
		ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_RETRY_LIMITS);

	if (changed & (WIPHY_PARAM_TXQ_LIMIT |
		       WIPHY_PARAM_TXQ_MEMORY_LIMIT |
		       WIPHY_PARAM_TXQ_QUANTUM))
		ieee80211_txq_set_params(local);

	return 0;
}