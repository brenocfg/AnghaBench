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
struct wlandevice {scalar_t__ state; int /*<<< orphan*/  nsd_rxq; struct net_device* netdev; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  protocol; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  ip_summed; struct net_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {scalar_t__ type; TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  ETH_P_80211_RAW ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 scalar_t__ WLAN_DEVICE_OPEN ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx_ni (struct sk_buff*) ; 
 int /*<<< orphan*/  p80211_convert_to_ether (struct wlandevice*,struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static void p80211netdev_rx_bh(unsigned long arg)
{
	struct wlandevice *wlandev = (struct wlandevice *)arg;
	struct sk_buff *skb = NULL;
	struct net_device *dev = wlandev->netdev;

	/* Let's empty our our queue */
	while ((skb = skb_dequeue(&wlandev->nsd_rxq))) {
		if (wlandev->state == WLAN_DEVICE_OPEN) {
			if (dev->type != ARPHRD_ETHER) {
				/* RAW frame; we shouldn't convert it */
				/* XXX Append the Prism Header here instead. */

				/* set up various data fields */
				skb->dev = dev;
				skb_reset_mac_header(skb);
				skb->ip_summed = CHECKSUM_NONE;
				skb->pkt_type = PACKET_OTHERHOST;
				skb->protocol = htons(ETH_P_80211_RAW);

				dev->stats.rx_packets++;
				dev->stats.rx_bytes += skb->len;
				netif_rx_ni(skb);
				continue;
			} else {
				if (!p80211_convert_to_ether(wlandev, skb))
					continue;
			}
		}
		dev_kfree_skb(skb);
	}
}