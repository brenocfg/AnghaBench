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
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 scalar_t__ CTINFO2DIR (int) ; 
 scalar_t__ IP_CT_DIR_ORIGINAL ; 
 int IP_CT_RELATED ; 
 int IP_CT_RELATED_REPLY ; 
 int /*<<< orphan*/  nf_conntrack_get (int /*<<< orphan*/ ) ; 
 struct nf_conn* nf_ct_get (struct sk_buff const*,int*) ; 
 int /*<<< orphan*/  nf_ct_set (struct sk_buff*,struct nf_conn*,int) ; 
 int /*<<< orphan*/  skb_nfct (struct sk_buff*) ; 

__attribute__((used)) static void nf_conntrack_attach(struct sk_buff *nskb, const struct sk_buff *skb)
{
	struct nf_conn *ct;
	enum ip_conntrack_info ctinfo;

	/* This ICMP is in reverse direction to the packet which caused it */
	ct = nf_ct_get(skb, &ctinfo);
	if (CTINFO2DIR(ctinfo) == IP_CT_DIR_ORIGINAL)
		ctinfo = IP_CT_RELATED_REPLY;
	else
		ctinfo = IP_CT_RELATED;

	/* Attach to new skbuff, and increment count */
	nf_ct_set(nskb, ct, ctinfo);
	nf_conntrack_get(skb_nfct(nskb));
}