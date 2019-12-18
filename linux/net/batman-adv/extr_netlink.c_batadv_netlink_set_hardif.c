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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct genl_info {struct nlattr** attrs; struct batadv_priv** user_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  throughput_override; int /*<<< orphan*/  elp_interval; } ;
struct batadv_priv {TYPE_1__ bat_v; } ;
struct batadv_hard_iface {TYPE_1__ bat_v; } ;

/* Variables and functions */
 size_t BATADV_ATTR_ELP_INTERVAL ; 
 size_t BATADV_ATTR_THROUGHPUT_OVERRIDE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_netlink_notify_hardif (struct batadv_priv*,struct batadv_priv*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 

__attribute__((used)) static int batadv_netlink_set_hardif(struct sk_buff *skb,
				     struct genl_info *info)
{
	struct batadv_hard_iface *hard_iface = info->user_ptr[1];
	struct batadv_priv *bat_priv = info->user_ptr[0];

#ifdef CONFIG_BATMAN_ADV_BATMAN_V
	struct nlattr *attr;

	if (info->attrs[BATADV_ATTR_ELP_INTERVAL]) {
		attr = info->attrs[BATADV_ATTR_ELP_INTERVAL];

		atomic_set(&hard_iface->bat_v.elp_interval, nla_get_u32(attr));
	}

	if (info->attrs[BATADV_ATTR_THROUGHPUT_OVERRIDE]) {
		attr = info->attrs[BATADV_ATTR_THROUGHPUT_OVERRIDE];

		atomic_set(&hard_iface->bat_v.throughput_override,
			   nla_get_u32(attr));
	}
#endif /* CONFIG_BATMAN_ADV_BATMAN_V */

	batadv_netlink_notify_hardif(bat_priv, hard_iface);

	return 0;
}