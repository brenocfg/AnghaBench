#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_vif {int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ath_vif {int /*<<< orphan*/  aid; int /*<<< orphan*/  bssid; } ;
struct ath_softc {int ps_flags; TYPE_2__* sc_ah; int /*<<< orphan*/  sc_pm_lock; } ;
struct ath_common {int /*<<< orphan*/  curbssid; void* last_rssi; int /*<<< orphan*/  curaid; int /*<<< orphan*/  op_flags; } ;
struct TYPE_5__ {void* avgbrssi; } ;
struct TYPE_6__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_OP_PRIM_STA_VIF ; 
 void* ATH_RSSI_DUMMY_MARKER ; 
 int /*<<< orphan*/  CONFIG ; 
 int PS_BEACON_SYNC ; 
 int PS_WAIT_FOR_BEACON ; 
 struct ath_common* ath9k_hw_common (TYPE_2__*) ; 
 scalar_t__ ath9k_hw_mci_is_enabled (TYPE_2__*) ; 
 int /*<<< orphan*/  ath9k_hw_write_associd (TYPE_2__*) ; 
 int /*<<< orphan*/  ath9k_mci_update_wlan_channels (struct ath_softc*,int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ath9k_set_assoc_state(struct ath_softc *sc,
				  struct ieee80211_vif *vif, bool changed)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_vif *avp = (struct ath_vif *)vif->drv_priv;
	unsigned long flags;

	set_bit(ATH_OP_PRIM_STA_VIF, &common->op_flags);

	ether_addr_copy(common->curbssid, avp->bssid);
	common->curaid = avp->aid;
	ath9k_hw_write_associd(sc->sc_ah);

	if (changed) {
		common->last_rssi = ATH_RSSI_DUMMY_MARKER;
		sc->sc_ah->stats.avgbrssi = ATH_RSSI_DUMMY_MARKER;

		spin_lock_irqsave(&sc->sc_pm_lock, flags);
		sc->ps_flags |= PS_BEACON_SYNC | PS_WAIT_FOR_BEACON;
		spin_unlock_irqrestore(&sc->sc_pm_lock, flags);
	}

	if (ath9k_hw_mci_is_enabled(sc->sc_ah))
		ath9k_mci_update_wlan_channels(sc, false);

	ath_dbg(common, CONFIG,
		"Primary Station interface: %pM, BSSID: %pM\n",
		vif->addr, common->curbssid);
}