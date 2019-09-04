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
struct nf_hook_state {int dummy; } ;
struct nf_conntrack_helper {unsigned int (* help ) (struct sk_buff*,scalar_t__,struct nf_conn*,int) ;} ;
struct nf_conn_help {int /*<<< orphan*/  helper; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int IP_CT_RELATED_REPLY ; 
 unsigned int NF_ACCEPT ; 
 scalar_t__ ip_hdrlen (struct sk_buff*) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 struct nf_conn_help* nfct_help (struct nf_conn*) ; 
 struct nf_conntrack_helper* rcu_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_network_offset (struct sk_buff*) ; 
 unsigned int stub1 (struct sk_buff*,scalar_t__,struct nf_conn*,int) ; 

__attribute__((used)) static unsigned int ipv4_helper(void *priv,
				struct sk_buff *skb,
				const struct nf_hook_state *state)
{
	struct nf_conn *ct;
	enum ip_conntrack_info ctinfo;
	const struct nf_conn_help *help;
	const struct nf_conntrack_helper *helper;

	/* This is where we call the helper: as the packet goes out. */
	ct = nf_ct_get(skb, &ctinfo);
	if (!ct || ctinfo == IP_CT_RELATED_REPLY)
		return NF_ACCEPT;

	help = nfct_help(ct);
	if (!help)
		return NF_ACCEPT;

	/* rcu_read_lock()ed by nf_hook_thresh */
	helper = rcu_dereference(help->helper);
	if (!helper)
		return NF_ACCEPT;

	return helper->help(skb, skb_network_offset(skb) + ip_hdrlen(skb),
			    ct, ctinfo);
}