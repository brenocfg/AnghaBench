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
struct sk_buff {scalar_t__ _nfct; } ;
struct nf_hook_state {int dummy; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 unsigned int NF_ACCEPT ; 
 int /*<<< orphan*/  ip_hdr (struct sk_buff*) ; 
 scalar_t__ ip_is_fragment (int /*<<< orphan*/ ) ; 
 unsigned int nf_conntrack_in (struct sk_buff*,struct nf_hook_state const*) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 scalar_t__ nf_ct_is_template (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 

__attribute__((used)) static unsigned int ipv4_conntrack_local(void *priv,
					 struct sk_buff *skb,
					 const struct nf_hook_state *state)
{
	if (ip_is_fragment(ip_hdr(skb))) { /* IP_NODEFRAG setsockopt set */
		enum ip_conntrack_info ctinfo;
		struct nf_conn *tmpl;

		tmpl = nf_ct_get(skb, &ctinfo);
		if (tmpl && nf_ct_is_template(tmpl)) {
			/* when skipping ct, clear templates to avoid fooling
			 * later targets/matches
			 */
			skb->_nfct = 0;
			nf_ct_put(tmpl);
		}
		return NF_ACCEPT;
	}

	return nf_conntrack_in(skb, state);
}