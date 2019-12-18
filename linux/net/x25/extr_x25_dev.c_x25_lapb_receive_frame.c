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
struct x25_neigh {int dummy; } ;
struct sk_buff {int* data; } ;
struct packet_type {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  X25_IFACE_CONNECT 130 
#define  X25_IFACE_DATA 129 
#define  X25_IFACE_DISCONNECT 128 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 struct x25_neigh* x25_get_neigh (struct net_device*) ; 
 int /*<<< orphan*/  x25_link_established (struct x25_neigh*) ; 
 int /*<<< orphan*/  x25_link_terminated (struct x25_neigh*) ; 
 int /*<<< orphan*/  x25_neigh_put (struct x25_neigh*) ; 
 int /*<<< orphan*/  x25_receive_data (struct sk_buff*,struct x25_neigh*) ; 

int x25_lapb_receive_frame(struct sk_buff *skb, struct net_device *dev,
			   struct packet_type *ptype, struct net_device *orig_dev)
{
	struct sk_buff *nskb;
	struct x25_neigh *nb;

	if (!net_eq(dev_net(dev), &init_net))
		goto drop;

	nskb = skb_copy(skb, GFP_ATOMIC);
	if (!nskb)
		goto drop;
	kfree_skb(skb);
	skb = nskb;

	/*
	 * Packet received from unrecognised device, throw it away.
	 */
	nb = x25_get_neigh(dev);
	if (!nb) {
		pr_debug("unknown neighbour - %s\n", dev->name);
		goto drop;
	}

	if (!pskb_may_pull(skb, 1))
		return 0;

	switch (skb->data[0]) {

	case X25_IFACE_DATA:
		skb_pull(skb, 1);
		if (x25_receive_data(skb, nb)) {
			x25_neigh_put(nb);
			goto out;
		}
		break;

	case X25_IFACE_CONNECT:
		x25_link_established(nb);
		break;

	case X25_IFACE_DISCONNECT:
		x25_link_terminated(nb);
		break;
	}
	x25_neigh_put(nb);
drop:
	kfree_skb(skb);
out:
	return 0;
}