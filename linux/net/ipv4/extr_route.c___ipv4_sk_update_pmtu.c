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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  mark; scalar_t__ data; } ;
struct rtable {int dummy; } ;
struct iphdr {int dummy; } ;
struct flowi4 {scalar_t__ flowi4_mark; } ;

/* Variables and functions */
 scalar_t__ IP4_REPLY_MARK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct rtable*) ; 
 int /*<<< orphan*/  __build_flow_key (int /*<<< orphan*/ ,struct flowi4*,struct sock*,struct iphdr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtable* __ip_route_output_key (int /*<<< orphan*/ ,struct flowi4*) ; 
 int /*<<< orphan*/  __ip_rt_update_pmtu (struct rtable*,struct flowi4*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static void __ipv4_sk_update_pmtu(struct sk_buff *skb, struct sock *sk, u32 mtu)
{
	const struct iphdr *iph = (const struct iphdr *) skb->data;
	struct flowi4 fl4;
	struct rtable *rt;

	__build_flow_key(sock_net(sk), &fl4, sk, iph, 0, 0, 0, 0, 0);

	if (!fl4.flowi4_mark)
		fl4.flowi4_mark = IP4_REPLY_MARK(sock_net(sk), skb->mark);

	rt = __ip_route_output_key(sock_net(sk), &fl4);
	if (!IS_ERR(rt)) {
		__ip_rt_update_pmtu(rt, &fl4, mtu);
		ip_rt_put(rt);
	}
}