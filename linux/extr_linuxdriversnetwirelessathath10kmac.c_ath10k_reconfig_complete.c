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
struct ieee80211_hw {struct ath10k* priv; } ;
struct ath10k {scalar_t__ state; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  hw; } ;
typedef  enum ieee80211_reconfig_type { ____Placeholder_ieee80211_reconfig_type } ieee80211_reconfig_type ;

/* Variables and functions */
 scalar_t__ ATH10K_STATE_ON ; 
 scalar_t__ ATH10K_STATE_RESTARTED ; 
 int IEEE80211_RECONFIG_TYPE_RESTART ; 
 int /*<<< orphan*/  ath10k_info (struct ath10k*,char*) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_reconfig_complete(struct ieee80211_hw *hw,
				     enum ieee80211_reconfig_type reconfig_type)
{
	struct ath10k *ar = hw->priv;

	if (reconfig_type != IEEE80211_RECONFIG_TYPE_RESTART)
		return;

	mutex_lock(&ar->conf_mutex);

	/* If device failed to restart it will be in a different state, e.g.
	 * ATH10K_STATE_WEDGED
	 */
	if (ar->state == ATH10K_STATE_RESTARTED) {
		ath10k_info(ar, "device successfully recovered\n");
		ar->state = ATH10K_STATE_ON;
		ieee80211_wake_queues(ar->hw);
	}

	mutex_unlock(&ar->conf_mutex);
}