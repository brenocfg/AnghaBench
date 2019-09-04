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

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  SetPageWaiters (struct page*) ; 
 int /*<<< orphan*/  WQ_FLAG_EXCLUSIVE ; 
 int /*<<< orphan*/  __add_wait_queue_entry_tail (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  init_wait (TYPE_2__*) ; 
 int /*<<< orphan*/  io_schedule () ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_current_state (int) ; 
 int /*<<< orphan*/  signal_pending_state (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit_lock (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_page_function ; 

__attribute__((used)) static inline int wait_on_page_bit_common(wait_queue_head_t *q,
		struct page *page, int bit_nr, int state, bool lock)
{
	struct wait_page_queue wait_page;
	wait_queue_entry_t *wait = &wait_page.wait;
	int ret = 0;

	init_wait(wait);
	wait->flags = lock ? WQ_FLAG_EXCLUSIVE : 0;
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

		if (likely(test_bit(bit_nr, &page->flags))) {
			io_schedule();
		}

		if (lock) {
			if (!test_and_set_bit_lock(bit_nr, &page->flags))
				break;
		} else {
			if (!test_bit(bit_nr, &page->flags))
				break;
		}

		if (unlikely(signal_pending_state(state, current))) {
			ret = -EINTR;
			break;
		}
	}

	finish_wait(q, wait);

	/*
	 * A signal could leave PageWaiters set. Clearing it here if
	 * !waitqueue_active would be possible (by open-coding finish_wait),
	 * but still fail to catch it in the case of wait hash collision. We
	 * already can fail to clear wait hash collision cases, so don't
	 * bother with signals either.
	 */

	return ret;
}