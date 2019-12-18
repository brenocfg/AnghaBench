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
struct nlattr {int dummy; } ;
struct batadv_softif_vlan {int /*<<< orphan*/  ap_isolation; } ;
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_NO_FLAGS ; 
 int ENOENT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct batadv_softif_vlan* batadv_softif_vlan_get (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_softif_vlan_put (struct batadv_softif_vlan*) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 

__attribute__((used)) static int batadv_netlink_set_mesh_ap_isolation(struct nlattr *attr,
						struct batadv_priv *bat_priv)
{
	struct batadv_softif_vlan *vlan;

	vlan = batadv_softif_vlan_get(bat_priv, BATADV_NO_FLAGS);
	if (!vlan)
		return -ENOENT;

	atomic_set(&vlan->ap_isolation, !!nla_get_u8(attr));
	batadv_softif_vlan_put(vlan);

	return 0;
}