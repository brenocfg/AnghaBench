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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct genl_info {int /*<<< orphan*/  extack; int /*<<< orphan*/ * attrs; struct devlink** user_ptr; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 size_t DEVLINK_ATTR_PORT_INDEX ; 
 size_t DEVLINK_ATTR_PORT_SPLIT_COUNT ; 
 int EINVAL ; 
 int devlink_port_split (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_nl_cmd_port_split_doit(struct sk_buff *skb,
					  struct genl_info *info)
{
	struct devlink *devlink = info->user_ptr[0];
	u32 port_index;
	u32 count;

	if (!info->attrs[DEVLINK_ATTR_PORT_INDEX] ||
	    !info->attrs[DEVLINK_ATTR_PORT_SPLIT_COUNT])
		return -EINVAL;

	port_index = nla_get_u32(info->attrs[DEVLINK_ATTR_PORT_INDEX]);
	count = nla_get_u32(info->attrs[DEVLINK_ATTR_PORT_SPLIT_COUNT]);
	return devlink_port_split(devlink, port_index, count, info->extack);
}