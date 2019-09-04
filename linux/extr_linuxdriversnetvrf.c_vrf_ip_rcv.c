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
struct sk_buff {scalar_t__ pkt_type; int /*<<< orphan*/  mac_len; int /*<<< orphan*/  len; int /*<<< orphan*/  skb_iif; struct net_device* dev; } ;
struct net_device {int /*<<< orphan*/  ptype_all; int /*<<< orphan*/  ifindex; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 TYPE_2__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IPSKB_L3SLAVE ; 
 int /*<<< orphan*/  NFPROTO_IPV4 ; 
 int /*<<< orphan*/  NF_INET_PRE_ROUTING ; 
 scalar_t__ PACKET_HOST ; 
 scalar_t__ PACKET_LOOPBACK ; 
 int /*<<< orphan*/  dev_queue_xmit_nit (struct sk_buff*,struct net_device*) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 scalar_t__ ipv4_is_multicast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* vrf_rcv_nfhook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  vrf_rx_stats (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *vrf_ip_rcv(struct net_device *vrf_dev,
				  struct sk_buff *skb)
{
	skb->dev = vrf_dev;
	skb->skb_iif = vrf_dev->ifindex;
	IPCB(skb)->flags |= IPSKB_L3SLAVE;

	if (ipv4_is_multicast(ip_hdr(skb)->daddr))
		goto out;

	/* loopback traffic; do not push through packet taps again.
	 * Reset pkt_type for upper layers to process skb
	 */
	if (skb->pkt_type == PACKET_LOOPBACK) {
		skb->pkt_type = PACKET_HOST;
		goto out;
	}

	vrf_rx_stats(vrf_dev, skb->len);

	if (!list_empty(&vrf_dev->ptype_all)) {
		skb_push(skb, skb->mac_len);
		dev_queue_xmit_nit(skb, vrf_dev);
		skb_pull(skb, skb->mac_len);
	}

	skb = vrf_rcv_nfhook(NFPROTO_IPV4, NF_INET_PRE_ROUTING, skb, vrf_dev);
out:
	return skb;
}