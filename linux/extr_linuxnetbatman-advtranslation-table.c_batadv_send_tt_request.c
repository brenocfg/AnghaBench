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
typedef  int u16 ;
struct batadv_tvlv_tt_vlan_data {int /*<<< orphan*/  crc; int /*<<< orphan*/  vid; } ;
struct batadv_tvlv_tt_data {int /*<<< orphan*/  flags; int /*<<< orphan*/  num_vlan; int /*<<< orphan*/  ttvn; } ;
struct batadv_tt_req_node {int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  req_list_lock; } ;
struct batadv_priv {TYPE_2__ tt; } ;
struct batadv_orig_node {int /*<<< orphan*/  orig; } ;
struct batadv_hard_iface {TYPE_1__* net_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_CNT_TT_REQUEST_TX ; 
 int /*<<< orphan*/  BATADV_DBG_TT ; 
 int /*<<< orphan*/  BATADV_TT_FULL_TABLE ; 
 int /*<<< orphan*/  BATADV_TT_REQUEST ; 
 int /*<<< orphan*/  BATADV_TVLV_TT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_inc_counter (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 struct batadv_hard_iface* batadv_primary_if_get_selected (struct batadv_priv*) ; 
 struct batadv_tt_req_node* batadv_tt_req_node_new (struct batadv_priv*,struct batadv_orig_node*) ; 
 int /*<<< orphan*/  batadv_tt_req_node_put (struct batadv_tt_req_node*) ; 
 int /*<<< orphan*/  batadv_tvlv_unicast_send (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct batadv_tvlv_tt_data*,int) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  kfree (struct batadv_tvlv_tt_data*) ; 
 struct batadv_tvlv_tt_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool batadv_send_tt_request(struct batadv_priv *bat_priv,
				   struct batadv_orig_node *dst_orig_node,
				   u8 ttvn,
				   struct batadv_tvlv_tt_vlan_data *tt_vlan,
				   u16 num_vlan, bool full_table)
{
	struct batadv_tvlv_tt_data *tvlv_tt_data = NULL;
	struct batadv_tt_req_node *tt_req_node = NULL;
	struct batadv_tvlv_tt_vlan_data *tt_vlan_req;
	struct batadv_hard_iface *primary_if;
	bool ret = false;
	int i, size;

	primary_if = batadv_primary_if_get_selected(bat_priv);
	if (!primary_if)
		goto out;

	/* The new tt_req will be issued only if I'm not waiting for a
	 * reply from the same orig_node yet
	 */
	tt_req_node = batadv_tt_req_node_new(bat_priv, dst_orig_node);
	if (!tt_req_node)
		goto out;

	size = sizeof(*tvlv_tt_data) + sizeof(*tt_vlan_req) * num_vlan;
	tvlv_tt_data = kzalloc(size, GFP_ATOMIC);
	if (!tvlv_tt_data)
		goto out;

	tvlv_tt_data->flags = BATADV_TT_REQUEST;
	tvlv_tt_data->ttvn = ttvn;
	tvlv_tt_data->num_vlan = htons(num_vlan);

	/* send all the CRCs within the request. This is needed by intermediate
	 * nodes to ensure they have the correct table before replying
	 */
	tt_vlan_req = (struct batadv_tvlv_tt_vlan_data *)(tvlv_tt_data + 1);
	for (i = 0; i < num_vlan; i++) {
		tt_vlan_req->vid = tt_vlan->vid;
		tt_vlan_req->crc = tt_vlan->crc;

		tt_vlan_req++;
		tt_vlan++;
	}

	if (full_table)
		tvlv_tt_data->flags |= BATADV_TT_FULL_TABLE;

	batadv_dbg(BATADV_DBG_TT, bat_priv, "Sending TT_REQUEST to %pM [%c]\n",
		   dst_orig_node->orig, full_table ? 'F' : '.');

	batadv_inc_counter(bat_priv, BATADV_CNT_TT_REQUEST_TX);
	batadv_tvlv_unicast_send(bat_priv, primary_if->net_dev->dev_addr,
				 dst_orig_node->orig, BATADV_TVLV_TT, 1,
				 tvlv_tt_data, size);
	ret = true;

out:
	if (primary_if)
		batadv_hardif_put(primary_if);

	if (ret && tt_req_node) {
		spin_lock_bh(&bat_priv->tt.req_list_lock);
		if (!hlist_unhashed(&tt_req_node->list)) {
			hlist_del_init(&tt_req_node->list);
			batadv_tt_req_node_put(tt_req_node);
		}
		spin_unlock_bh(&bat_priv->tt.req_list_lock);
	}

	if (tt_req_node)
		batadv_tt_req_node_put(tt_req_node);

	kfree(tvlv_tt_data);
	return ret;
}