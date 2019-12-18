#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ wait_queue_head_t ;
struct TYPE_8__ {int /*<<< orphan*/  entry; } ;
typedef  TYPE_2__ wait_queue_entry_t ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  __add_wait_queue_entry_tail (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int do_wait_intr_irq(wait_queue_head_t *wq, wait_queue_entry_t *wait)
{
	if (likely(list_empty(&wait->entry)))
		__add_wait_queue_entry_tail(wq, wait);

	set_current_state(TASK_INTERRUPTIBLE);
	if (signal_pending(current))
		return -ERESTARTSYS;

	spin_unlock_irq(&wq->lock);
	schedule();
	spin_lock_irq(&wq->lock);

	return 0;
}