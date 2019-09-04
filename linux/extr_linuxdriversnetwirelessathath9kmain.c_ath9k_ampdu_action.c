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
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_vif {int dummy; } ;
struct TYPE_2__ {int ampdu_factor; } ;
struct ieee80211_sta {TYPE_1__ ht_cap; int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ieee80211_ampdu_params {int action; int /*<<< orphan*/  ssn; int /*<<< orphan*/  tid; struct ieee80211_sta* sta; } ;
struct ath_softc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  sc_ah; } ;
struct ath_node {int dummy; } ;
struct ath_common {int /*<<< orphan*/  op_flags; } ;
struct ath_atx_tid {int baw_size; } ;
typedef  enum ieee80211_ampdu_mlme_action { ____Placeholder_ieee80211_ampdu_mlme_action } ieee80211_ampdu_mlme_action ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_OP_SCANNING ; 
 int EBUSY ; 
#define  IEEE80211_AMPDU_RX_START 134 
#define  IEEE80211_AMPDU_RX_STOP 133 
#define  IEEE80211_AMPDU_TX_OPERATIONAL 132 
#define  IEEE80211_AMPDU_TX_START 131 
#define  IEEE80211_AMPDU_TX_STOP_CONT 130 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH 129 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH_CONT 128 
 int IEEE80211_MIN_AMPDU_BUF ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_is_chanctx_enabled () ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*) ; 
 struct ath_atx_tid* ath_node_to_tid (struct ath_node*,int /*<<< orphan*/ ) ; 
 int ath_tx_aggr_start (struct ath_softc*,struct ieee80211_sta*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_tx_aggr_stop (struct ath_softc*,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_start_tx_ba_cb_irqsafe (struct ieee80211_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_stop_tx_ba_cb_irqsafe (struct ieee80211_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath9k_ampdu_action(struct ieee80211_hw *hw,
			      struct ieee80211_vif *vif,
			      struct ieee80211_ampdu_params *params)
{
	struct ath_softc *sc = hw->priv;
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	bool flush = false;
	int ret = 0;
	struct ieee80211_sta *sta = params->sta;
	struct ath_node *an = (struct ath_node *)sta->drv_priv;
	enum ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;
	u16 *ssn = &params->ssn;
	struct ath_atx_tid *atid;

	mutex_lock(&sc->mutex);

	switch (action) {
	case IEEE80211_AMPDU_RX_START:
		break;
	case IEEE80211_AMPDU_RX_STOP:
		break;
	case IEEE80211_AMPDU_TX_START:
		if (ath9k_is_chanctx_enabled()) {
			if (test_bit(ATH_OP_SCANNING, &common->op_flags)) {
				ret = -EBUSY;
				break;
			}
		}
		ath9k_ps_wakeup(sc);
		ret = ath_tx_aggr_start(sc, sta, tid, ssn);
		if (!ret)
			ieee80211_start_tx_ba_cb_irqsafe(vif, sta->addr, tid);
		ath9k_ps_restore(sc);
		break;
	case IEEE80211_AMPDU_TX_STOP_FLUSH:
	case IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		flush = true;
		/* fall through */
	case IEEE80211_AMPDU_TX_STOP_CONT:
		ath9k_ps_wakeup(sc);
		ath_tx_aggr_stop(sc, sta, tid);
		if (!flush)
			ieee80211_stop_tx_ba_cb_irqsafe(vif, sta->addr, tid);
		ath9k_ps_restore(sc);
		break;
	case IEEE80211_AMPDU_TX_OPERATIONAL:
		atid = ath_node_to_tid(an, tid);
		atid->baw_size = IEEE80211_MIN_AMPDU_BUF <<
			        sta->ht_cap.ampdu_factor;
		break;
	default:
		ath_err(ath9k_hw_common(sc->sc_ah), "Unknown AMPDU action\n");
	}

	mutex_unlock(&sc->mutex);

	return ret;
}