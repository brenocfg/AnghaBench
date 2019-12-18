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
typedef  int u16 ;
struct net {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;
struct batadv_softif_vlan {int dummy; } ;
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 size_t BATADV_ATTR_VLANID ; 
 int BATADV_VLAN_HAS_TAG ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 struct batadv_softif_vlan* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct batadv_softif_vlan* batadv_softif_vlan_get (struct batadv_priv*,int) ; 
 int nla_get_u16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct batadv_softif_vlan *
batadv_get_vlan_from_info(struct batadv_priv *bat_priv, struct net *net,
			  struct genl_info *info)
{
	struct batadv_softif_vlan *vlan;
	u16 vid;

	if (!info->attrs[BATADV_ATTR_VLANID])
		return ERR_PTR(-EINVAL);

	vid = nla_get_u16(info->attrs[BATADV_ATTR_VLANID]);

	vlan = batadv_softif_vlan_get(bat_priv, vid | BATADV_VLAN_HAS_TAG);
	if (!vlan)
		return ERR_PTR(-ENOENT);

	return vlan;
}