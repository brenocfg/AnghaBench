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
struct net_device {int dummy; } ;
struct net_bridge_port {TYPE_1__* br; } ;
struct ethhdr {scalar_t__ h_proto; int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; } ;
struct ebt_entry {int bitmask; scalar_t__ ethproto; int /*<<< orphan*/  destmsk; int /*<<< orphan*/  destmac; int /*<<< orphan*/  sourcemsk; int /*<<< orphan*/  sourcemac; int /*<<< orphan*/  logical_out; int /*<<< orphan*/  logical_in; int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_2__ {struct net_device const* dev; } ;

/* Variables and functions */
 int EBT_802_3 ; 
 int EBT_DESTMAC ; 
 int /*<<< orphan*/  EBT_IDEST ; 
 int /*<<< orphan*/  EBT_IIN ; 
 int /*<<< orphan*/  EBT_ILOGICALIN ; 
 int /*<<< orphan*/  EBT_ILOGICALOUT ; 
 int /*<<< orphan*/  EBT_IOUT ; 
 int /*<<< orphan*/  EBT_IPROTO ; 
 int /*<<< orphan*/  EBT_ISOURCE ; 
 int EBT_NOPROTO ; 
 int EBT_SOURCEMAC ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 scalar_t__ NF_INVF (struct ebt_entry const*,int /*<<< orphan*/ ,int) ; 
 struct net_bridge_port* br_port_get_rcu (struct net_device const*) ; 
 int ebt_dev_check (int /*<<< orphan*/ ,struct net_device const*) ; 
 struct ethhdr* eth_hdr (struct sk_buff const*) ; 
 int eth_proto_is_802_3 (scalar_t__) ; 
 int /*<<< orphan*/  ether_addr_equal_masked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff const*) ; 

__attribute__((used)) static inline int
ebt_basic_match(const struct ebt_entry *e, const struct sk_buff *skb,
		const struct net_device *in, const struct net_device *out)
{
	const struct ethhdr *h = eth_hdr(skb);
	const struct net_bridge_port *p;
	__be16 ethproto;

	if (skb_vlan_tag_present(skb))
		ethproto = htons(ETH_P_8021Q);
	else
		ethproto = h->h_proto;

	if (e->bitmask & EBT_802_3) {
		if (NF_INVF(e, EBT_IPROTO, eth_proto_is_802_3(ethproto)))
			return 1;
	} else if (!(e->bitmask & EBT_NOPROTO) &&
		   NF_INVF(e, EBT_IPROTO, e->ethproto != ethproto))
		return 1;

	if (NF_INVF(e, EBT_IIN, ebt_dev_check(e->in, in)))
		return 1;
	if (NF_INVF(e, EBT_IOUT, ebt_dev_check(e->out, out)))
		return 1;
	/* rcu_read_lock()ed by nf_hook_thresh */
	if (in && (p = br_port_get_rcu(in)) != NULL &&
	    NF_INVF(e, EBT_ILOGICALIN,
		    ebt_dev_check(e->logical_in, p->br->dev)))
		return 1;
	if (out && (p = br_port_get_rcu(out)) != NULL &&
	    NF_INVF(e, EBT_ILOGICALOUT,
		    ebt_dev_check(e->logical_out, p->br->dev)))
		return 1;

	if (e->bitmask & EBT_SOURCEMAC) {
		if (NF_INVF(e, EBT_ISOURCE,
			    !ether_addr_equal_masked(h->h_source, e->sourcemac,
						     e->sourcemsk)))
			return 1;
	}
	if (e->bitmask & EBT_DESTMAC) {
		if (NF_INVF(e, EBT_IDEST,
			    !ether_addr_equal_masked(h->h_dest, e->destmac,
						     e->destmsk)))
			return 1;
	}
	return 0;
}