#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net {int dummy; } ;
struct ebt_table {TYPE_1__* private; int /*<<< orphan*/  me; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {struct TYPE_4__* entries; scalar_t__ nentries; int /*<<< orphan*/  entries_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBT_ENTRY_ITERATE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ebt_cleanup_entry ; 
 int /*<<< orphan*/  ebt_free_table_info (TYPE_1__*) ; 
 int /*<<< orphan*/  ebt_mutex ; 
 int /*<<< orphan*/  kfree (struct ebt_table*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (TYPE_1__*) ; 

__attribute__((used)) static void __ebt_unregister_table(struct net *net, struct ebt_table *table)
{
	mutex_lock(&ebt_mutex);
	list_del(&table->list);
	mutex_unlock(&ebt_mutex);
	EBT_ENTRY_ITERATE(table->private->entries, table->private->entries_size,
			  ebt_cleanup_entry, net, NULL);
	if (table->private->nentries)
		module_put(table->me);
	vfree(table->private->entries);
	ebt_free_table_info(table->private);
	vfree(table->private);
	kfree(table);
}