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
struct sk_buff {int /*<<< orphan*/  cb; int /*<<< orphan*/  protocol; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  dev; scalar_t__ data; } ;
struct rtl_80211_hdr_4addr {int /*<<< orphan*/  frame_ctl; } ;
struct ieee80211_rx_stats {int dummy; } ;
struct ieee80211_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_80211_RAW ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_get_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static inline void ieee80211_monitor_rx(struct ieee80211_device *ieee,
					struct sk_buff *skb,
					struct ieee80211_rx_stats *rx_stats)
{
	struct rtl_80211_hdr_4addr *hdr = (struct rtl_80211_hdr_4addr *)skb->data;
	u16 fc = le16_to_cpu(hdr->frame_ctl);

	skb->dev = ieee->dev;
	skb_reset_mac_header(skb);

	skb_pull(skb, ieee80211_get_hdrlen(fc));
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = htons(ETH_P_80211_RAW);
	memset(skb->cb, 0, sizeof(skb->cb));
	netif_rx(skb);
}