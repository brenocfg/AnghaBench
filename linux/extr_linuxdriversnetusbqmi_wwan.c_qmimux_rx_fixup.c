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
typedef  unsigned int u8 ;
struct usbnet {int dummy; } ;
struct sk_buff {unsigned int len; int* data; void* protocol; struct net_device* dev; } ;
struct qmimux_hdr {int pad; int /*<<< orphan*/  mux_id; int /*<<< orphan*/  pkt_len; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ NET_RX_SUCCESS ; 
 unsigned int be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,unsigned int) ; 
 scalar_t__ netif_rx (struct sk_buff*) ; 
 struct net_device* qmimux_find_dev (struct usbnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int*,unsigned int) ; 

__attribute__((used)) static int qmimux_rx_fixup(struct usbnet *dev, struct sk_buff *skb)
{
	unsigned int len, offset = 0;
	struct qmimux_hdr *hdr;
	struct net_device *net;
	struct sk_buff *skbn;
	u8 qmimux_hdr_sz = sizeof(*hdr);

	while (offset + qmimux_hdr_sz < skb->len) {
		hdr = (struct qmimux_hdr *)(skb->data + offset);
		len = be16_to_cpu(hdr->pkt_len);

		/* drop the packet, bogus length */
		if (offset + len + qmimux_hdr_sz > skb->len)
			return 0;

		/* control packet, we do not know what to do */
		if (hdr->pad & 0x80)
			goto skip;

		net = qmimux_find_dev(dev, hdr->mux_id);
		if (!net)
			goto skip;
		skbn = netdev_alloc_skb(net, len);
		if (!skbn)
			return 0;
		skbn->dev = net;

		switch (skb->data[offset + qmimux_hdr_sz] & 0xf0) {
		case 0x40:
			skbn->protocol = htons(ETH_P_IP);
			break;
		case 0x60:
			skbn->protocol = htons(ETH_P_IPV6);
			break;
		default:
			/* not ip - do not know what to do */
			goto skip;
		}

		skb_put_data(skbn, skb->data + offset + qmimux_hdr_sz, len);
		if (netif_rx(skbn) != NET_RX_SUCCESS)
			return 0;

skip:
		offset += len + qmimux_hdr_sz;
	}
	return 1;
}