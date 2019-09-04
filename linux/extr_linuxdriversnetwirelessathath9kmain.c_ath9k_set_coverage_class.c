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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_softc {int /*<<< orphan*/  mutex; struct ath_hw* sc_ah; } ;
struct TYPE_2__ {int enabled; } ;
struct ath_hw {TYPE_1__ dynack; scalar_t__ coverage_class; } ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ATH9K_TX99 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_enable_dynack (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_hw_init_global_settings (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_setrxfilter (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_calcrxfilter (struct ath_softc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_set_coverage_class(struct ieee80211_hw *hw,
				     s16 coverage_class)
{
	struct ath_softc *sc = hw->priv;
	struct ath_hw *ah = sc->sc_ah;

	if (IS_ENABLED(CONFIG_ATH9K_TX99))
		return;

	mutex_lock(&sc->mutex);

	if (coverage_class >= 0) {
		ah->coverage_class = coverage_class;
		if (ah->dynack.enabled) {
			u32 rfilt;

			ah->dynack.enabled = false;
			rfilt = ath_calcrxfilter(sc);
			ath9k_hw_setrxfilter(ah, rfilt);
		}
		ath9k_ps_wakeup(sc);
		ath9k_hw_init_global_settings(ah);
		ath9k_ps_restore(sc);
	} else if (!ah->dynack.enabled) {
		ath9k_enable_dynack(sc);
	}

	mutex_unlock(&sc->mutex);
}