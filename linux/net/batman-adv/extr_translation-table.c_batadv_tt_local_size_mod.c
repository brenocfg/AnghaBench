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
struct TYPE_2__ {int /*<<< orphan*/  num_entries; } ;
struct batadv_softif_vlan {TYPE_1__ tt; } ;
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 struct batadv_softif_vlan* batadv_softif_vlan_get (struct batadv_priv*,unsigned short) ; 
 int /*<<< orphan*/  batadv_softif_vlan_put (struct batadv_softif_vlan*) ; 

__attribute__((used)) static void batadv_tt_local_size_mod(struct batadv_priv *bat_priv,
				     unsigned short vid, int v)
{
	struct batadv_softif_vlan *vlan;

	vlan = batadv_softif_vlan_get(bat_priv, vid);
	if (!vlan)
		return;

	atomic_add(v, &vlan->tt.num_entries);

	batadv_softif_vlan_put(vlan);
}