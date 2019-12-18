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
struct xa_state {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  func; } ;
struct wait_exceptional_entry_queue {TYPE_1__ wait; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 void* XA_RETRY_ENTRY ; 
 unsigned int dax_entry_order (void*) ; 
 int /*<<< orphan*/ * dax_entry_waitqueue (struct xa_state*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dax_is_locked (void*) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  init_wait (TYPE_1__*) ; 
 int /*<<< orphan*/  prepare_to_wait_exclusive (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  wake_exceptional_entry_func ; 
 int /*<<< orphan*/  xa_is_value (void*) ; 
 void* xas_find_conflict (struct xa_state*) ; 
 int /*<<< orphan*/  xas_lock_irq (struct xa_state*) ; 
 int /*<<< orphan*/  xas_reset (struct xa_state*) ; 
 int /*<<< orphan*/  xas_unlock_irq (struct xa_state*) ; 

__attribute__((used)) static void *get_unlocked_entry(struct xa_state *xas, unsigned int order)
{
	void *entry;
	struct wait_exceptional_entry_queue ewait;
	wait_queue_head_t *wq;

	init_wait(&ewait.wait);
	ewait.wait.func = wake_exceptional_entry_func;

	for (;;) {
		entry = xas_find_conflict(xas);
		if (!entry || WARN_ON_ONCE(!xa_is_value(entry)))
			return entry;
		if (dax_entry_order(entry) < order)
			return XA_RETRY_ENTRY;
		if (!dax_is_locked(entry))
			return entry;

		wq = dax_entry_waitqueue(xas, entry, &ewait.key);
		prepare_to_wait_exclusive(wq, &ewait.wait,
					  TASK_UNINTERRUPTIBLE);
		xas_unlock_irq(xas);
		xas_reset(xas);
		schedule();
		finish_wait(wq, &ewait.wait);
		xas_lock_irq(xas);
	}
}