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
struct ieee80211_vif {int type; int p2p; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_vif {int /*<<< orphan*/  chanctx; } ;
struct ath_softc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  sc_ah; } ;
struct ath_common {int dummy; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  CONFIG_ATH9K_TX99 ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_assign_hw_queues (struct ieee80211_hw*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ath9k_beacon_assign_slot (struct ath_softc*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ath9k_beacon_remove_slot (struct ath_softc*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ath9k_calculate_summary_state (struct ath_softc*,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_set_txpower (struct ath_softc*,struct ieee80211_vif*) ; 
 scalar_t__ ath9k_uses_beacons (int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath9k_change_interface(struct ieee80211_hw *hw,
				  struct ieee80211_vif *vif,
				  enum nl80211_iftype new_type,
				  bool p2p)
{
	struct ath_softc *sc = hw->priv;
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_vif *avp = (void *)vif->drv_priv;

	mutex_lock(&sc->mutex);

	if (IS_ENABLED(CONFIG_ATH9K_TX99)) {
		mutex_unlock(&sc->mutex);
		return -EOPNOTSUPP;
	}

	ath_dbg(common, CONFIG, "Change Interface\n");

	if (ath9k_uses_beacons(vif->type))
		ath9k_beacon_remove_slot(sc, vif);

	vif->type = new_type;
	vif->p2p = p2p;

	if (ath9k_uses_beacons(vif->type))
		ath9k_beacon_assign_slot(sc, vif);

	ath9k_assign_hw_queues(hw, vif);
	ath9k_calculate_summary_state(sc, avp->chanctx);

	ath9k_set_txpower(sc, vif);

	mutex_unlock(&sc->mutex);
	return 0;
}