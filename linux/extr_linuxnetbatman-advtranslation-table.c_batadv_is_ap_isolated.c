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
struct batadv_tt_local_entry {int dummy; } ;
struct batadv_tt_global_entry {int dummy; } ;
struct batadv_softif_vlan {int /*<<< orphan*/  ap_isolation; } ;
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 scalar_t__ _batadv_is_ap_isolated (struct batadv_tt_local_entry*,struct batadv_tt_global_entry*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct batadv_softif_vlan* batadv_softif_vlan_get (struct batadv_priv*,unsigned short) ; 
 int /*<<< orphan*/  batadv_softif_vlan_put (struct batadv_softif_vlan*) ; 
 int /*<<< orphan*/  batadv_tt_global_entry_put (struct batadv_tt_global_entry*) ; 
 struct batadv_tt_global_entry* batadv_tt_global_hash_find (struct batadv_priv*,int /*<<< orphan*/ *,unsigned short) ; 
 int /*<<< orphan*/  batadv_tt_local_entry_put (struct batadv_tt_local_entry*) ; 
 struct batadv_tt_local_entry* batadv_tt_local_hash_find (struct batadv_priv*,int /*<<< orphan*/ *,unsigned short) ; 

bool batadv_is_ap_isolated(struct batadv_priv *bat_priv, u8 *src, u8 *dst,
			   unsigned short vid)
{
	struct batadv_tt_local_entry *tt_local_entry;
	struct batadv_tt_global_entry *tt_global_entry;
	struct batadv_softif_vlan *vlan;
	bool ret = false;

	vlan = batadv_softif_vlan_get(bat_priv, vid);
	if (!vlan)
		return false;

	if (!atomic_read(&vlan->ap_isolation))
		goto vlan_put;

	tt_local_entry = batadv_tt_local_hash_find(bat_priv, dst, vid);
	if (!tt_local_entry)
		goto vlan_put;

	tt_global_entry = batadv_tt_global_hash_find(bat_priv, src, vid);
	if (!tt_global_entry)
		goto local_entry_put;

	if (_batadv_is_ap_isolated(tt_local_entry, tt_global_entry))
		ret = true;

	batadv_tt_global_entry_put(tt_global_entry);
local_entry_put:
	batadv_tt_local_entry_put(tt_local_entry);
vlan_put:
	batadv_softif_vlan_put(vlan);
	return ret;
}