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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct TYPE_4__ {int /*<<< orphan*/  func; } ;
struct wait_exceptional_entry_queue {TYPE_1__ wait; int /*<<< orphan*/  key; } ;
struct address_space {int /*<<< orphan*/  i_pages; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/ * dax_entry_waitqueue (struct address_space*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  init_wait (TYPE_1__*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  wake_exceptional_entry_func ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wait_entry_unlocked(struct address_space *mapping, pgoff_t index,
		void ***slotp, void *entry)
{
	struct wait_exceptional_entry_queue ewait;
	wait_queue_head_t *wq;

	init_wait(&ewait.wait);
	ewait.wait.func = wake_exceptional_entry_func;

	wq = dax_entry_waitqueue(mapping, index, entry, &ewait.key);
	/*
	 * Unlike get_unlocked_entry() there is no guarantee that this
	 * path ever successfully retrieves an unlocked entry before an
	 * inode dies. Perform a non-exclusive wait in case this path
	 * never successfully performs its own wake up.
	 */
	prepare_to_wait(wq, &ewait.wait, TASK_UNINTERRUPTIBLE);
	xa_unlock_irq(&mapping->i_pages);
	schedule();
	finish_wait(wq, &ewait.wait);
}