#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ wait_queue_head_t ;
struct TYPE_10__ {int /*<<< orphan*/  entry; int /*<<< orphan*/  func; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ wait_queue_entry_t ;
struct wait_page_queue {int bit_nr; struct page* page; TYPE_2__ wait; } ;
struct page {int /*<<< orphan*/  flags; } ;
typedef  enum behavior { ____Placeholder_behavior } behavior ;

/* Variables and functions */
 int DROP ; 
 int EINTR ; 
 int EXCLUSIVE ; 
 int PG_locked ; 
 int /*<<< orphan*/  PageSwapBacked (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 scalar_t__ PageWorkingset (struct page*) ; 
 int SHARED ; 
 int /*<<< orphan*/  SetPageWaiters (struct page*) ; 
 int /*<<< orphan*/  WQ_FLAG_EXCLUSIVE ; 
 int /*<<< orphan*/  __add_wait_queue_entry_tail (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  delayacct_thrashing_end () ; 
 int /*<<< orphan*/  delayacct_thrashing_start () ; 
 int /*<<< orphan*/  finish_wait (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  init_wait (TYPE_2__*) ; 
 int /*<<< orphan*/  io_schedule () ; 
 scalar_t__ likely (int) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psi_memstall_enter (unsigned long*) ; 
 int /*<<< orphan*/  psi_memstall_leave (unsigned long*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_current_state (int) ; 
 scalar_t__ signal_pending_state (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit_lock (int,int /*<<< orphan*/ *) ; 
 int test_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_page_function ; 

__attribute__((used)) static inline int wait_on_page_bit_common(wait_queue_head_t *q,
	struct page *page, int bit_nr, int state, enum behavior behavior)
{
	struct wait_page_queue wait_page;
	wait_queue_entry_t *wait = &wait_page.wait;
	bool bit_is_set;
	bool thrashing = false;
	bool delayacct = false;
	unsigned long pflags;
	int ret = 0;

	if (bit_nr == PG_locked &&
	    !PageUptodate(page) && PageWorkingset(page)) {
		if (!PageSwapBacked(page)) {
			delayacct_thrashing_start();
			delayacct = true;
		}
		psi_memstall_enter(&pflags);
		thrashing = true;
	}

	init_wait(wait);
	wait->flags = behavior == EXCLUSIVE ? WQ_FLAG_EXCLUSIVE : 0;
	wait->func = wake_page_function;
	wait_page.page = page;
	wait_page.bit_nr = bit_nr;

	for (;;) {
		spin_lock_irq(&q->lock);

		if (likely(list_empty(&wait->entry))) {
			__add_wait_queue_entry_tail(q, wait);
			SetPageWaiters(page);
		}

		set_current_state(state);

		spin_unlock_irq(&q->lock);

		bit_is_set = test_bit(bit_nr, &page->flags);
		if (behavior == DROP)
			put_page(page);

		if (likely(bit_is_set))
			io_schedule();

		if (behavior == EXCLUSIVE) {
			if (!test_and_set_bit_lock(bit_nr, &page->flags))
				break;
		} else if (behavior == SHARED) {
			if (!test_bit(bit_nr, &page->flags))
				break;
		}

		if (signal_pending_state(state, current)) {
			ret = -EINTR;
			break;
		}

		if (behavior == DROP) {
			/*
			 * We can no longer safely access page->flags:
			 * even if CONFIG_MEMORY_HOTREMOVE is not enabled,
			 * there is a risk of waiting forever on a page reused
			 * for something that keeps it locked indefinitely.
			 * But best check for -EINTR above before breaking.
			 */
			break;
		}
	}

	finish_wait(q, wait);

	if (thrashing) {
		if (delayacct)
			delayacct_thrashing_end();
		psi_memstall_leave(&pflags);
	}

	/*
	 * A signal could leave PageWaiters set. Clearing it here if
	 * !waitqueue_active would be possible (by open-coding finish_wait),
	 * but still fail to catch it in the case of wait hash collision. We
	 * already can fail to clear wait hash collision cases, so don't
	 * bother with signals either.
	 */

	return ret;
}