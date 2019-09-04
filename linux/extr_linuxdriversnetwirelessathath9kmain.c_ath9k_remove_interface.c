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
struct ieee80211_vif {int /*<<< orphan*/  type; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_vif {int /*<<< orphan*/  chanctx; int /*<<< orphan*/  mcast_node; int /*<<< orphan*/  list; } ;
struct ath_softc {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * tx99_vif; TYPE_1__* cur_chan; int /*<<< orphan*/  sc_ah; } ;
struct ath_common {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nvifs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  ath9k_beacon_remove_slot (struct ath_softc*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ath9k_calculate_summary_state (struct ath_softc*,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_is_chanctx_enabled () ; 
 int /*<<< orphan*/  ath9k_p2p_remove_vif (struct ath_softc*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ath9k_set_txpower (struct ath_softc*,int /*<<< orphan*/ *) ; 
 scalar_t__ ath9k_uses_beacons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath_tx_node_cleanup (struct ath_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_remove_interface(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif)
{
	struct ath_softc *sc = hw->priv;
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_vif *avp = (void *)vif->drv_priv;

	ath_dbg(common, CONFIG, "Detach Interface\n");

	mutex_lock(&sc->mutex);

	ath9k_p2p_remove_vif(sc, vif);

	sc->cur_chan->nvifs--;
	sc->tx99_vif = NULL;
	if (!ath9k_is_chanctx_enabled())
		list_del(&avp->list);

	if (ath9k_uses_beacons(vif->type))
		ath9k_beacon_remove_slot(sc, vif);

	ath_tx_node_cleanup(sc, &avp->mcast_node);

	ath9k_calculate_summary_state(sc, avp->chanctx);

	ath9k_set_txpower(sc, NULL);

	mutex_unlock(&sc->mutex);
}