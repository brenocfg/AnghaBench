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
struct ath_txq {int axq_tx_inprogress; scalar_t__ axq_depth; } ;
struct TYPE_2__ {struct ath_txq** txq_map; } ;
struct ath_softc {int /*<<< orphan*/  sc_ah; TYPE_1__ tx; scalar_t__ tx99_state; } ;

/* Variables and functions */
 int IEEE80211_NUM_ACS ; 
 int /*<<< orphan*/  RESET ; 
 int /*<<< orphan*/  RESET_TYPE_TX_HANG ; 
 int /*<<< orphan*/  ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_queue_reset (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath_txq_lock (struct ath_softc*,struct ath_txq*) ; 
 int /*<<< orphan*/  ath_txq_unlock (struct ath_softc*,struct ath_txq*) ; 

__attribute__((used)) static bool ath_tx_complete_check(struct ath_softc *sc)
{
	struct ath_txq *txq;
	int i;

	if (sc->tx99_state)
		return true;

	for (i = 0; i < IEEE80211_NUM_ACS; i++) {
		txq = sc->tx.txq_map[i];

		ath_txq_lock(sc, txq);
		if (txq->axq_depth) {
			if (txq->axq_tx_inprogress) {
				ath_txq_unlock(sc, txq);
				goto reset;
			}

			txq->axq_tx_inprogress = true;
		}
		ath_txq_unlock(sc, txq);
	}

	return true;

reset:
	ath_dbg(ath9k_hw_common(sc->sc_ah), RESET,
		"tx hung, resetting the chip\n");
	ath9k_queue_reset(sc, RESET_TYPE_TX_HANG);
	return false;

}