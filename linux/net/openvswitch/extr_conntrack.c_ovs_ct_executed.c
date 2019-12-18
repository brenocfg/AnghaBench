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
struct sw_flow_key {int ct_state; scalar_t__ ct_zone; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ id; } ;
struct ovs_conntrack_info {int /*<<< orphan*/  family; TYPE_1__ zone; scalar_t__ force; } ;
struct nf_conn {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int OVS_CS_F_INVALID ; 
 int OVS_CS_F_NAT_MASK ; 
 int OVS_CS_F_TRACKED ; 
 struct nf_conn* ovs_ct_find_existing (struct net*,TYPE_1__*,int /*<<< orphan*/ ,struct sk_buff*,int) ; 

__attribute__((used)) static
struct nf_conn *ovs_ct_executed(struct net *net,
				const struct sw_flow_key *key,
				const struct ovs_conntrack_info *info,
				struct sk_buff *skb,
				bool *ct_executed)
{
	struct nf_conn *ct = NULL;

	/* If no ct, check if we have evidence that an existing conntrack entry
	 * might be found for this skb.  This happens when we lose a skb->_nfct
	 * due to an upcall, or if the direction is being forced.  If the
	 * connection was not confirmed, it is not cached and needs to be run
	 * through conntrack again.
	 */
	*ct_executed = (key->ct_state & OVS_CS_F_TRACKED) &&
		       !(key->ct_state & OVS_CS_F_INVALID) &&
		       (key->ct_zone == info->zone.id);

	if (*ct_executed || (!key->ct_state && info->force)) {
		ct = ovs_ct_find_existing(net, &info->zone, info->family, skb,
					  !!(key->ct_state &
					  OVS_CS_F_NAT_MASK));
	}

	return ct;
}