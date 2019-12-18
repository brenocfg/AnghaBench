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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct genl_info {struct nlattr** attrs; struct batadv_softif_vlan** user_ptr; } ;
struct batadv_softif_vlan {int /*<<< orphan*/  ap_isolation; } ;
struct batadv_priv {int /*<<< orphan*/  ap_isolation; } ;

/* Variables and functions */
 size_t BATADV_ATTR_AP_ISOLATION_ENABLED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  batadv_netlink_notify_vlan (struct batadv_softif_vlan*,struct batadv_softif_vlan*) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 

__attribute__((used)) static int batadv_netlink_set_vlan(struct sk_buff *skb, struct genl_info *info)
{
	struct batadv_softif_vlan *vlan = info->user_ptr[1];
	struct batadv_priv *bat_priv = info->user_ptr[0];
	struct nlattr *attr;

	if (info->attrs[BATADV_ATTR_AP_ISOLATION_ENABLED]) {
		attr = info->attrs[BATADV_ATTR_AP_ISOLATION_ENABLED];

		atomic_set(&vlan->ap_isolation, !!nla_get_u8(attr));
	}

	batadv_netlink_notify_vlan(bat_priv, vlan);

	return 0;
}