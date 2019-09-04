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
struct sk_buff {int dummy; } ;
struct nf_hook_state {int /*<<< orphan*/  hook; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_2__ {scalar_t__ protocol; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_ICMP ; 
 int IP_CT_RELATED ; 
 int IP_CT_RELATED_REPLY ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  nf_nat_icmp_reply_translation (struct sk_buff*,struct nf_conn*,int,int /*<<< orphan*/ ) ; 
 unsigned int nf_nat_inet_fn (void*,struct sk_buff*,struct nf_hook_state const*) ; 

__attribute__((used)) static unsigned int
nf_nat_ipv4_fn(void *priv, struct sk_buff *skb,
	       const struct nf_hook_state *state)
{
	struct nf_conn *ct;
	enum ip_conntrack_info ctinfo;

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct)
		return NF_ACCEPT;

	if (ctinfo == IP_CT_RELATED || ctinfo == IP_CT_RELATED_REPLY) {
		if (ip_hdr(skb)->protocol == IPPROTO_ICMP) {
			if (!nf_nat_icmp_reply_translation(skb, ct, ctinfo,
							   state->hook))
				return NF_DROP;
			else
				return NF_ACCEPT;
		}
	}

	return nf_nat_inet_fn(priv, skb, state);
}