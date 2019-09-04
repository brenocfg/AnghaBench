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

/* Variables and functions */
 int /*<<< orphan*/  __start___bug_table ; 
 int /*<<< orphan*/  __stop___bug_table ; 
 int /*<<< orphan*/  clear_once_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void generic_bug_clear_once(void)
{
#ifdef CONFIG_MODULES
	struct module *mod;

	rcu_read_lock_sched();
	list_for_each_entry_rcu(mod, &module_bug_list, bug_list)
		clear_once_table(mod->bug_table,
				 mod->bug_table + mod->num_bugs);
	rcu_read_unlock_sched();
#endif

	clear_once_table(__start___bug_table, __stop___bug_table);
}