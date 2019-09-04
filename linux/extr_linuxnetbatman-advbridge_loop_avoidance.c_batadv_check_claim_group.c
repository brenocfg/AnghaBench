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
typedef  int /*<<< orphan*/  u8 ;
struct ethhdr {int /*<<< orphan*/ * h_source; } ;
struct batadv_bla_claim_dst {int type; scalar_t__ group; } ;
struct TYPE_3__ {struct batadv_bla_claim_dst claim_dest; } ;
struct batadv_priv {TYPE_1__ bla; } ;
struct batadv_orig_node {int dummy; } ;
struct batadv_hard_iface {TYPE_2__* net_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
#define  BATADV_CLAIM_TYPE_ANNOUNCE 131 
#define  BATADV_CLAIM_TYPE_CLAIM 130 
#define  BATADV_CLAIM_TYPE_REQUEST 129 
#define  BATADV_CLAIM_TYPE_UNCLAIM 128 
 int /*<<< orphan*/  BATADV_DBG_BLA ; 
 scalar_t__ batadv_compare_eth (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,scalar_t__) ; 
 struct batadv_orig_node* batadv_orig_hash_find (struct batadv_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_orig_node_put (struct batadv_orig_node*) ; 
 scalar_t__ ntohs (scalar_t__) ; 

__attribute__((used)) static int batadv_check_claim_group(struct batadv_priv *bat_priv,
				    struct batadv_hard_iface *primary_if,
				    u8 *hw_src, u8 *hw_dst,
				    struct ethhdr *ethhdr)
{
	u8 *backbone_addr;
	struct batadv_orig_node *orig_node;
	struct batadv_bla_claim_dst *bla_dst, *bla_dst_own;

	bla_dst = (struct batadv_bla_claim_dst *)hw_dst;
	bla_dst_own = &bat_priv->bla.claim_dest;

	/* if announcement packet, use the source,
	 * otherwise assume it is in the hw_src
	 */
	switch (bla_dst->type) {
	case BATADV_CLAIM_TYPE_CLAIM:
		backbone_addr = hw_src;
		break;
	case BATADV_CLAIM_TYPE_REQUEST:
	case BATADV_CLAIM_TYPE_ANNOUNCE:
	case BATADV_CLAIM_TYPE_UNCLAIM:
		backbone_addr = ethhdr->h_source;
		break;
	default:
		return 0;
	}

	/* don't accept claim frames from ourselves */
	if (batadv_compare_eth(backbone_addr, primary_if->net_dev->dev_addr))
		return 0;

	/* if its already the same group, it is fine. */
	if (bla_dst->group == bla_dst_own->group)
		return 2;

	/* lets see if this originator is in our mesh */
	orig_node = batadv_orig_hash_find(bat_priv, backbone_addr);

	/* dont accept claims from gateways which are not in
	 * the same mesh or group.
	 */
	if (!orig_node)
		return 1;

	/* if our mesh friends mac is bigger, use it for ourselves. */
	if (ntohs(bla_dst->group) > ntohs(bla_dst_own->group)) {
		batadv_dbg(BATADV_DBG_BLA, bat_priv,
			   "taking other backbones claim group: %#.4x\n",
			   ntohs(bla_dst->group));
		bla_dst_own->group = bla_dst->group;
	}

	batadv_orig_node_put(orig_node);

	return 2;
}