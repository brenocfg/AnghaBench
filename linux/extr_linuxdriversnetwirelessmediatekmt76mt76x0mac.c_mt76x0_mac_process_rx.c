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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct mt76x0_rxwi {int rxinfo; int /*<<< orphan*/  rate; int /*<<< orphan*/  ctl; } ;
struct TYPE_5__ {TYPE_1__* chan; } ;
struct TYPE_6__ {TYPE_2__ chandef; } ;
struct mt76x0_dev {int avg_rssi; int /*<<< orphan*/  con_mon_lock; TYPE_3__ mt76; } ;
struct ieee80211_rx_status {int flag; int* chain_signal; int signal; int /*<<< orphan*/  band; int /*<<< orphan*/  freq; int /*<<< orphan*/  chains; } ;
struct TYPE_4__ {int /*<<< orphan*/  band; int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  MT_RXINFO_DECRYPT ; 
 int /*<<< orphan*/  MT_RXINFO_U2M ; 
 int /*<<< orphan*/  MT_RXWI_CTL_MPDU_LEN ; 
 int RX_FLAG_DECRYPTED ; 
 int RX_FLAG_IV_STRIPPED ; 
 int RX_FLAG_MMIC_STRIPPED ; 
 scalar_t__ WARN_ON (int) ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_mac_process_rate (struct ieee80211_rx_status*,int /*<<< orphan*/ ) ; 
 int mt76x0_phy_get_rssi (struct mt76x0_dev*,struct mt76x0_rxwi*) ; 
 scalar_t__ mt76x0_rx_is_our_beacon (struct mt76x0_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x0_rx_monitor_beacon (struct mt76x0_dev*,struct mt76x0_rxwi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

u32 mt76x0_mac_process_rx(struct mt76x0_dev *dev, struct sk_buff *skb,
			u8 *data, void *rxi)
{
	struct ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	struct mt76x0_rxwi *rxwi = rxi;
	u32 len, ctl = le32_to_cpu(rxwi->ctl);
	u16 rate = le16_to_cpu(rxwi->rate);
	int rssi;

	len = FIELD_GET(MT_RXWI_CTL_MPDU_LEN, ctl);
	if (WARN_ON(len < 10))
		return 0;

	if (rxwi->rxinfo & cpu_to_le32(MT_RXINFO_DECRYPT)) {
		status->flag |= RX_FLAG_DECRYPTED;
		status->flag |= RX_FLAG_IV_STRIPPED | RX_FLAG_MMIC_STRIPPED;
	}

	status->chains = BIT(0);
	rssi = mt76x0_phy_get_rssi(dev, rxwi);
	status->chain_signal[0] = status->signal = rssi;
	status->freq = dev->mt76.chandef.chan->center_freq;
	status->band = dev->mt76.chandef.chan->band;

	mt76_mac_process_rate(status, rate);

	spin_lock_bh(&dev->con_mon_lock);
	if (mt76x0_rx_is_our_beacon(dev, data)) {
		mt76x0_rx_monitor_beacon(dev, rxwi, rate, rssi);
	} else if (rxwi->rxinfo & cpu_to_le32(MT_RXINFO_U2M)) {
		if (dev->avg_rssi == 0)
			dev->avg_rssi = rssi;
		else
			dev->avg_rssi = (dev->avg_rssi * 15) / 16 + rssi / 16;

	}
	spin_unlock_bh(&dev->con_mon_lock);

	return len;
}