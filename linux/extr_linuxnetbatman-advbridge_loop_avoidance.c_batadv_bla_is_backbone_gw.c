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
struct batadv_orig_node {int /*<<< orphan*/  orig; TYPE_1__* bat_priv; } ;
struct batadv_bla_backbone_gw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bridge_loop_avoidance; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_backbone_gw_put (struct batadv_bla_backbone_gw*) ; 
 struct batadv_bla_backbone_gw* batadv_backbone_hash_find (TYPE_1__*,int /*<<< orphan*/ ,unsigned short) ; 
 unsigned short batadv_get_vid (struct sk_buff*,int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__) ; 

bool batadv_bla_is_backbone_gw(struct sk_buff *skb,
			       struct batadv_orig_node *orig_node, int hdr_size)
{
	struct batadv_bla_backbone_gw *backbone_gw;
	unsigned short vid;

	if (!atomic_read(&orig_node->bat_priv->bridge_loop_avoidance))
		return false;

	/* first, find out the vid. */
	if (!pskb_may_pull(skb, hdr_size + ETH_HLEN))
		return false;

	vid = batadv_get_vid(skb, hdr_size);

	/* see if this originator is a backbone gw for this VLAN */
	backbone_gw = batadv_backbone_hash_find(orig_node->bat_priv,
						orig_node->orig, vid);
	if (!backbone_gw)
		return false;

	batadv_backbone_gw_put(backbone_gw);
	return true;
}