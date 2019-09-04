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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int* data; int len; scalar_t__ cb; } ;
struct mt76x2_sta {scalar_t__ inactive_count; int /*<<< orphan*/  rssi; } ;
struct mt76x2_rxwi {int rxinfo; int ctl; int /*<<< orphan*/ * rssi; int /*<<< orphan*/  tid_sn; int /*<<< orphan*/  rate; } ;
struct TYPE_5__ {TYPE_1__* chan; } ;
struct TYPE_6__ {TYPE_2__ chandef; int /*<<< orphan*/  state; } ;
struct mt76x2_dev {TYPE_3__ mt76; } ;
struct mt76_rx_status {int* iv; int aggr; int chains; int /*<<< orphan*/  signal; void* seqno; void* tid; int /*<<< orphan*/  band; int /*<<< orphan*/  freq; void** chain_signal; int /*<<< orphan*/  flag; int /*<<< orphan*/  wcid; } ;
struct TYPE_4__ {int /*<<< orphan*/  band; int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 void* FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT76_STATE_RUNNING ; 
 int MT_RXINFO_BA ; 
 int MT_RXINFO_DECRYPT ; 
 int MT_RXINFO_FRAG ; 
 int MT_RXINFO_L2PAD ; 
 int MT_RXINFO_NULL ; 
 int /*<<< orphan*/  MT_RXINFO_PN_LEN ; 
 int /*<<< orphan*/  MT_RXINFO_UNICAST ; 
 int /*<<< orphan*/  MT_RXWI_CTL_MPDU_LEN ; 
 int /*<<< orphan*/  MT_RXWI_CTL_WCID ; 
 int /*<<< orphan*/  MT_RXWI_SN ; 
 int /*<<< orphan*/  MT_RXWI_TID ; 
 int /*<<< orphan*/  RX_FLAG_DECRYPTED ; 
 int /*<<< orphan*/  RX_FLAG_IV_STRIPPED ; 
 int /*<<< orphan*/  RX_FLAG_MIC_STRIPPED ; 
 int /*<<< orphan*/  RX_FLAG_MMIC_STRIPPED ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ewma_signal_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ieee80211_get_hdrlen_from_skb (struct sk_buff*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int) ; 
 int /*<<< orphan*/  max (void*,void*) ; 
 void* mt76x2_mac_get_rssi (struct mt76x2_dev*,int /*<<< orphan*/ ,int) ; 
 int mt76x2_mac_process_rate (struct mt76_rx_status*,int) ; 
 int /*<<< orphan*/  mt76x2_remove_hdr_pad (struct sk_buff*,int) ; 
 struct mt76x2_sta* mt76x2_rx_get_sta (struct mt76x2_dev*,int) ; 
 int /*<<< orphan*/  mt76x2_rx_get_sta_wcid (struct mt76x2_dev*,struct mt76x2_sta*,int) ; 
 int /*<<< orphan*/  pskb_trim (struct sk_buff*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mt76x2_mac_process_rx(struct mt76x2_dev *dev, struct sk_buff *skb,
			  void *rxi)
{
	struct mt76_rx_status *status = (struct mt76_rx_status *) skb->cb;
	struct mt76x2_rxwi *rxwi = rxi;
	struct mt76x2_sta *sta;
	u32 rxinfo = le32_to_cpu(rxwi->rxinfo);
	u32 ctl = le32_to_cpu(rxwi->ctl);
	u16 rate = le16_to_cpu(rxwi->rate);
	u16 tid_sn = le16_to_cpu(rxwi->tid_sn);
	bool unicast = rxwi->rxinfo & cpu_to_le32(MT_RXINFO_UNICAST);
	int pad_len = 0;
	u8 pn_len;
	u8 wcid;
	int len;

	if (!test_bit(MT76_STATE_RUNNING, &dev->mt76.state))
		return -EINVAL;

	if (rxinfo & MT_RXINFO_L2PAD)
		pad_len += 2;

	if (rxinfo & MT_RXINFO_DECRYPT) {
		status->flag |= RX_FLAG_DECRYPTED;
		status->flag |= RX_FLAG_MMIC_STRIPPED;
		status->flag |= RX_FLAG_MIC_STRIPPED;
		status->flag |= RX_FLAG_IV_STRIPPED;
	}

	wcid = FIELD_GET(MT_RXWI_CTL_WCID, ctl);
	sta = mt76x2_rx_get_sta(dev, wcid);
	status->wcid = mt76x2_rx_get_sta_wcid(dev, sta, unicast);

	len = FIELD_GET(MT_RXWI_CTL_MPDU_LEN, ctl);
	pn_len = FIELD_GET(MT_RXINFO_PN_LEN, rxinfo);
	if (pn_len) {
		int offset = ieee80211_get_hdrlen_from_skb(skb) + pad_len;
		u8 *data = skb->data + offset;

		status->iv[0] = data[7];
		status->iv[1] = data[6];
		status->iv[2] = data[5];
		status->iv[3] = data[4];
		status->iv[4] = data[1];
		status->iv[5] = data[0];

		/*
		 * Driver CCMP validation can't deal with fragments.
		 * Let mac80211 take care of it.
		 */
		if (rxinfo & MT_RXINFO_FRAG) {
			status->flag &= ~RX_FLAG_IV_STRIPPED;
		} else {
			pad_len += pn_len << 2;
			len -= pn_len << 2;
		}
	}

	mt76x2_remove_hdr_pad(skb, pad_len);

	if ((rxinfo & MT_RXINFO_BA) && !(rxinfo & MT_RXINFO_NULL))
		status->aggr = true;

	if (WARN_ON_ONCE(len > skb->len))
		return -EINVAL;

	pskb_trim(skb, len);
	status->chains = BIT(0) | BIT(1);
	status->chain_signal[0] = mt76x2_mac_get_rssi(dev, rxwi->rssi[0], 0);
	status->chain_signal[1] = mt76x2_mac_get_rssi(dev, rxwi->rssi[1], 1);
	status->signal = max(status->chain_signal[0], status->chain_signal[1]);
	status->freq = dev->mt76.chandef.chan->center_freq;
	status->band = dev->mt76.chandef.chan->band;

	status->tid = FIELD_GET(MT_RXWI_TID, tid_sn);
	status->seqno = FIELD_GET(MT_RXWI_SN, tid_sn);

	if (sta) {
		ewma_signal_add(&sta->rssi, status->signal);
		sta->inactive_count = 0;
	}

	return mt76x2_mac_process_rate(status, rate);
}