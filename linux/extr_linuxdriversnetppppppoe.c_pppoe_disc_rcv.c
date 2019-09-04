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
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  padt_work; } ;
struct TYPE_5__ {TYPE_1__ pppoe; } ;
struct pppox_sock {TYPE_2__ proto; } ;
struct pppoe_net {int dummy; } ;
struct pppoe_hdr {scalar_t__ code; int /*<<< orphan*/  sid; } ;
struct packet_type {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct TYPE_6__ {int /*<<< orphan*/  h_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NET_RX_SUCCESS ; 
 scalar_t__ PADT_CODE ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 TYPE_3__* eth_hdr (struct sk_buff*) ; 
 struct pppox_sock* get_item (struct pppoe_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct pppoe_hdr* pppoe_hdr (struct sk_buff*) ; 
 struct pppoe_net* pppoe_pernet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_pppox (struct pppox_sock*) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pppoe_disc_rcv(struct sk_buff *skb, struct net_device *dev,
			  struct packet_type *pt, struct net_device *orig_dev)

{
	struct pppoe_hdr *ph;
	struct pppox_sock *po;
	struct pppoe_net *pn;

	skb = skb_share_check(skb, GFP_ATOMIC);
	if (!skb)
		goto out;

	if (!pskb_may_pull(skb, sizeof(struct pppoe_hdr)))
		goto abort;

	ph = pppoe_hdr(skb);
	if (ph->code != PADT_CODE)
		goto abort;

	pn = pppoe_pernet(dev_net(dev));
	po = get_item(pn, ph->sid, eth_hdr(skb)->h_source, dev->ifindex);
	if (po)
		if (!schedule_work(&po->proto.pppoe.padt_work))
			sock_put(sk_pppox(po));

abort:
	kfree_skb(skb);
out:
	return NET_RX_SUCCESS; /* Lies... :-) */
}