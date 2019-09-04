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
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct rtable {TYPE_1__ dst; } ;
struct net {int dummy; } ;
struct iphdr {int /*<<< orphan*/  tos; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct flowi4 {int flowi4_oif; int /*<<< orphan*/  flowi4_flags; int /*<<< orphan*/  flowi4_scope; int /*<<< orphan*/  flowi4_tos; int /*<<< orphan*/  daddr; } ;
typedef  int /*<<< orphan*/  fl4 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  FLOWI_FLAG_KNOWN_NH ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 int /*<<< orphan*/  RT_TOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 struct rtable* ip_route_output_key (struct net*,struct flowi4*) ; 
 int /*<<< orphan*/  memset (struct flowi4*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,TYPE_1__*) ; 

__attribute__((used)) static bool nf_dup_ipv4_route(struct net *net, struct sk_buff *skb,
			      const struct in_addr *gw, int oif)
{
	const struct iphdr *iph = ip_hdr(skb);
	struct rtable *rt;
	struct flowi4 fl4;

	memset(&fl4, 0, sizeof(fl4));
	if (oif != -1)
		fl4.flowi4_oif = oif;

	fl4.daddr = gw->s_addr;
	fl4.flowi4_tos = RT_TOS(iph->tos);
	fl4.flowi4_scope = RT_SCOPE_UNIVERSE;
	fl4.flowi4_flags = FLOWI_FLAG_KNOWN_NH;
	rt = ip_route_output_key(net, &fl4);
	if (IS_ERR(rt))
		return false;

	skb_dst_drop(skb);
	skb_dst_set(skb, &rt->dst);
	skb->dev      = rt->dst.dev;
	skb->protocol = htons(ETH_P_IP);

	return true;
}