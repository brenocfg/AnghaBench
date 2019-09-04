#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u16 ;
struct sk_buff {int* data; int len; int /*<<< orphan*/  ip_summed; TYPE_2__* dev; int /*<<< orphan*/  protocol; int /*<<< orphan*/  cb; } ;
struct rtllib_rxb {size_t nr_subframes; int* src; int* dst; struct sk_buff** subframes; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct rtllib_device {int /*<<< orphan*/  last_rx_ps_time; TYPE_2__* dev; struct net_device_stats stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int ETH_ALEN ; 
 int ETH_P_AARP ; 
 int ETH_P_IPX ; 
 int /*<<< orphan*/  SNAP_SIZE ; 
 int /*<<< orphan*/  bridge_tunnel_header ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,TYPE_2__*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct rtllib_rxb*) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  rfc1042_header ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

void rtllib_indicate_packets(struct rtllib_device *ieee,
			     struct rtllib_rxb **prxbIndicateArray, u8 index)
{
	struct net_device_stats *stats = &ieee->stats;
	u8 i = 0, j = 0;
	u16 ethertype;

	for (j = 0; j < index; j++) {
		struct rtllib_rxb *prxb = prxbIndicateArray[j];

		for (i = 0; i < prxb->nr_subframes; i++) {
			struct sk_buff *sub_skb = prxb->subframes[i];

		/* convert hdr + possible LLC headers into Ethernet header */
			ethertype = (sub_skb->data[6] << 8) | sub_skb->data[7];
			if (sub_skb->len >= 8 &&
			    ((memcmp(sub_skb->data, rfc1042_header,
				     SNAP_SIZE) == 0 &&
			      ethertype != ETH_P_AARP &&
			      ethertype != ETH_P_IPX) ||
			    memcmp(sub_skb->data, bridge_tunnel_header,
				   SNAP_SIZE) == 0)) {
				/* remove RFC1042 or Bridge-Tunnel encapsulation
				 * and replace EtherType
				 */
				skb_pull(sub_skb, SNAP_SIZE);
				memcpy(skb_push(sub_skb, ETH_ALEN), prxb->src, ETH_ALEN);
				memcpy(skb_push(sub_skb, ETH_ALEN), prxb->dst, ETH_ALEN);
			} else {
				u16 len;
			/* Leave Ethernet header part of hdr and full payload */
				len = sub_skb->len;
				memcpy(skb_push(sub_skb, 2), &len, 2);
				memcpy(skb_push(sub_skb, ETH_ALEN), prxb->src, ETH_ALEN);
				memcpy(skb_push(sub_skb, ETH_ALEN), prxb->dst, ETH_ALEN);
			}

			/* Indicate the packets to upper layer */
			if (sub_skb) {
				stats->rx_packets++;
				stats->rx_bytes += sub_skb->len;

				memset(sub_skb->cb, 0, sizeof(sub_skb->cb));
				sub_skb->protocol = eth_type_trans(sub_skb,
								   ieee->dev);
				sub_skb->dev = ieee->dev;
				sub_skb->dev->stats.rx_packets++;
				sub_skb->dev->stats.rx_bytes += sub_skb->len;
				/* 802.11 crc not sufficient */
				sub_skb->ip_summed = CHECKSUM_NONE;
				ieee->last_rx_ps_time = jiffies;
				netif_rx(sub_skb);
			}
		}
		kfree(prxb);
		prxb = NULL;
	}
}