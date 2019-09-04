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
struct genl_info {scalar_t__* attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t TASKSTATS_CMD_ATTR_DEREGISTER_CPUMASK ; 
 size_t TASKSTATS_CMD_ATTR_PID ; 
 size_t TASKSTATS_CMD_ATTR_REGISTER_CPUMASK ; 
 size_t TASKSTATS_CMD_ATTR_TGID ; 
 int cmd_attr_deregister_cpumask (struct genl_info*) ; 
 int cmd_attr_pid (struct genl_info*) ; 
 int cmd_attr_register_cpumask (struct genl_info*) ; 
 int cmd_attr_tgid (struct genl_info*) ; 

__attribute__((used)) static int taskstats_user_cmd(struct sk_buff *skb, struct genl_info *info)
{
	if (info->attrs[TASKSTATS_CMD_ATTR_REGISTER_CPUMASK])
		return cmd_attr_register_cpumask(info);
	else if (info->attrs[TASKSTATS_CMD_ATTR_DEREGISTER_CPUMASK])
		return cmd_attr_deregister_cpumask(info);
	else if (info->attrs[TASKSTATS_CMD_ATTR_PID])
		return cmd_attr_pid(info);
	else if (info->attrs[TASKSTATS_CMD_ATTR_TGID])
		return cmd_attr_tgid(info);
	else
		return -EINVAL;
}