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
struct sk_buff {scalar_t__ data; } ;
struct rtable {int dummy; } ;
struct net {int dummy; } ;
struct iphdr {int dummy; } ;
struct flowi4 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct rtable*) ; 
 int /*<<< orphan*/  __build_flow_key (struct net*,struct flowi4*,struct sock*,struct iphdr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ip_do_redirect (struct rtable*,struct sk_buff*,struct flowi4*,int) ; 
 struct rtable* __ip_route_output_key (struct net*,struct flowi4*) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 struct net* sock_net (struct sock*) ; 

void ipv4_sk_redirect(struct sk_buff *skb, struct sock *sk)
{
	const struct iphdr *iph = (const struct iphdr *) skb->data;
	struct flowi4 fl4;
	struct rtable *rt;
	struct net *net = sock_net(sk);

	__build_flow_key(net, &fl4, sk, iph, 0, 0, 0, 0, 0);
	rt = __ip_route_output_key(net, &fl4);
	if (!IS_ERR(rt)) {
		__ip_do_redirect(rt, skb, &fl4, false);
		ip_rt_put(rt);
	}
}