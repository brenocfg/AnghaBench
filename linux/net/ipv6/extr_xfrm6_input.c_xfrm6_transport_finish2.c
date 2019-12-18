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
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ip6_rcv_finish ; 
 scalar_t__ xfrm_trans_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xfrm6_transport_finish2(struct net *net, struct sock *sk,
				   struct sk_buff *skb)
{
	if (xfrm_trans_queue(skb, ip6_rcv_finish))
		__kfree_skb(skb);
	return -1;
}