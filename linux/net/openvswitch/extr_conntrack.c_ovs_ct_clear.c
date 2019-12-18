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
struct sw_flow_key {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_CT_UNTRACKED ; 
 int /*<<< orphan*/  nf_conntrack_put (scalar_t__) ; 
 int /*<<< orphan*/  nf_ct_set (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_ct_fill_key (struct sk_buff*,struct sw_flow_key*) ; 
 scalar_t__ skb_nfct (struct sk_buff*) ; 

int ovs_ct_clear(struct sk_buff *skb, struct sw_flow_key *key)
{
	if (skb_nfct(skb)) {
		nf_conntrack_put(skb_nfct(skb));
		nf_ct_set(skb, NULL, IP_CT_UNTRACKED);
		ovs_ct_fill_key(skb, key);
	}

	return 0;
}