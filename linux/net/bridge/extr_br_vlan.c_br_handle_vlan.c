#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ len; TYPE_1__* dev; } ;
struct net_bridge_vlan_group {int dummy; } ;
struct net_bridge_vlan {int flags; int /*<<< orphan*/  stats; } ;
struct net_bridge_port {int flags; } ;
struct net_bridge {TYPE_1__* dev; } ;
struct br_vlan_stats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct TYPE_4__ {int /*<<< orphan*/  vlan_filtered; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int BRIDGE_VLAN_INFO_UNTAGGED ; 
 int /*<<< orphan*/  BROPT_VLAN_STATS_ENABLED ; 
 TYPE_2__* BR_INPUT_SKB_CB (struct sk_buff*) ; 
 int BR_VLAN_TUNNEL ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  __vlan_hwaccel_clear_tag (struct sk_buff*) ; 
 scalar_t__ br_handle_egress_vlan_tunnel (struct sk_buff*,struct net_bridge_vlan*) ; 
 scalar_t__ br_opt_get (struct net_bridge*,int /*<<< orphan*/ ) ; 
 struct net_bridge_vlan* br_vlan_find (struct net_bridge_vlan_group*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_vlan_get_tag (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_vlan_should_use (struct net_bridge_vlan*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct br_vlan_stats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

struct sk_buff *br_handle_vlan(struct net_bridge *br,
			       const struct net_bridge_port *p,
			       struct net_bridge_vlan_group *vg,
			       struct sk_buff *skb)
{
	struct br_vlan_stats *stats;
	struct net_bridge_vlan *v;
	u16 vid;

	/* If this packet was not filtered at input, let it pass */
	if (!BR_INPUT_SKB_CB(skb)->vlan_filtered)
		goto out;

	/* At this point, we know that the frame was filtered and contains
	 * a valid vlan id.  If the vlan id has untagged flag set,
	 * send untagged; otherwise, send tagged.
	 */
	br_vlan_get_tag(skb, &vid);
	v = br_vlan_find(vg, vid);
	/* Vlan entry must be configured at this point.  The
	 * only exception is the bridge is set in promisc mode and the
	 * packet is destined for the bridge device.  In this case
	 * pass the packet as is.
	 */
	if (!v || !br_vlan_should_use(v)) {
		if ((br->dev->flags & IFF_PROMISC) && skb->dev == br->dev) {
			goto out;
		} else {
			kfree_skb(skb);
			return NULL;
		}
	}
	if (br_opt_get(br, BROPT_VLAN_STATS_ENABLED)) {
		stats = this_cpu_ptr(v->stats);
		u64_stats_update_begin(&stats->syncp);
		stats->tx_bytes += skb->len;
		stats->tx_packets++;
		u64_stats_update_end(&stats->syncp);
	}

	if (v->flags & BRIDGE_VLAN_INFO_UNTAGGED)
		__vlan_hwaccel_clear_tag(skb);

	if (p && (p->flags & BR_VLAN_TUNNEL) &&
	    br_handle_egress_vlan_tunnel(skb, v)) {
		kfree_skb(skb);
		return NULL;
	}
out:
	return skb;
}