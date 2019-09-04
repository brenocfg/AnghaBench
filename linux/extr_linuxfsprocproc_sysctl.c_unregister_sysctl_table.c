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
struct ctl_table_header {struct ctl_table_header* ctl_table_arg; } ;
struct ctl_table {struct ctl_table* ctl_table_arg; } ;

/* Variables and functions */
 int count_subheaders (struct ctl_table_header*) ; 
 int /*<<< orphan*/  drop_sysctl_table (struct ctl_table_header*) ; 
 int /*<<< orphan*/  kfree (struct ctl_table_header*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_lock ; 
 scalar_t__ unlikely (int) ; 

void unregister_sysctl_table(struct ctl_table_header * header)
{
	int nr_subheaders;
	might_sleep();

	if (header == NULL)
		return;

	nr_subheaders = count_subheaders(header->ctl_table_arg);
	if (unlikely(nr_subheaders > 1)) {
		struct ctl_table_header **subheaders;
		int i;

		subheaders = (struct ctl_table_header **)(header + 1);
		for (i = nr_subheaders -1; i >= 0; i--) {
			struct ctl_table_header *subh = subheaders[i];
			struct ctl_table *table = subh->ctl_table_arg;
			unregister_sysctl_table(subh);
			kfree(table);
		}
		kfree(header);
		return;
	}

	spin_lock(&sysctl_lock);
	drop_sysctl_table(header);
	spin_unlock(&sysctl_lock);
}