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
struct sk_buff {int dummy; } ;
struct nft_regs {int dummy; } ;
struct nft_pktinfo {struct sk_buff* skb; } ;
struct nft_expr {int dummy; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int IP_CT_UNTRACKED ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  nf_ct_set (struct sk_buff*,struct nf_conn*,int) ; 

__attribute__((used)) static void nft_notrack_eval(const struct nft_expr *expr,
			     struct nft_regs *regs,
			     const struct nft_pktinfo *pkt)
{
	struct sk_buff *skb = pkt->skb;
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct;

	ct = nf_ct_get(pkt->skb, &ctinfo);
	/* Previously seen (loopback or untracked)?  Ignore. */
	if (ct || ctinfo == IP_CT_UNTRACKED)
		return;

	nf_ct_set(skb, ct, IP_CT_UNTRACKED);
}