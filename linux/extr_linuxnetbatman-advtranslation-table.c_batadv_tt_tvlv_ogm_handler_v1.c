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
struct batadv_tvlv_tt_vlan_data {int dummy; } ;
struct batadv_tvlv_tt_data {int /*<<< orphan*/  ttvn; int /*<<< orphan*/  num_vlan; } ;
struct batadv_tvlv_tt_change {int dummy; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int dummy; } ;

/* Variables and functions */
 int batadv_tt_entries (int) ; 
 int /*<<< orphan*/  batadv_tt_update_orig (struct batadv_priv*,struct batadv_orig_node*,struct batadv_tvlv_tt_vlan_data*,int,struct batadv_tvlv_tt_change*,int,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void batadv_tt_tvlv_ogm_handler_v1(struct batadv_priv *bat_priv,
					  struct batadv_orig_node *orig,
					  u8 flags, void *tvlv_value,
					  u16 tvlv_value_len)
{
	struct batadv_tvlv_tt_vlan_data *tt_vlan;
	struct batadv_tvlv_tt_change *tt_change;
	struct batadv_tvlv_tt_data *tt_data;
	u16 num_entries, num_vlan;

	if (tvlv_value_len < sizeof(*tt_data))
		return;

	tt_data = (struct batadv_tvlv_tt_data *)tvlv_value;
	tvlv_value_len -= sizeof(*tt_data);

	num_vlan = ntohs(tt_data->num_vlan);

	if (tvlv_value_len < sizeof(*tt_vlan) * num_vlan)
		return;

	tt_vlan = (struct batadv_tvlv_tt_vlan_data *)(tt_data + 1);
	tt_change = (struct batadv_tvlv_tt_change *)(tt_vlan + num_vlan);
	tvlv_value_len -= sizeof(*tt_vlan) * num_vlan;

	num_entries = batadv_tt_entries(tvlv_value_len);

	batadv_tt_update_orig(bat_priv, orig, tt_vlan, num_vlan, tt_change,
			      num_entries, tt_data->ttvn);
}