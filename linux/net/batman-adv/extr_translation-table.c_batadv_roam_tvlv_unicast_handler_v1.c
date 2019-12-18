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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct batadv_tvlv_roam_adv {int /*<<< orphan*/  vid; int /*<<< orphan*/  client; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int /*<<< orphan*/  last_ttvn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_CNT_TT_ROAM_ADV_RX ; 
 int /*<<< orphan*/  BATADV_DBG_TT ; 
 int /*<<< orphan*/  BATADV_TT_CLIENT_ROAM ; 
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_inc_counter (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_is_my_mac (struct batadv_priv*,int /*<<< orphan*/ *) ; 
 struct batadv_orig_node* batadv_orig_hash_find (struct batadv_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_orig_node_put (struct batadv_orig_node*) ; 
 int /*<<< orphan*/  batadv_tt_global_add (struct batadv_priv*,struct batadv_orig_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int batadv_roam_tvlv_unicast_handler_v1(struct batadv_priv *bat_priv,
					       u8 *src, u8 *dst,
					       void *tvlv_value,
					       u16 tvlv_value_len)
{
	struct batadv_tvlv_roam_adv *roaming_adv;
	struct batadv_orig_node *orig_node = NULL;

	/* If this node is not the intended recipient of the
	 * roaming advertisement the packet is forwarded
	 * (the tvlv API will re-route the packet).
	 */
	if (!batadv_is_my_mac(bat_priv, dst))
		return NET_RX_DROP;

	if (tvlv_value_len < sizeof(*roaming_adv))
		goto out;

	orig_node = batadv_orig_hash_find(bat_priv, src);
	if (!orig_node)
		goto out;

	batadv_inc_counter(bat_priv, BATADV_CNT_TT_ROAM_ADV_RX);
	roaming_adv = (struct batadv_tvlv_roam_adv *)tvlv_value;

	batadv_dbg(BATADV_DBG_TT, bat_priv,
		   "Received ROAMING_ADV from %pM (client %pM)\n",
		   src, roaming_adv->client);

	batadv_tt_global_add(bat_priv, orig_node, roaming_adv->client,
			     ntohs(roaming_adv->vid), BATADV_TT_CLIENT_ROAM,
			     atomic_read(&orig_node->last_ttvn) + 1);

out:
	if (orig_node)
		batadv_orig_node_put(orig_node);
	return NET_RX_SUCCESS;
}