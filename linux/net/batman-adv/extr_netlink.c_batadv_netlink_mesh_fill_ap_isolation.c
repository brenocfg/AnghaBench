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
struct sk_buff {int dummy; } ;
struct batadv_softif_vlan {int /*<<< orphan*/  ap_isolation; } ;
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_ATTR_AP_ISOLATION_ENABLED ; 
 int /*<<< orphan*/  BATADV_NO_FLAGS ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct batadv_softif_vlan* batadv_softif_vlan_get (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_softif_vlan_put (struct batadv_softif_vlan*) ; 
 int nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int batadv_netlink_mesh_fill_ap_isolation(struct sk_buff *msg,
						 struct batadv_priv *bat_priv)
{
	struct batadv_softif_vlan *vlan;
	u8 ap_isolation;

	vlan = batadv_softif_vlan_get(bat_priv, BATADV_NO_FLAGS);
	if (!vlan)
		return 0;

	ap_isolation = atomic_read(&vlan->ap_isolation);
	batadv_softif_vlan_put(vlan);

	return nla_put_u8(msg, BATADV_ATTR_AP_ISOLATION_ENABLED,
			  !!ap_isolation);
}