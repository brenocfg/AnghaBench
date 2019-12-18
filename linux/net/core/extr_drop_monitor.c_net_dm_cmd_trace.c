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
struct netlink_ext_ack {int dummy; } ;
struct genl_info {TYPE_1__* genlhdr; struct netlink_ext_ack* extack; int /*<<< orphan*/ * attrs; } ;
struct TYPE_2__ {int cmd; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 size_t NET_DM_ATTR_HW_DROPS ; 
 size_t NET_DM_ATTR_SW_DROPS ; 
#define  NET_DM_CMD_START 129 
#define  NET_DM_CMD_STOP 128 
 int net_dm_monitor_start (int,int,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  net_dm_monitor_stop (int,int,struct netlink_ext_ack*) ; 

__attribute__((used)) static int net_dm_cmd_trace(struct sk_buff *skb,
			struct genl_info *info)
{
	bool set_sw = !!info->attrs[NET_DM_ATTR_SW_DROPS];
	bool set_hw = !!info->attrs[NET_DM_ATTR_HW_DROPS];
	struct netlink_ext_ack *extack = info->extack;

	/* To maintain backward compatibility, we start / stop monitoring of
	 * software drops if no flag is specified.
	 */
	if (!set_sw && !set_hw)
		set_sw = true;

	switch (info->genlhdr->cmd) {
	case NET_DM_CMD_START:
		return net_dm_monitor_start(set_sw, set_hw, extack);
	case NET_DM_CMD_STOP:
		net_dm_monitor_stop(set_sw, set_hw, extack);
		return 0;
	}

	return -EOPNOTSUPP;
}