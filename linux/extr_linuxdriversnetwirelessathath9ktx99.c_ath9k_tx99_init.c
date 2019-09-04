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
typedef  int /*<<< orphan*/  txctl ;
struct ieee80211_hw {int dummy; } ;
struct ath_tx_control {int /*<<< orphan*/  txq; } ;
struct TYPE_2__ {int /*<<< orphan*/ * txq_map; } ;
struct ath_softc {int tx99_state; int tx99_power; int /*<<< orphan*/  tx99_skb; TYPE_1__ tx; struct ath_hw* sc_ah; struct ieee80211_hw* hw; } ;
struct ath_hw {int dummy; } ;
struct ath_common {int /*<<< orphan*/  op_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_OP_INVALID ; 
 int EINVAL ; 
 int ENOMEM ; 
 size_t IEEE80211_AC_VO ; 
 int MAX_RATE_POWER ; 
 int /*<<< orphan*/  XMIT ; 
 int /*<<< orphan*/  ath9k_build_tx99_skb (struct ath_softc*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_disable_interrupts (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_tx99_set_txpower (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int ath9k_tx99_send (struct ath_softc*,int /*<<< orphan*/ ,struct ath_tx_control*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ath_drain_all_txq (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*) ; 
 int /*<<< orphan*/  ath_reset (struct ath_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_stoprecv (struct ath_softc*) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  memset (struct ath_tx_control*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath9k_tx99_init(struct ath_softc *sc)
{
	struct ieee80211_hw *hw = sc->hw;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath_tx_control txctl;
	int r;

	if (test_bit(ATH_OP_INVALID, &common->op_flags)) {
		ath_err(common,
			"driver is in invalid state unable to use TX99");
		return -EINVAL;
	}

	sc->tx99_skb = ath9k_build_tx99_skb(sc);
	if (!sc->tx99_skb)
		return -ENOMEM;

	memset(&txctl, 0, sizeof(txctl));
	txctl.txq = sc->tx.txq_map[IEEE80211_AC_VO];

	ath_reset(sc, NULL);

	ath9k_ps_wakeup(sc);

	ath9k_hw_disable_interrupts(ah);
	ath_drain_all_txq(sc);
	ath_stoprecv(sc);

	sc->tx99_state = true;

	ieee80211_stop_queues(hw);

	if (sc->tx99_power == MAX_RATE_POWER + 1)
		sc->tx99_power = MAX_RATE_POWER;

	ath9k_hw_tx99_set_txpower(ah, sc->tx99_power);
	r = ath9k_tx99_send(sc, sc->tx99_skb, &txctl);
	if (r) {
		ath_dbg(common, XMIT, "Failed to xmit TX99 skb\n");
		return r;
	}

	ath_dbg(common, XMIT, "TX99 xmit started using %d ( %ddBm)\n",
		sc->tx99_power,
		sc->tx99_power / 2);

	/* We leave the hardware awake as it will be chugging on */

	return 0;
}