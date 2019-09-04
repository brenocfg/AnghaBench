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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {size_t priority; scalar_t__ data; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_rx_status {int enc_flags; scalar_t__ bw; scalar_t__ encoding; size_t rate_idx; size_t band; } ;
struct ieee80211_rate {int bitrate; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr2; int /*<<< orphan*/  frame_control; } ;
struct ath_vif {TYPE_2__* chanctx; } ;
struct ath_softc {int airtime_flags; int /*<<< orphan*/  hw; struct ath_hw* sc_ah; } ;
struct ath_rx_status {int /*<<< orphan*/  rs_rate; int /*<<< orphan*/  rs_datalen; } ;
struct ath_node {scalar_t__* airtime_deficit; TYPE_1__* vif; } ;
struct ath_hw {int dummy; } ;
struct ath_common {TYPE_3__* sbands; } ;
struct ath_acq {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {struct ieee80211_rate* bitrates; } ;
struct TYPE_5__ {struct ath_acq* acq; } ;
struct TYPE_4__ {scalar_t__ drv_priv; } ;

/* Variables and functions */
 int AIRTIME_USE_RX ; 
 int /*<<< orphan*/  ATH_AN_2_TID (struct ath_node*,size_t) ; 
 size_t IEEE80211_QOS_CTL_TID_MASK ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 scalar_t__ IS_CCK_RATE (int /*<<< orphan*/ ) ; 
 scalar_t__ RATE_INFO_BW_40 ; 
 int RX_ENC_FLAG_SHORTPRE ; 
 int RX_ENC_FLAG_SHORT_GI ; 
 scalar_t__ RX_ENC_HT ; 
 size_t TID_TO_WME_AC (size_t) ; 
 int WLAN_RC_PHY_CCK ; 
 int WLAN_RC_PHY_OFDM ; 
 int /*<<< orphan*/  __ath_tx_queue_tid (struct ath_softc*,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 scalar_t__ ath9k_hw_computetxtime (struct ath_hw*,int,int,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  ath_debug_airtime (struct ath_softc*,struct ath_node*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ath_pkt_duration (struct ath_softc*,size_t,int /*<<< orphan*/ ,int,int,int) ; 
 struct ieee80211_sta* ieee80211_find_sta_by_ifaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_is_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath_rx_count_airtime(struct ath_softc *sc,
				 struct ath_rx_status *rs,
				 struct sk_buff *skb)
{
	struct ath_node *an;
	struct ath_acq *acq;
	struct ath_vif *avp;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *) skb->data;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ieee80211_sta *sta;
	struct ieee80211_rx_status *rxs;
	const struct ieee80211_rate *rate;
	bool is_sgi, is_40, is_sp;
	int phy;
	u16 len = rs->rs_datalen;
	u32 airtime = 0;
	u8 tidno, acno;

	if (!ieee80211_is_data(hdr->frame_control))
		return;

	rcu_read_lock();

	sta = ieee80211_find_sta_by_ifaddr(sc->hw, hdr->addr2, NULL);
	if (!sta)
		goto exit;
	an = (struct ath_node *) sta->drv_priv;
	avp = (struct ath_vif *) an->vif->drv_priv;
	tidno = skb->priority & IEEE80211_QOS_CTL_TID_MASK;
	acno = TID_TO_WME_AC(tidno);
	acq = &avp->chanctx->acq[acno];

	rxs = IEEE80211_SKB_RXCB(skb);

	is_sgi = !!(rxs->enc_flags & RX_ENC_FLAG_SHORT_GI);
	is_40 = !!(rxs->bw == RATE_INFO_BW_40);
	is_sp = !!(rxs->enc_flags & RX_ENC_FLAG_SHORTPRE);

	if (!!(rxs->encoding == RX_ENC_HT)) {
		/* MCS rates */

		airtime += ath_pkt_duration(sc, rxs->rate_idx, len,
					is_40, is_sgi, is_sp);
	} else {

		phy = IS_CCK_RATE(rs->rs_rate) ? WLAN_RC_PHY_CCK : WLAN_RC_PHY_OFDM;
		rate = &common->sbands[rxs->band].bitrates[rxs->rate_idx];
		airtime += ath9k_hw_computetxtime(ah, phy, rate->bitrate * 100,
						len, rxs->rate_idx, is_sp);
	}

 	if (!!(sc->airtime_flags & AIRTIME_USE_RX)) {
		spin_lock_bh(&acq->lock);
		an->airtime_deficit[acno] -= airtime;
		if (an->airtime_deficit[acno] <= 0)
			__ath_tx_queue_tid(sc, ATH_AN_2_TID(an, tidno));
		spin_unlock_bh(&acq->lock);
	}
	ath_debug_airtime(sc, an, airtime, 0);
exit:
	rcu_read_unlock();
}