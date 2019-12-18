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
struct devlink_dpipe_table {int counters_enabled; } ;
struct devlink {int /*<<< orphan*/  dpipe_table_list; } ;

/* Variables and functions */
 struct devlink_dpipe_table* devlink_dpipe_table_find (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

bool devlink_dpipe_table_counter_enabled(struct devlink *devlink,
					 const char *table_name)
{
	struct devlink_dpipe_table *table;
	bool enabled;

	rcu_read_lock();
	table = devlink_dpipe_table_find(&devlink->dpipe_table_list,
					 table_name);
	enabled = false;
	if (table)
		enabled = table->counters_enabled;
	rcu_read_unlock();
	return enabled;
}