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
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;
struct ath_softc {struct ieee80211_hw* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_deinit_debug (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_deinit_softc (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_deinit_wow (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_deinit_leds (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_rx_cleanup (struct ath_softc*) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  wiphy_rfkill_stop_polling (int /*<<< orphan*/ ) ; 

void ath9k_deinit_device(struct ath_softc *sc)
{
	struct ieee80211_hw *hw = sc->hw;

	ath9k_ps_wakeup(sc);

	wiphy_rfkill_stop_polling(sc->hw->wiphy);
	ath_deinit_leds(sc);

	ath9k_ps_restore(sc);

	ath9k_deinit_debug(sc);
	ath9k_deinit_wow(hw);
	ieee80211_unregister_hw(hw);
	ath_rx_cleanup(sc);
	ath9k_deinit_softc(sc);
}