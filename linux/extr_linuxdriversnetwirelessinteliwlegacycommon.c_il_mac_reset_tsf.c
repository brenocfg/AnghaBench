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
struct TYPE_2__ {int /*<<< orphan*/  filter_flags; } ;
struct il_priv {int /*<<< orphan*/  mutex; TYPE_1__ staging; int /*<<< orphan*/  lock; scalar_t__ timestamp; int /*<<< orphan*/ * beacon_skb; int /*<<< orphan*/  current_ht_config; } ;
struct il_ht_config {int dummy; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; int /*<<< orphan*/  type; } ;
struct ieee80211_hw {struct il_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_MAC80211 (char*,...) ; 
 int /*<<< orphan*/  RXON_FILTER_ASSOC_MSK ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  il_commit_rxon (struct il_priv*) ; 
 int /*<<< orphan*/  il_is_ready_rf (struct il_priv*) ; 
 int /*<<< orphan*/  il_scan_cancel_timeout (struct il_priv*,int) ; 
 int /*<<< orphan*/  il_set_rate (struct il_priv*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
il_mac_reset_tsf(struct ieee80211_hw *hw, struct ieee80211_vif *vif)
{
	struct il_priv *il = hw->priv;
	unsigned long flags;

	mutex_lock(&il->mutex);
	D_MAC80211("enter: type %d, addr %pM\n", vif->type, vif->addr);

	spin_lock_irqsave(&il->lock, flags);

	memset(&il->current_ht_config, 0, sizeof(struct il_ht_config));

	/* new association get rid of ibss beacon skb */
	if (il->beacon_skb)
		dev_kfree_skb(il->beacon_skb);
	il->beacon_skb = NULL;
	il->timestamp = 0;

	spin_unlock_irqrestore(&il->lock, flags);

	il_scan_cancel_timeout(il, 100);
	if (!il_is_ready_rf(il)) {
		D_MAC80211("leave - not ready\n");
		mutex_unlock(&il->mutex);
		return;
	}

	/* we are restarting association process */
	il->staging.filter_flags &= ~RXON_FILTER_ASSOC_MSK;
	il_commit_rxon(il);

	il_set_rate(il);

	D_MAC80211("leave\n");
	mutex_unlock(&il->mutex);
}