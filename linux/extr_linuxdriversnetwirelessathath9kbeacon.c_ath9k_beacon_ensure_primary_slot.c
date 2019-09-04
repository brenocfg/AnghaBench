#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ath_vif {int av_bslot; TYPE_2__* chanctx; int /*<<< orphan*/  tsf_adjust; } ;
struct TYPE_3__ {struct ieee80211_vif** bslot; } ;
struct ath_softc {int /*<<< orphan*/  bcon_tasklet; int /*<<< orphan*/  sc_ah; TYPE_2__* cur_chan; TYPE_1__ beacon; } ;
struct ath_common {int dummy; } ;
typedef  scalar_t__ s64 ;
struct TYPE_4__ {scalar_t__ tsf_val; int /*<<< orphan*/  tsf_ts; } ;

/* Variables and functions */
 int ATH_BCBUF ; 
 int /*<<< orphan*/  CONFIG ; 
 scalar_t__ WARN_ON (int) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 scalar_t__ ath9k_hw_get_tsf_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_hw_settsf64 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,long long) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 

void ath9k_beacon_ensure_primary_slot(struct ath_softc *sc)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ieee80211_vif *vif;
	struct ath_vif *avp;
	s64 tsfadjust;
	u32 offset;
	int first_slot = ATH_BCBUF;
	int slot;

	tasklet_disable(&sc->bcon_tasklet);

	/* Find first taken slot. */
	for (slot = 0; slot < ATH_BCBUF; slot++) {
		if (sc->beacon.bslot[slot]) {
			first_slot = slot;
			break;
		}
	}
	if (first_slot == 0)
		goto out;

	/* Re-enumarate all slots, moving them forward. */
	for (slot = 0; slot < ATH_BCBUF; slot++) {
		if (slot + first_slot < ATH_BCBUF) {
			vif = sc->beacon.bslot[slot + first_slot];
			sc->beacon.bslot[slot] = vif;

			if (vif) {
				avp = (void *)vif->drv_priv;
				avp->av_bslot = slot;
			}
		} else {
			sc->beacon.bslot[slot] = NULL;
		}
	}

	vif = sc->beacon.bslot[0];
	if (WARN_ON(!vif))
		goto out;

	/* Get the tsf_adjust value for the new first slot. */
	avp = (void *)vif->drv_priv;
	tsfadjust = le64_to_cpu(avp->tsf_adjust);

	ath_dbg(common, CONFIG,
		"Adjusting global TSF after beacon slot reassignment: %lld\n",
		(signed long long)tsfadjust);

	/* Modify TSF as required and update the HW. */
	avp->chanctx->tsf_val += tsfadjust;
	if (sc->cur_chan == avp->chanctx) {
		offset = ath9k_hw_get_tsf_offset(&avp->chanctx->tsf_ts, NULL);
		ath9k_hw_settsf64(sc->sc_ah, avp->chanctx->tsf_val + offset);
	}

	/* The slots tsf_adjust will be updated by ath9k_beacon_config later. */

out:
	tasklet_enable(&sc->bcon_tasklet);
}