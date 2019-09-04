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
struct devlink_dpipe_table {int /*<<< orphan*/  list; } ;
struct devlink {int /*<<< orphan*/  lock; int /*<<< orphan*/  dpipe_table_list; } ;

/* Variables and functions */
 struct devlink_dpipe_table* devlink_dpipe_table_find (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  kfree_rcu (struct devlink_dpipe_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 

void devlink_dpipe_table_unregister(struct devlink *devlink,
				    const char *table_name)
{
	struct devlink_dpipe_table *table;

	mutex_lock(&devlink->lock);
	table = devlink_dpipe_table_find(&devlink->dpipe_table_list,
					 table_name);
	if (!table)
		goto unlock;
	list_del_rcu(&table->list);
	mutex_unlock(&devlink->lock);
	kfree_rcu(table, rcu);
	return;
unlock:
	mutex_unlock(&devlink->lock);
}