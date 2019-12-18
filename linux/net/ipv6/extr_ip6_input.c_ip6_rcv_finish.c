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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int NET_RX_SUCCESS ; 
 int dst_input (struct sk_buff*) ; 
 int /*<<< orphan*/  ip6_rcv_finish_core (struct net*,struct sock*,struct sk_buff*) ; 
 struct sk_buff* l3mdev_ip6_rcv (struct sk_buff*) ; 

int ip6_rcv_finish(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	/* if ingress device is enslaved to an L3 master device pass the
	 * skb to its handler for processing
	 */
	skb = l3mdev_ip6_rcv(skb);
	if (!skb)
		return NET_RX_SUCCESS;
	ip6_rcv_finish_core(net, sk, skb);

	return dst_input(skb);
}