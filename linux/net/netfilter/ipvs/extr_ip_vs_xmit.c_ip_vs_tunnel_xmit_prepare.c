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
struct sk_buff {int ipvs_property; } ;
struct ip_vs_conn {int flags; } ;

/* Variables and functions */
 int IP_VS_CONN_F_NFCT ; 
 int NF_ACCEPT ; 
 int ip_vs_confirm_conntrack (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_reset_ct (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_forward_csum (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int ip_vs_tunnel_xmit_prepare(struct sk_buff *skb,
					    struct ip_vs_conn *cp)
{
	int ret = NF_ACCEPT;

	skb->ipvs_property = 1;
	if (unlikely(cp->flags & IP_VS_CONN_F_NFCT))
		ret = ip_vs_confirm_conntrack(skb);
	if (ret == NF_ACCEPT) {
		nf_reset_ct(skb);
		skb_forward_csum(skb);
	}
	return ret;
}