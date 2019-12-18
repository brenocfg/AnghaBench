#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int ipvs_property; } ;
struct ip_vs_protocol {scalar_t__ snat_handler; } ;
struct ip_vs_proto_data {struct ip_vs_protocol* pp; } ;
struct ip_vs_iphdr {int /*<<< orphan*/  off; int /*<<< orphan*/  len; } ;
struct TYPE_5__ {int /*<<< orphan*/  ip; int /*<<< orphan*/  in6; } ;
struct ip_vs_conn {int flags; int /*<<< orphan*/  ipvs; TYPE_1__ vaddr; } ;
struct TYPE_7__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_6__ {int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int AF_INET6 ; 
 int IP_VS_CONN_F_NFCT ; 
 int /*<<< orphan*/  IP_VS_DBG_PKT (int,int,struct ip_vs_protocol*,struct sk_buff*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IP_VS_DIR_OUTPUT ; 
 int /*<<< orphan*/  LeaveFunction (int) ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_STOLEN ; 
 int /*<<< orphan*/  SNAT_CALL (scalar_t__,struct sk_buff*,struct ip_vs_protocol*,struct ip_vs_conn*,struct ip_vs_iphdr*) ; 
 TYPE_3__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_send_check (TYPE_3__*) ; 
 int /*<<< orphan*/  ip_vs_conn_put (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  ip_vs_notrack (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_vs_out_stats (struct ip_vs_conn*,struct sk_buff*) ; 
 scalar_t__ ip_vs_route_me_harder (int /*<<< orphan*/ ,int,struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  ip_vs_set_state (struct ip_vs_conn*,int /*<<< orphan*/ ,struct sk_buff*,struct ip_vs_proto_data*) ; 
 int /*<<< orphan*/  ip_vs_update_conntrack (struct sk_buff*,struct ip_vs_conn*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
handle_response(int af, struct sk_buff *skb, struct ip_vs_proto_data *pd,
		struct ip_vs_conn *cp, struct ip_vs_iphdr *iph,
		unsigned int hooknum)
{
	struct ip_vs_protocol *pp = pd->pp;

	IP_VS_DBG_PKT(11, af, pp, skb, iph->off, "Outgoing packet");

	if (skb_ensure_writable(skb, iph->len))
		goto drop;

	/* mangle the packet */
	if (pp->snat_handler &&
	    !SNAT_CALL(pp->snat_handler, skb, pp, cp, iph))
		goto drop;

#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		ipv6_hdr(skb)->saddr = cp->vaddr.in6;
	else
#endif
	{
		ip_hdr(skb)->saddr = cp->vaddr.ip;
		ip_send_check(ip_hdr(skb));
	}

	/*
	 * nf_iterate does not expect change in the skb->dst->dev.
	 * It looks like it is not fatal to enable this code for hooks
	 * where our handlers are at the end of the chain list and
	 * when all next handlers use skb->dst->dev and not outdev.
	 * It will definitely route properly the inout NAT traffic
	 * when multiple paths are used.
	 */

	/* For policy routing, packets originating from this
	 * machine itself may be routed differently to packets
	 * passing through.  We want this packet to be routed as
	 * if it came from this machine itself.  So re-compute
	 * the routing information.
	 */
	if (ip_vs_route_me_harder(cp->ipvs, af, skb, hooknum))
		goto drop;

	IP_VS_DBG_PKT(10, af, pp, skb, iph->off, "After SNAT");

	ip_vs_out_stats(cp, skb);
	ip_vs_set_state(cp, IP_VS_DIR_OUTPUT, skb, pd);
	skb->ipvs_property = 1;
	if (!(cp->flags & IP_VS_CONN_F_NFCT))
		ip_vs_notrack(skb);
	else
		ip_vs_update_conntrack(skb, cp, 0);
	ip_vs_conn_put(cp);

	LeaveFunction(11);
	return NF_ACCEPT;

drop:
	ip_vs_conn_put(cp);
	kfree_skb(skb);
	LeaveFunction(11);
	return NF_STOLEN;
}