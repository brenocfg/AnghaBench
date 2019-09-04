#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  txctl ;
struct sk_buff {int dummy; } ;
struct TYPE_10__ {TYPE_4__* rates; } ;
struct ieee80211_tx_info {int /*<<< orphan*/  paprd; TYPE_5__ control; int /*<<< orphan*/  flags; int /*<<< orphan*/  band; int /*<<< orphan*/  txq; } ;
struct ieee80211_hw {int dummy; } ;
struct ath_tx_control {int /*<<< orphan*/  paprd; TYPE_5__ control; int /*<<< orphan*/  flags; int /*<<< orphan*/  band; int /*<<< orphan*/  txq; } ;
struct TYPE_8__ {TYPE_2__* chan; } ;
struct TYPE_6__ {int /*<<< orphan*/ * txq_map; } ;
struct ath_softc {int /*<<< orphan*/  paprd_complete; TYPE_3__ cur_chandef; TYPE_1__ tx; struct ath_hw* sc_ah; struct ieee80211_hw* hw; } ;
struct ath_hw {int dummy; } ;
struct ath_common {int dummy; } ;
struct TYPE_9__ {int idx; int count; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  band; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_PAPRD_TIMEOUT ; 
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  CALIBRATE ; 
 size_t IEEE80211_AC_BE ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IEEE80211_TX_CTL_NO_ACK ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_MCS ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ath_tx_start (struct ieee80211_hw*,struct sk_buff*,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ieee80211_tx_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ath_paprd_send_frame(struct ath_softc *sc, struct sk_buff *skb, int chain)
{
	struct ieee80211_hw *hw = sc->hw;
	struct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath_tx_control txctl;
	unsigned long time_left;

	memset(&txctl, 0, sizeof(txctl));
	txctl.txq = sc->tx.txq_map[IEEE80211_AC_BE];

	memset(tx_info, 0, sizeof(*tx_info));
	tx_info->band = sc->cur_chandef.chan->band;
	tx_info->flags |= IEEE80211_TX_CTL_NO_ACK;
	tx_info->control.rates[0].idx = 0;
	tx_info->control.rates[0].count = 1;
	tx_info->control.rates[0].flags = IEEE80211_TX_RC_MCS;
	tx_info->control.rates[1].idx = -1;

	init_completion(&sc->paprd_complete);
	txctl.paprd = BIT(chain);

	if (ath_tx_start(hw, skb, &txctl) != 0) {
		ath_dbg(common, CALIBRATE, "PAPRD TX failed\n");
		dev_kfree_skb_any(skb);
		return false;
	}

	time_left = wait_for_completion_timeout(&sc->paprd_complete,
			msecs_to_jiffies(ATH_PAPRD_TIMEOUT));

	if (!time_left)
		ath_dbg(common, CALIBRATE,
			"Timeout waiting for paprd training on TX chain %d\n",
			chain);

	return !!time_left;
}