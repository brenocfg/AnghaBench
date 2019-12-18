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
typedef  int u8 ;
struct sw_flow_key {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ovs_conntrack_info {int /*<<< orphan*/  zone; int /*<<< orphan*/  family; } ;
struct nf_conntrack_expect {int /*<<< orphan*/  master; } ;
struct nf_conn {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int OVS_CS_F_NEW ; 
 int OVS_CS_F_RELATED ; 
 int OVS_CS_F_TRACKED ; 
 int __ovs_ct_lookup (struct net*,struct sw_flow_key*,struct ovs_conntrack_info const*,struct sk_buff*) ; 
 int /*<<< orphan*/  __ovs_ct_update_key (struct sw_flow_key*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_deliver_cached_events (struct nf_conn*) ; 
 struct nf_conntrack_expect* ovs_ct_expect_find (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*) ; 
 scalar_t__ skb_nfct (struct sk_buff*) ; 

__attribute__((used)) static int ovs_ct_lookup(struct net *net, struct sw_flow_key *key,
			 const struct ovs_conntrack_info *info,
			 struct sk_buff *skb)
{
	struct nf_conntrack_expect *exp;

	/* If we pass an expected packet through nf_conntrack_in() the
	 * expectation is typically removed, but the packet could still be
	 * lost in upcall processing.  To prevent this from happening we
	 * perform an explicit expectation lookup.  Expected connections are
	 * always new, and will be passed through conntrack only when they are
	 * committed, as it is OK to remove the expectation at that time.
	 */
	exp = ovs_ct_expect_find(net, &info->zone, info->family, skb);
	if (exp) {
		u8 state;

		/* NOTE: New connections are NATted and Helped only when
		 * committed, so we are not calling into NAT here.
		 */
		state = OVS_CS_F_TRACKED | OVS_CS_F_NEW | OVS_CS_F_RELATED;
		__ovs_ct_update_key(key, state, &info->zone, exp->master);
	} else {
		struct nf_conn *ct;
		int err;

		err = __ovs_ct_lookup(net, key, info, skb);
		if (err)
			return err;

		ct = (struct nf_conn *)skb_nfct(skb);
		if (ct)
			nf_ct_deliver_cached_events(ct);
	}

	return 0;
}