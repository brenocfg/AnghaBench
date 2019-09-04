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
struct mwl8k_priv {int hw_restart_in_progress; scalar_t__ hw_restart_owner; int pending_tx_pkts; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/ * tx_wait; int /*<<< orphan*/  fw_reload; int /*<<< orphan*/  watchdog_event_pending; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct mwl8k_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MWL8K_TX_WAIT_TIMEOUT_MS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  ieee80211_queue_work (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl8k_dump_tx_rings (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mwl8k_tx_start (struct mwl8k_priv*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_wait ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_notice (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int mwl8k_tx_wait_empty(struct ieee80211_hw *hw)
{
	struct mwl8k_priv *priv = hw->priv;
	DECLARE_COMPLETION_ONSTACK(tx_wait);
	int retry;
	int rc;

	might_sleep();

	/* Since fw restart is in progress, allow only the firmware
	 * commands from the restart code and block the other
	 * commands since they are going to fail in any case since
	 * the firmware has crashed
	 */
	if (priv->hw_restart_in_progress) {
		if (priv->hw_restart_owner == current)
			return 0;
		else
			return -EBUSY;
	}

	if (atomic_read(&priv->watchdog_event_pending))
		return 0;

	/*
	 * The TX queues are stopped at this point, so this test
	 * doesn't need to take ->tx_lock.
	 */
	if (!priv->pending_tx_pkts)
		return 0;

	retry = 1;
	rc = 0;

	spin_lock_bh(&priv->tx_lock);
	priv->tx_wait = &tx_wait;
	while (!rc) {
		int oldcount;
		unsigned long timeout;

		oldcount = priv->pending_tx_pkts;

		spin_unlock_bh(&priv->tx_lock);
		timeout = wait_for_completion_timeout(&tx_wait,
			    msecs_to_jiffies(MWL8K_TX_WAIT_TIMEOUT_MS));

		if (atomic_read(&priv->watchdog_event_pending)) {
			spin_lock_bh(&priv->tx_lock);
			priv->tx_wait = NULL;
			spin_unlock_bh(&priv->tx_lock);
			return 0;
		}

		spin_lock_bh(&priv->tx_lock);

		if (timeout || !priv->pending_tx_pkts) {
			WARN_ON(priv->pending_tx_pkts);
			if (retry)
				wiphy_notice(hw->wiphy, "tx rings drained\n");
			break;
		}

		if (retry) {
			mwl8k_tx_start(priv);
			retry = 0;
			continue;
		}

		if (priv->pending_tx_pkts < oldcount) {
			wiphy_notice(hw->wiphy,
				     "waiting for tx rings to drain (%d -> %d pkts)\n",
				     oldcount, priv->pending_tx_pkts);
			retry = 1;
			continue;
		}

		priv->tx_wait = NULL;

		wiphy_err(hw->wiphy, "tx rings stuck for %d ms\n",
			  MWL8K_TX_WAIT_TIMEOUT_MS);
		mwl8k_dump_tx_rings(hw);
		priv->hw_restart_in_progress = true;
		ieee80211_queue_work(hw, &priv->fw_reload);

		rc = -ETIMEDOUT;
	}
	priv->tx_wait = NULL;
	spin_unlock_bh(&priv->tx_lock);

	return rc;
}