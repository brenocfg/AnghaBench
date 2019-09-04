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
typedef  int /*<<< orphan*/  u16 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_ampdu_params {int action; int /*<<< orphan*/  ssn; int /*<<< orphan*/  tid; struct ieee80211_sta* sta; } ;
typedef  enum ieee80211_ampdu_mlme_action { ____Placeholder_ieee80211_ampdu_mlme_action } ieee80211_ampdu_mlme_action ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_MAC80211 ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int EOPNOTSUPP ; 
#define  IEEE80211_AMPDU_RX_START 134 
#define  IEEE80211_AMPDU_RX_STOP 133 
#define  IEEE80211_AMPDU_TX_OPERATIONAL 132 
#define  IEEE80211_AMPDU_TX_START 131 
#define  IEEE80211_AMPDU_TX_STOP_CONT 130 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH 129 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH_CONT 128 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_rx_agg_start (struct ieee80211_hw*,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 int rtl_rx_agg_stop (struct ieee80211_hw*,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_tx_agg_oper (struct ieee80211_hw*,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 int rtl_tx_agg_start (struct ieee80211_hw*,struct ieee80211_vif*,struct ieee80211_sta*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rtl_tx_agg_stop (struct ieee80211_hw*,struct ieee80211_vif*,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl_op_ampdu_action(struct ieee80211_hw *hw,
			       struct ieee80211_vif *vif,
			       struct ieee80211_ampdu_params *params)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct ieee80211_sta *sta = params->sta;
	enum ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;
	u16 *ssn = &params->ssn;

	switch (action) {
	case IEEE80211_AMPDU_TX_START:
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_TRACE,
			 "IEEE80211_AMPDU_TX_START: TID:%d\n", tid);
		return rtl_tx_agg_start(hw, vif, sta, tid, ssn);
	case IEEE80211_AMPDU_TX_STOP_CONT:
	case IEEE80211_AMPDU_TX_STOP_FLUSH:
	case IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_TRACE,
			 "IEEE80211_AMPDU_TX_STOP: TID:%d\n", tid);
		return rtl_tx_agg_stop(hw, vif, sta, tid);
	case IEEE80211_AMPDU_TX_OPERATIONAL:
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_TRACE,
			 "IEEE80211_AMPDU_TX_OPERATIONAL:TID:%d\n", tid);
		rtl_tx_agg_oper(hw, sta, tid);
		break;
	case IEEE80211_AMPDU_RX_START:
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_TRACE,
			 "IEEE80211_AMPDU_RX_START:TID:%d\n", tid);
		return rtl_rx_agg_start(hw, sta, tid);
	case IEEE80211_AMPDU_RX_STOP:
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_TRACE,
			 "IEEE80211_AMPDU_RX_STOP:TID:%d\n", tid);
		return rtl_rx_agg_stop(hw, sta, tid);
	default:
		pr_err("IEEE80211_AMPDU_ERR!!!!:\n");
		return -EOPNOTSUPP;
	}
	return 0;
}