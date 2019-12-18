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
struct sk_buff {scalar_t__ protocol; scalar_t__ vlan_proto; scalar_t__ len; scalar_t__ vlan_tci; } ;
struct net_bridge_vlan_group {int dummy; } ;
struct net_bridge_vlan {int /*<<< orphan*/  stats; } ;
struct net_bridge {scalar_t__ vlan_proto; } ;
struct br_vlan_stats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; } ;
struct TYPE_2__ {int vlan_filtered; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROPT_VLAN_STATS_ENABLED ; 
 TYPE_1__* BR_INPUT_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,scalar_t__,scalar_t__) ; 
 scalar_t__ br_get_pvid (struct net_bridge_vlan_group*) ; 
 scalar_t__ br_opt_get (struct net_bridge const*,int /*<<< orphan*/ ) ; 
 struct net_bridge_vlan* br_vlan_find (struct net_bridge_vlan_group*,scalar_t__) ; 
 int /*<<< orphan*/  br_vlan_get_tag (struct sk_buff*,scalar_t__*) ; 
 int /*<<< orphan*/  br_vlan_should_use (struct net_bridge_vlan*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_get (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_present (struct sk_buff*) ; 
 struct sk_buff* skb_vlan_untag (struct sk_buff*) ; 
 struct br_vlan_stats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 struct sk_buff* vlan_insert_tag_set_proto (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __allowed_ingress(const struct net_bridge *br,
			      struct net_bridge_vlan_group *vg,
			      struct sk_buff *skb, u16 *vid)
{
	struct br_vlan_stats *stats;
	struct net_bridge_vlan *v;
	bool tagged;

	BR_INPUT_SKB_CB(skb)->vlan_filtered = true;
	/* If vlan tx offload is disabled on bridge device and frame was
	 * sent from vlan device on the bridge device, it does not have
	 * HW accelerated vlan tag.
	 */
	if (unlikely(!skb_vlan_tag_present(skb) &&
		     skb->protocol == br->vlan_proto)) {
		skb = skb_vlan_untag(skb);
		if (unlikely(!skb))
			return false;
	}

	if (!br_vlan_get_tag(skb, vid)) {
		/* Tagged frame */
		if (skb->vlan_proto != br->vlan_proto) {
			/* Protocol-mismatch, empty out vlan_tci for new tag */
			skb_push(skb, ETH_HLEN);
			skb = vlan_insert_tag_set_proto(skb, skb->vlan_proto,
							skb_vlan_tag_get(skb));
			if (unlikely(!skb))
				return false;

			skb_pull(skb, ETH_HLEN);
			skb_reset_mac_len(skb);
			*vid = 0;
			tagged = false;
		} else {
			tagged = true;
		}
	} else {
		/* Untagged frame */
		tagged = false;
	}

	if (!*vid) {
		u16 pvid = br_get_pvid(vg);

		/* Frame had a tag with VID 0 or did not have a tag.
		 * See if pvid is set on this port.  That tells us which
		 * vlan untagged or priority-tagged traffic belongs to.
		 */
		if (!pvid)
			goto drop;

		/* PVID is set on this port.  Any untagged or priority-tagged
		 * ingress frame is considered to belong to this vlan.
		 */
		*vid = pvid;
		if (likely(!tagged))
			/* Untagged Frame. */
			__vlan_hwaccel_put_tag(skb, br->vlan_proto, pvid);
		else
			/* Priority-tagged Frame.
			 * At this point, we know that skb->vlan_tci VID
			 * field was 0.
			 * We update only VID field and preserve PCP field.
			 */
			skb->vlan_tci |= pvid;

		/* if stats are disabled we can avoid the lookup */
		if (!br_opt_get(br, BROPT_VLAN_STATS_ENABLED))
			return true;
	}
	v = br_vlan_find(vg, *vid);
	if (!v || !br_vlan_should_use(v))
		goto drop;

	if (br_opt_get(br, BROPT_VLAN_STATS_ENABLED)) {
		stats = this_cpu_ptr(v->stats);
		u64_stats_update_begin(&stats->syncp);
		stats->rx_bytes += skb->len;
		stats->rx_packets++;
		u64_stats_update_end(&stats->syncp);
	}

	return true;

drop:
	kfree_skb(skb);
	return false;
}