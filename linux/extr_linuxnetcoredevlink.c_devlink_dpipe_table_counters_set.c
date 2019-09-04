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
struct devlink_dpipe_table {int counters_enabled; int /*<<< orphan*/  priv; TYPE_1__* table_ops; scalar_t__ counter_control_extern; } ;
struct devlink {int /*<<< orphan*/  dpipe_table_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* counters_set_update ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 struct devlink_dpipe_table* devlink_dpipe_table_find (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int devlink_dpipe_table_counters_set(struct devlink *devlink,
					    const char *table_name,
					    bool enable)
{
	struct devlink_dpipe_table *table;

	table = devlink_dpipe_table_find(&devlink->dpipe_table_list,
					 table_name);
	if (!table)
		return -EINVAL;

	if (table->counter_control_extern)
		return -EOPNOTSUPP;

	if (!(table->counters_enabled ^ enable))
		return 0;

	table->counters_enabled = enable;
	if (table->table_ops->counters_set_update)
		table->table_ops->counters_set_update(table->priv, enable);
	return 0;
}