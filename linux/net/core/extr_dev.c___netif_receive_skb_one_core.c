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
struct sk_buff {struct net_device* dev; } ;
struct packet_type {int /*<<< orphan*/  func; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int INDIRECT_CALL_INET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,struct net_device*,struct packet_type*,struct net_device*) ; 
 int __netif_receive_skb_core (struct sk_buff*,int,struct packet_type**) ; 
 int /*<<< orphan*/  ip_rcv ; 
 int /*<<< orphan*/  ipv6_rcv ; 

__attribute__((used)) static int __netif_receive_skb_one_core(struct sk_buff *skb, bool pfmemalloc)
{
	struct net_device *orig_dev = skb->dev;
	struct packet_type *pt_prev = NULL;
	int ret;

	ret = __netif_receive_skb_core(skb, pfmemalloc, &pt_prev);
	if (pt_prev)
		ret = INDIRECT_CALL_INET(pt_prev->func, ipv6_rcv, ip_rcv, skb,
					 skb->dev, pt_prev, orig_dev);
	return ret;
}