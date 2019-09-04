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
struct mwl8k_priv {int /*<<< orphan*/  fw_mutex; int /*<<< orphan*/ * fw_mutex_owner; int /*<<< orphan*/  hw_restart_in_progress; int /*<<< orphan*/  fw_mutex_depth; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_wake_queues (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mwl8k_fw_unlock(struct ieee80211_hw *hw)
{
	struct mwl8k_priv *priv = hw->priv;

	if (!--priv->fw_mutex_depth) {
		if (!priv->hw_restart_in_progress)
			ieee80211_wake_queues(hw);

		priv->fw_mutex_owner = NULL;
		mutex_unlock(&priv->fw_mutex);
	}
}