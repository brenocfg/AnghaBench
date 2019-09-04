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
struct mac80211_hwsim_data {int roc_duration; int /*<<< orphan*/  roc_start; int /*<<< orphan*/  mutex; struct ieee80211_channel* roc_chan; scalar_t__ hw_scan_request; scalar_t__ tmp_chan; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct mac80211_hwsim_data* priv; } ;
struct ieee80211_channel {int /*<<< orphan*/  center_freq; } ;
typedef  enum ieee80211_roc_type { ____Placeholder_ieee80211_roc_type } ieee80211_roc_type ;

/* Variables and functions */
 int EBUSY ; 
 int HZ ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (struct ieee80211_hw*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mac80211_hwsim_roc(struct ieee80211_hw *hw,
			      struct ieee80211_vif *vif,
			      struct ieee80211_channel *chan,
			      int duration,
			      enum ieee80211_roc_type type)
{
	struct mac80211_hwsim_data *hwsim = hw->priv;

	mutex_lock(&hwsim->mutex);
	if (WARN_ON(hwsim->tmp_chan || hwsim->hw_scan_request)) {
		mutex_unlock(&hwsim->mutex);
		return -EBUSY;
	}

	hwsim->roc_chan = chan;
	hwsim->roc_duration = duration;
	mutex_unlock(&hwsim->mutex);

	wiphy_dbg(hw->wiphy, "hwsim ROC (%d MHz, %d ms)\n",
		  chan->center_freq, duration);
	ieee80211_queue_delayed_work(hw, &hwsim->roc_start, HZ/50);

	return 0;
}