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
typedef  scalar_t__ u8 ;
struct sk_buff {int dummy; } ;
struct nf_hook_state {int /*<<< orphan*/  hook; } ;
struct nf_conn {int dummy; } ;
struct ipv6hdr {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {scalar_t__ nexthdr; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_ICMPV6 ; 
 int IP_CT_RELATED ; 
 int IP_CT_RELATED_REPLY ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int ipv6_skip_exthdr (struct sk_buff*,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  nf_nat_icmpv6_reply_translation (struct sk_buff*,struct nf_conn*,int,int /*<<< orphan*/ ,int) ; 
 unsigned int nf_nat_inet_fn (void*,struct sk_buff*,struct nf_hook_state const*) ; 

__attribute__((used)) static unsigned int
nf_nat_ipv6_fn(void *priv, struct sk_buff *skb,
	       const struct nf_hook_state *state)
{
	struct nf_conn *ct;
	enum ip_conntrack_info ctinfo;
	__be16 frag_off;
	int hdrlen;
	u8 nexthdr;

	ct = nf_ct_get(skb, &ctinfo);
	/* Can't track?  It's not due to stress, or conntrack would
	 * have dropped it.  Hence it's the user's responsibilty to
	 * packet filter it out, or implement conntrack/NAT for that
	 * protocol. 8) --RR
	 */
	if (!ct)
		return NF_ACCEPT;

	if (ctinfo == IP_CT_RELATED || ctinfo == IP_CT_RELATED_REPLY) {
		nexthdr = ipv6_hdr(skb)->nexthdr;
		hdrlen = ipv6_skip_exthdr(skb, sizeof(struct ipv6hdr),
					  &nexthdr, &frag_off);

		if (hdrlen >= 0 && nexthdr == IPPROTO_ICMPV6) {
			if (!nf_nat_icmpv6_reply_translation(skb, ct, ctinfo,
							     state->hook,
							     hdrlen))
				return NF_DROP;
			else
				return NF_ACCEPT;
		}
	}

	return nf_nat_inet_fn(priv, skb, state);
}