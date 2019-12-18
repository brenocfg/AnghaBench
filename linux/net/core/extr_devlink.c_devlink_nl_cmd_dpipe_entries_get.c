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
struct genl_info {int /*<<< orphan*/ * attrs; struct devlink** user_ptr; } ;
struct devlink_dpipe_table {TYPE_1__* table_ops; } ;
struct devlink {int /*<<< orphan*/  dpipe_table_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  entries_dump; } ;

/* Variables and functions */
 size_t DEVLINK_ATTR_DPIPE_TABLE_NAME ; 
 int /*<<< orphan*/  DEVLINK_CMD_DPIPE_ENTRIES_GET ; 
 int EINVAL ; 
 int devlink_dpipe_entries_fill (struct genl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct devlink_dpipe_table*) ; 
 struct devlink_dpipe_table* devlink_dpipe_table_find (int /*<<< orphan*/ *,char const*) ; 
 char* nla_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_nl_cmd_dpipe_entries_get(struct sk_buff *skb,
					    struct genl_info *info)
{
	struct devlink *devlink = info->user_ptr[0];
	struct devlink_dpipe_table *table;
	const char *table_name;

	if (!info->attrs[DEVLINK_ATTR_DPIPE_TABLE_NAME])
		return -EINVAL;

	table_name = nla_data(info->attrs[DEVLINK_ATTR_DPIPE_TABLE_NAME]);
	table = devlink_dpipe_table_find(&devlink->dpipe_table_list,
					 table_name);
	if (!table)
		return -EINVAL;

	if (!table->table_ops->entries_dump)
		return -EINVAL;

	return devlink_dpipe_entries_fill(info, DEVLINK_CMD_DPIPE_ENTRIES_GET,
					  0, table);
}