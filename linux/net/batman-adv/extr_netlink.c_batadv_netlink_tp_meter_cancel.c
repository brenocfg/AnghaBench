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
struct genl_info {int /*<<< orphan*/ * attrs; struct batadv_priv** user_ptr; } ;
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 size_t BATADV_ATTR_ORIG_ADDRESS ; 
 int /*<<< orphan*/  BATADV_TP_REASON_CANCEL ; 
 int EINVAL ; 
 int /*<<< orphan*/  batadv_tp_stop (struct batadv_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nla_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
batadv_netlink_tp_meter_cancel(struct sk_buff *skb, struct genl_info *info)
{
	struct batadv_priv *bat_priv = info->user_ptr[0];
	u8 *dst;
	int ret = 0;

	if (!info->attrs[BATADV_ATTR_ORIG_ADDRESS])
		return -EINVAL;

	dst = nla_data(info->attrs[BATADV_ATTR_ORIG_ADDRESS]);

	batadv_tp_stop(bat_priv, dst, BATADV_TP_REASON_CANCEL);

	return ret;
}