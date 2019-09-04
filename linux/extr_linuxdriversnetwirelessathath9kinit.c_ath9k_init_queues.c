#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__** txq_map; void* uapsdq; } ;
struct TYPE_6__ {void* cabq; int /*<<< orphan*/  beaconq; } ;
struct ath_softc {TYPE_2__ tx; TYPE_3__ beacon; int /*<<< orphan*/  sc_ah; } ;
struct TYPE_4__ {int mac80211_qnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH9K_TX_QUEUE_CAB ; 
 int /*<<< orphan*/  ATH9K_TX_QUEUE_DATA ; 
 int /*<<< orphan*/  ATH9K_TX_QUEUE_UAPSD ; 
 int IEEE80211_NUM_ACS ; 
 int /*<<< orphan*/  ath9k_hw_beaconq_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_cabq_update (struct ath_softc*) ; 
 void* ath_txq_setup (struct ath_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ath9k_init_queues(struct ath_softc *sc)
{
	int i = 0;

	sc->beacon.beaconq = ath9k_hw_beaconq_setup(sc->sc_ah);
	sc->beacon.cabq = ath_txq_setup(sc, ATH9K_TX_QUEUE_CAB, 0);
	ath_cabq_update(sc);

	sc->tx.uapsdq = ath_txq_setup(sc, ATH9K_TX_QUEUE_UAPSD, 0);

	for (i = 0; i < IEEE80211_NUM_ACS; i++) {
		sc->tx.txq_map[i] = ath_txq_setup(sc, ATH9K_TX_QUEUE_DATA, i);
		sc->tx.txq_map[i]->mac80211_qnum = i;
	}
	return 0;
}