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
struct rsi_hw {struct rsi_common* priv; } ;
struct rsi_common {scalar_t__ fsm_state; int /*<<< orphan*/  mutex; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct rsi_hw* priv; } ;

/* Variables and functions */
 scalar_t__ FSM_MAC_INIT_DONE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rsi_mac80211_rfkill_poll(struct ieee80211_hw *hw)
{
	struct rsi_hw *adapter = hw->priv;
	struct rsi_common *common = adapter->priv;

	mutex_lock(&common->mutex);
	if (common->fsm_state != FSM_MAC_INIT_DONE)
		wiphy_rfkill_set_hw_state(hw->wiphy, true);
	else
		wiphy_rfkill_set_hw_state(hw->wiphy, false);
	mutex_unlock(&common->mutex);
}