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
typedef  void xt_table_info ;
struct xt_table {size_t af; int /*<<< orphan*/  list; void* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct xt_table*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* xt ; 

void *xt_unregister_table(struct xt_table *table)
{
	struct xt_table_info *private;

	mutex_lock(&xt[table->af].mutex);
	private = table->private;
	list_del(&table->list);
	mutex_unlock(&xt[table->af].mutex);
	kfree(table);

	return private;
}