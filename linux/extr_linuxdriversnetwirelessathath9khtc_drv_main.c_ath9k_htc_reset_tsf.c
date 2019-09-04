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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct ath9k_htc_priv* priv; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_htc_ps_restore (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_ps_wakeup (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_hw_reset_tsf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_htc_reset_tsf(struct ieee80211_hw *hw,
				struct ieee80211_vif *vif)
{
	struct ath9k_htc_priv *priv = hw->priv;

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);
	ath9k_hw_reset_tsf(priv->ah);
	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);
}