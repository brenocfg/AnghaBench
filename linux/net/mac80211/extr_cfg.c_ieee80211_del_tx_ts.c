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
typedef  scalar_t__ u8 ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct ieee80211_if_managed {struct ieee80211_sta_tx_tspec* tx_tspec; } ;
struct TYPE_2__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_1__ u; } ;
struct ieee80211_sta_tx_tspec {scalar_t__ tsid; int up; int downgraded; int /*<<< orphan*/  action; int /*<<< orphan*/  admitted_time; } ;
struct ieee80211_local {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int IEEE80211_NUM_ACS ; 
 int /*<<< orphan*/  TX_TSPEC_ACTION_STOP_DOWNGRADE ; 
 int /*<<< orphan*/  ieee80211_flush_queues (struct ieee80211_local*,struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  ieee80211_sta_handle_tspec_ac_params (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  memset (struct ieee80211_sta_tx_tspec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  synchronize_net () ; 
 struct ieee80211_local* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int ieee80211_del_tx_ts(struct wiphy *wiphy, struct net_device *dev,
			       u8 tsid, const u8 *peer)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	struct ieee80211_local *local = wiphy_priv(wiphy);
	int ac;

	for (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		struct ieee80211_sta_tx_tspec *tx_tspec = &ifmgd->tx_tspec[ac];

		/* skip unused entries */
		if (!tx_tspec->admitted_time)
			continue;

		if (tx_tspec->tsid != tsid)
			continue;

		/* due to this new packets will be reassigned to non-ACM ACs */
		tx_tspec->up = -1;

		/* Make sure that all packets have been sent to avoid to
		 * restore the QoS params on packets that are still on the
		 * queues.
		 */
		synchronize_net();
		ieee80211_flush_queues(local, sdata, false);

		/* restore the normal QoS parameters
		 * (unconditionally to avoid races)
		 */
		tx_tspec->action = TX_TSPEC_ACTION_STOP_DOWNGRADE;
		tx_tspec->downgraded = false;
		ieee80211_sta_handle_tspec_ac_params(sdata);

		/* finally clear all the data */
		memset(tx_tspec, 0, sizeof(*tx_tspec));

		return 0;
	}

	return -ENOENT;
}