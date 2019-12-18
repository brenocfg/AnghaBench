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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int len; scalar_t__ pkt_type; int /*<<< orphan*/  protocol; struct net_device* dev; scalar_t__ priority; } ;
struct phonethdr {void* pn_sobj; void* pn_robj; int /*<<< orphan*/  pn_length; scalar_t__ pn_res; void* pn_sdev; void* pn_rdev; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_P_PHONET ; 
 scalar_t__ PACKET_LOOPBACK ; 
 scalar_t__ PNADDR_BROADCAST ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __cpu_to_be16 (int) ; 
 int dev_hard_header (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int net_xmit_errno (int) ; 
 scalar_t__ netif_rx (struct sk_buff*) ; 
 scalar_t__ netif_rx_ni (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ pn_addr (int /*<<< orphan*/ ) ; 
 void* pn_dev (int /*<<< orphan*/ ) ; 
 struct phonethdr* pn_hdr (struct sk_buff*) ; 
 void* pn_obj (int /*<<< orphan*/ ) ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pn_send(struct sk_buff *skb, struct net_device *dev,
			u16 dst, u16 src, u8 res, u8 irq)
{
	struct phonethdr *ph;
	int err;

	if (skb->len + 2 > 0xffff /* Phonet length field limit */ ||
	    skb->len + sizeof(struct phonethdr) > dev->mtu) {
		err = -EMSGSIZE;
		goto drop;
	}

	/* Broadcast sending is not implemented */
	if (pn_addr(dst) == PNADDR_BROADCAST) {
		err = -EOPNOTSUPP;
		goto drop;
	}

	skb_reset_transport_header(skb);
	WARN_ON(skb_headroom(skb) & 1); /* HW assumes word alignment */
	skb_push(skb, sizeof(struct phonethdr));
	skb_reset_network_header(skb);
	ph = pn_hdr(skb);
	ph->pn_rdev = pn_dev(dst);
	ph->pn_sdev = pn_dev(src);
	ph->pn_res = res;
	ph->pn_length = __cpu_to_be16(skb->len + 2 - sizeof(*ph));
	ph->pn_robj = pn_obj(dst);
	ph->pn_sobj = pn_obj(src);

	skb->protocol = htons(ETH_P_PHONET);
	skb->priority = 0;
	skb->dev = dev;

	if (skb->pkt_type == PACKET_LOOPBACK) {
		skb_reset_mac_header(skb);
		skb_orphan(skb);
		err = (irq ? netif_rx(skb) : netif_rx_ni(skb)) ? -ENOBUFS : 0;
	} else {
		err = dev_hard_header(skb, dev, ntohs(skb->protocol),
					NULL, NULL, skb->len);
		if (err < 0) {
			err = -EHOSTUNREACH;
			goto drop;
		}
		err = dev_queue_xmit(skb);
		if (unlikely(err > 0))
			err = net_xmit_errno(err);
	}

	return err;
drop:
	kfree_skb(skb);
	return err;
}