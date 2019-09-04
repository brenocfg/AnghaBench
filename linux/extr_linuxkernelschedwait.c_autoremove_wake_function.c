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
struct wait_queue_entry {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int default_wake_function (struct wait_queue_entry*,unsigned int,int,void*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

int autoremove_wake_function(struct wait_queue_entry *wq_entry, unsigned mode, int sync, void *key)
{
	int ret = default_wake_function(wq_entry, mode, sync, key);

	if (ret)
		list_del_init(&wq_entry->entry);

	return ret;
}