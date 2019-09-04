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
struct ath_softc {int tx99_state; struct ath_hw* sc_ah; int /*<<< orphan*/ * tx99_skb; int /*<<< orphan*/  hw; } ;
struct ath_hw {int dummy; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XMIT ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_enable_interrupts (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_interrupts (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_tx99_stop (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath_drain_all_txq (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_startrecv (struct ath_softc*) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_tx99_stop(struct ath_softc *sc)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);

	ath_drain_all_txq(sc);
	ath_startrecv(sc);

	ath9k_hw_set_interrupts(ah);
	ath9k_hw_enable_interrupts(ah);

	ieee80211_wake_queues(sc->hw);

	kfree_skb(sc->tx99_skb);
	sc->tx99_skb = NULL;
	sc->tx99_state = false;

	ath9k_hw_tx99_stop(sc->sc_ah);
	ath_dbg(common, XMIT, "TX99 stopped\n");
}