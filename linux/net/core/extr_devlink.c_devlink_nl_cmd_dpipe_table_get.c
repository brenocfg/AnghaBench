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
struct genl_info {scalar_t__* attrs; struct devlink** user_ptr; } ;
struct devlink {int /*<<< orphan*/  dpipe_table_list; } ;

/* Variables and functions */
 size_t DEVLINK_ATTR_DPIPE_TABLE_NAME ; 
 int /*<<< orphan*/  DEVLINK_CMD_DPIPE_TABLE_GET ; 
 int devlink_dpipe_tables_fill (struct genl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 char* nla_data (scalar_t__) ; 

__attribute__((used)) static int devlink_nl_cmd_dpipe_table_get(struct sk_buff *skb,
					  struct genl_info *info)
{
	struct devlink *devlink = info->user_ptr[0];
	const char *table_name =  NULL;

	if (info->attrs[DEVLINK_ATTR_DPIPE_TABLE_NAME])
		table_name = nla_data(info->attrs[DEVLINK_ATTR_DPIPE_TABLE_NAME]);

	return devlink_dpipe_tables_fill(info, DEVLINK_CMD_DPIPE_TABLE_GET, 0,
					 &devlink->dpipe_table_list,
					 table_name);
}