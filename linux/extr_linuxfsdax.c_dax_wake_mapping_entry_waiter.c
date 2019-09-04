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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct exceptional_entry_key {int dummy; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_NORMAL ; 
 int /*<<< orphan*/  __wake_up (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct exceptional_entry_key*) ; 
 int /*<<< orphan*/ * dax_entry_waitqueue (struct address_space*,int /*<<< orphan*/ ,void*,struct exceptional_entry_key*) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dax_wake_mapping_entry_waiter(struct address_space *mapping,
		pgoff_t index, void *entry, bool wake_all)
{
	struct exceptional_entry_key key;
	wait_queue_head_t *wq;

	wq = dax_entry_waitqueue(mapping, index, entry, &key);

	/*
	 * Checking for locked entry and prepare_to_wait_exclusive() happens
	 * under the i_pages lock, ditto for entry handling in our callers.
	 * So at this point all tasks that could have seen our entry locked
	 * must be in the waitqueue and the following check will see them.
	 */
	if (waitqueue_active(wq))
		__wake_up(wq, TASK_NORMAL, wake_all ? 0 : 1, &key);
}