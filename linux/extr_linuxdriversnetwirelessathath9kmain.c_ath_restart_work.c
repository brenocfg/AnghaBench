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
struct ath_softc {int /*<<< orphan*/  hw_pll_work; int /*<<< orphan*/  hw; int /*<<< orphan*/  sc_ah; int /*<<< orphan*/  hw_check_work; } ;

/* Variables and functions */
 scalar_t__ AR_SREV_9330 (int /*<<< orphan*/ ) ; 
 scalar_t__ AR_SREV_9340 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH_HW_CHECK_POLL_INT ; 
 int /*<<< orphan*/  ATH_PLL_WORK_INTERVAL ; 
 int /*<<< orphan*/  ath_start_ani (struct ath_softc*) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 

void ath_restart_work(struct ath_softc *sc)
{
	ieee80211_queue_delayed_work(sc->hw, &sc->hw_check_work,
				     ATH_HW_CHECK_POLL_INT);

	if (AR_SREV_9340(sc->sc_ah) || AR_SREV_9330(sc->sc_ah))
		ieee80211_queue_delayed_work(sc->hw, &sc->hw_pll_work,
				     msecs_to_jiffies(ATH_PLL_WORK_INTERVAL));

	ath_start_ani(sc);
}