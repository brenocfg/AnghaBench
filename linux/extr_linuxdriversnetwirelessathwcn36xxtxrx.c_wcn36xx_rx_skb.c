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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ mpdu_header_off; scalar_t__ mpdu_len; } ;
struct wcn36xx_rx_bd {TYPE_1__ pdu; } ;
struct wcn36xx {int /*<<< orphan*/  hw; int /*<<< orphan*/  scan_band; scalar_t__ scan_freq; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct ieee80211_rx_status {int mactime; int antenna; int rate_idx; int flag; scalar_t__ rx_flags; int /*<<< orphan*/  signal; int /*<<< orphan*/  band; scalar_t__ freq; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/  seq_ctrl; } ;
typedef  int /*<<< orphan*/  status ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_SEQ_TO_SN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int RX_FLAG_DECRYPTED ; 
 int RX_FLAG_IV_STRIPPED ; 
 int RX_FLAG_MMIC_STRIPPED ; 
 int /*<<< orphan*/  WCN36XX_BAND (struct wcn36xx*) ; 
 scalar_t__ WCN36XX_CENTER_FREQ (struct wcn36xx*) ; 
 int /*<<< orphan*/  WCN36XX_DBG_BEACON ; 
 int /*<<< orphan*/  WCN36XX_DBG_BEACON_DUMP ; 
 int /*<<< orphan*/  WCN36XX_DBG_RX ; 
 int /*<<< orphan*/  WCN36XX_DBG_RX_DUMP ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buff_to_be (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_rssi0 (struct wcn36xx_rx_bd*) ; 
 scalar_t__ ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_rx_irqsafe (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ieee80211_rx_status*,int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_rx_status*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wcn36xx_dbg_dump (int /*<<< orphan*/ ,char*,char*,int) ; 

int wcn36xx_rx_skb(struct wcn36xx *wcn, struct sk_buff *skb)
{
	struct ieee80211_rx_status status;
	struct ieee80211_hdr *hdr;
	struct wcn36xx_rx_bd *bd;
	u16 fc, sn;

	/*
	 * All fields must be 0, otherwise it can lead to
	 * unexpected consequences.
	 */
	memset(&status, 0, sizeof(status));

	bd = (struct wcn36xx_rx_bd *)skb->data;
	buff_to_be((u32 *)bd, sizeof(*bd)/sizeof(u32));
	wcn36xx_dbg_dump(WCN36XX_DBG_RX_DUMP,
			 "BD   <<< ", (char *)bd,
			 sizeof(struct wcn36xx_rx_bd));

	skb_put(skb, bd->pdu.mpdu_header_off + bd->pdu.mpdu_len);
	skb_pull(skb, bd->pdu.mpdu_header_off);

	hdr = (struct ieee80211_hdr *) skb->data;
	fc = __le16_to_cpu(hdr->frame_control);
	sn = IEEE80211_SEQ_TO_SN(__le16_to_cpu(hdr->seq_ctrl));

	/* When scanning associate beacons to this */
	if (ieee80211_is_beacon(hdr->frame_control) && wcn->scan_freq) {
		status.freq = wcn->scan_freq;
		status.band = wcn->scan_band;
	} else {
		status.freq = WCN36XX_CENTER_FREQ(wcn);
		status.band = WCN36XX_BAND(wcn);
	}

	status.mactime = 10;
	status.signal = -get_rssi0(bd);
	status.antenna = 1;
	status.rate_idx = 1;
	status.flag = 0;
	status.rx_flags = 0;
	status.flag |= RX_FLAG_IV_STRIPPED |
		       RX_FLAG_MMIC_STRIPPED |
		       RX_FLAG_DECRYPTED;

	wcn36xx_dbg(WCN36XX_DBG_RX, "status.flags=%x\n", status.flag);

	memcpy(IEEE80211_SKB_RXCB(skb), &status, sizeof(status));

	if (ieee80211_is_beacon(hdr->frame_control)) {
		wcn36xx_dbg(WCN36XX_DBG_BEACON, "beacon skb %p len %d fc %04x sn %d\n",
			    skb, skb->len, fc, sn);
		wcn36xx_dbg_dump(WCN36XX_DBG_BEACON_DUMP, "SKB <<< ",
				 (char *)skb->data, skb->len);
	} else {
		wcn36xx_dbg(WCN36XX_DBG_RX, "rx skb %p len %d fc %04x sn %d\n",
			    skb, skb->len, fc, sn);
		wcn36xx_dbg_dump(WCN36XX_DBG_RX_DUMP, "SKB <<< ",
				 (char *)skb->data, skb->len);
	}

	ieee80211_rx_irqsafe(wcn->hw, skb);

	return 0;
}