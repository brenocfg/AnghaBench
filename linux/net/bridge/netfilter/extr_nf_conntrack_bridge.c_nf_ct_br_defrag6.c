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
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct nf_hook_state {int /*<<< orphan*/  net; } ;
struct nf_conn {int dummy; } ;
struct inet6_skb_parm {int dummy; } ;
struct br_input_skb_cb {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_2__ {int /*<<< orphan*/  frag_max_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTINFO2DIR (int) ; 
 int EINPROGRESS ; 
 TYPE_1__* IP6CB (struct sk_buff*) ; 
 scalar_t__ IP_DEFRAG_CONNTRACK_BRIDGE_IN ; 
 unsigned int NF_ACCEPT ; 
 scalar_t__ NF_CT_DEFAULT_ZONE_ID ; 
 unsigned int NF_DROP ; 
 unsigned int NF_STOLEN ; 
 int /*<<< orphan*/  br_skb_cb_restore (struct sk_buff*,struct br_input_skb_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_skb_cb_save (struct sk_buff*,struct br_input_skb_cb*,int) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  nf_ct_zone (struct nf_conn const*) ; 
 scalar_t__ nf_ct_zone_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nf_ipv6_br_defrag (int /*<<< orphan*/ ,struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static unsigned int nf_ct_br_defrag6(struct sk_buff *skb,
				     const struct nf_hook_state *state)
{
	u16 zone_id = NF_CT_DEFAULT_ZONE_ID;
	enum ip_conntrack_info ctinfo;
	struct br_input_skb_cb cb;
	const struct nf_conn *ct;
	int err;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct)
		zone_id = nf_ct_zone_id(nf_ct_zone(ct), CTINFO2DIR(ctinfo));

	br_skb_cb_save(skb, &cb, sizeof(struct inet6_skb_parm));

	err = nf_ipv6_br_defrag(state->net, skb,
				IP_DEFRAG_CONNTRACK_BRIDGE_IN + zone_id);
	/* queued */
	if (err == -EINPROGRESS)
		return NF_STOLEN;

	br_skb_cb_restore(skb, &cb, IP6CB(skb)->frag_max_size);
	return err == 0 ? NF_ACCEPT : NF_DROP;
}