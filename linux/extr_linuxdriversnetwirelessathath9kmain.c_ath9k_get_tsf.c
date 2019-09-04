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
typedef  scalar_t__ u64 ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_vif {int /*<<< orphan*/  tsf_adjust; TYPE_1__* chanctx; } ;
struct ath_softc {int /*<<< orphan*/  mutex; TYPE_1__* cur_chan; int /*<<< orphan*/  sc_ah; } ;
struct TYPE_2__ {int /*<<< orphan*/  tsf_ts; scalar_t__ tsf_val; } ;

/* Variables and functions */
 scalar_t__ ath9k_hw_get_tsf_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ath9k_hw_gettsf64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 ath9k_get_tsf(struct ieee80211_hw *hw, struct ieee80211_vif *vif)
{
	struct ath_softc *sc = hw->priv;
	struct ath_vif *avp = (void *)vif->drv_priv;
	u64 tsf;

	mutex_lock(&sc->mutex);
	ath9k_ps_wakeup(sc);
	/* Get current TSF either from HW or kernel time. */
	if (sc->cur_chan == avp->chanctx) {
		tsf = ath9k_hw_gettsf64(sc->sc_ah);
	} else {
		tsf = sc->cur_chan->tsf_val +
		      ath9k_hw_get_tsf_offset(&sc->cur_chan->tsf_ts, NULL);
	}
	tsf += le64_to_cpu(avp->tsf_adjust);
	ath9k_ps_restore(sc);
	mutex_unlock(&sc->mutex);

	return tsf;
}