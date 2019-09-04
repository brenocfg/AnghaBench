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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct ath9k_htc_priv* priv; } ;
struct ath_common {int /*<<< orphan*/  op_flags; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ps_work; int /*<<< orphan*/  beacon_lock; int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_OP_SCANNING ; 
 int /*<<< orphan*/  ath9k_htc_stop_ani (struct ath9k_htc_priv*) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_htc_sw_scan_start(struct ieee80211_hw *hw,
				    struct ieee80211_vif *vif,
				    const u8 *mac_addr)
{
	struct ath9k_htc_priv *priv = hw->priv;
	struct ath_common *common = ath9k_hw_common(priv->ah);

	mutex_lock(&priv->mutex);
	spin_lock_bh(&priv->beacon_lock);
	set_bit(ATH_OP_SCANNING, &common->op_flags);
	spin_unlock_bh(&priv->beacon_lock);
	cancel_work_sync(&priv->ps_work);
	ath9k_htc_stop_ani(priv);
	mutex_unlock(&priv->mutex);
}