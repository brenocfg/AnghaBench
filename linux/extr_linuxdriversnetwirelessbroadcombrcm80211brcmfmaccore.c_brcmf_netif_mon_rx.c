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
struct sk_buff {int len; int /*<<< orphan*/  protocol; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  dev; } ;
struct ieee80211_radiotap_header {int /*<<< orphan*/  it_len; } ;
struct brcmf_if {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_FEAT_MONITOR_FMT_RADIOTAP ; 
 int /*<<< orphan*/  ETH_P_802_2 ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 scalar_t__ brcmf_feat_is_enabled (struct brcmf_if*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_netif_rx (struct brcmf_if*,struct sk_buff*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee80211_radiotap_header*,int /*<<< orphan*/ ,int) ; 
 struct ieee80211_radiotap_header* skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

void brcmf_netif_mon_rx(struct brcmf_if *ifp, struct sk_buff *skb)
{
	if (brcmf_feat_is_enabled(ifp, BRCMF_FEAT_MONITOR_FMT_RADIOTAP)) {
		/* Do nothing */
	} else {
		struct ieee80211_radiotap_header *radiotap;

		/* TODO: use RX status to fill some radiotap data */
		radiotap = skb_push(skb, sizeof(*radiotap));
		memset(radiotap, 0, sizeof(*radiotap));
		radiotap->it_len = cpu_to_le16(sizeof(*radiotap));

		/* TODO: 4 bytes with receive status? */
		skb->len -= 4;
	}

	skb->dev = ifp->ndev;
	skb_reset_mac_header(skb);
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = htons(ETH_P_802_2);

	brcmf_netif_rx(ifp, skb);
}