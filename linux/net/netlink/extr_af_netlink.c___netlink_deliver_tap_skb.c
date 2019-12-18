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
struct sock {scalar_t__ sk_protocol; } ;
struct sk_buff {int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  protocol; struct net_device* dev; int /*<<< orphan*/  head; struct sock* sk; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PACKET_KERNEL ; 
 int /*<<< orphan*/  PACKET_USER ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ is_vmalloc_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int net_xmit_errno (int) ; 
 scalar_t__ netlink_is_kernel (struct sock*) ; 
 struct sk_buff* netlink_to_full_skb (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __netlink_deliver_tap_skb(struct sk_buff *skb,
				     struct net_device *dev)
{
	struct sk_buff *nskb;
	struct sock *sk = skb->sk;
	int ret = -ENOMEM;

	if (!net_eq(dev_net(dev), sock_net(sk)))
		return 0;

	dev_hold(dev);

	if (is_vmalloc_addr(skb->head))
		nskb = netlink_to_full_skb(skb, GFP_ATOMIC);
	else
		nskb = skb_clone(skb, GFP_ATOMIC);
	if (nskb) {
		nskb->dev = dev;
		nskb->protocol = htons((u16) sk->sk_protocol);
		nskb->pkt_type = netlink_is_kernel(sk) ?
				 PACKET_KERNEL : PACKET_USER;
		skb_reset_network_header(nskb);
		ret = dev_queue_xmit(nskb);
		if (unlikely(ret > 0))
			ret = net_xmit_errno(ret);
	}

	dev_put(dev);
	return ret;
}