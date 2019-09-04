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
struct ath9k_htc_priv {int rearm_ani; int reconfig_beacon; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 int /*<<< orphan*/  ath9k_htc_beacon_reconfig (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_ps_restore (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_ps_wakeup (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_start_ani (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_vif_iter ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ath9k_htc_priv*) ; 

__attribute__((used)) static void ath9k_htc_vif_reconfig(struct ath9k_htc_priv *priv)
{
	priv->rearm_ani = false;
	priv->reconfig_beacon = false;

	ieee80211_iterate_active_interfaces_atomic(
		priv->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		ath9k_htc_vif_iter, priv);
	if (priv->rearm_ani)
		ath9k_htc_start_ani(priv);

	if (priv->reconfig_beacon) {
		ath9k_htc_ps_wakeup(priv);
		ath9k_htc_beacon_reconfig(priv);
		ath9k_htc_ps_restore(priv);
	}
}