#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  mark; TYPE_1__* dev; } ;
struct net {int dummy; } ;
struct iphdr {int /*<<< orphan*/  protocol; int /*<<< orphan*/  tos; } ;
struct flowi4 {int dummy; } ;
struct TYPE_2__ {int ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __build_flow_key (struct net const*,struct flowi4*,struct sock const*,struct iphdr const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* dev_net (TYPE_1__*) ; 
 struct iphdr* ip_hdr (struct sk_buff const*) ; 

__attribute__((used)) static void build_skb_flow_key(struct flowi4 *fl4, const struct sk_buff *skb,
			       const struct sock *sk)
{
	const struct net *net = dev_net(skb->dev);
	const struct iphdr *iph = ip_hdr(skb);
	int oif = skb->dev->ifindex;
	u8 tos = RT_TOS(iph->tos);
	u8 prot = iph->protocol;
	u32 mark = skb->mark;

	__build_flow_key(net, fl4, sk, iph, oif, tos, prot, mark, 0);
}