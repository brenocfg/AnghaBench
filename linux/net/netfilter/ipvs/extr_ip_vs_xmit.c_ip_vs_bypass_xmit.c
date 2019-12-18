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
struct sk_buff {int ignore_df; } ;
struct iphdr {int /*<<< orphan*/  daddr; } ;
struct ip_vs_protocol {int dummy; } ;
struct ip_vs_iphdr {int dummy; } ;
struct ip_vs_conn {int /*<<< orphan*/  af; int /*<<< orphan*/  ipvs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EnterFunction (int) ; 
 int /*<<< orphan*/  IP_VS_RT_MODE_NON_LOCAL ; 
 int /*<<< orphan*/  LeaveFunction (int) ; 
 int /*<<< orphan*/  NFPROTO_IPV4 ; 
 int NF_STOLEN ; 
 scalar_t__ __ip_vs_get_out_rt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ip_vs_iphdr*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_send_check (struct iphdr*) ; 
 int /*<<< orphan*/  ip_vs_send_or_cont (int /*<<< orphan*/ ,struct sk_buff*,struct ip_vs_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

int
ip_vs_bypass_xmit(struct sk_buff *skb, struct ip_vs_conn *cp,
		  struct ip_vs_protocol *pp, struct ip_vs_iphdr *ipvsh)
{
	struct iphdr  *iph = ip_hdr(skb);

	EnterFunction(10);

	if (__ip_vs_get_out_rt(cp->ipvs, cp->af, skb, NULL, iph->daddr,
			       IP_VS_RT_MODE_NON_LOCAL, NULL, ipvsh) < 0)
		goto tx_error;

	ip_send_check(iph);

	/* Another hack: avoid icmp_send in ip_fragment */
	skb->ignore_df = 1;

	ip_vs_send_or_cont(NFPROTO_IPV4, skb, cp, 0);

	LeaveFunction(10);
	return NF_STOLEN;

 tx_error:
	kfree_skb(skb);
	LeaveFunction(10);
	return NF_STOLEN;
}