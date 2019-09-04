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
struct TYPE_8__ {int flags; int /*<<< orphan*/  entry; int /*<<< orphan*/ * func; int /*<<< orphan*/ * private; } ;
typedef  TYPE_2__ wait_queue_entry_t ;
struct wait_page_key {int bit_nr; scalar_t__ page_match; struct page* page; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageWaiters (struct page*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_NORMAL ; 
 int WQ_FLAG_BOOKMARK ; 
 int /*<<< orphan*/  __wake_up_locked_key_bookmark (TYPE_1__*,int /*<<< orphan*/ ,struct wait_page_key*,TYPE_2__*) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_1__* page_waitqueue (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  waitqueue_active (TYPE_1__*) ; 

__attribute__((used)) static void wake_up_page_bit(struct page *page, int bit_nr)
{
	wait_queue_head_t *q = page_waitqueue(page);
	struct wait_page_key key;
	unsigned long flags;
	wait_queue_entry_t bookmark;

	key.page = page;
	key.bit_nr = bit_nr;
	key.page_match = 0;

	bookmark.flags = 0;
	bookmark.private = NULL;
	bookmark.func = NULL;
	INIT_LIST_HEAD(&bookmark.entry);

	spin_lock_irqsave(&q->lock, flags);
	__wake_up_locked_key_bookmark(q, TASK_NORMAL, &key, &bookmark);

	while (bookmark.flags & WQ_FLAG_BOOKMARK) {
		/*
		 * Take a breather from holding the lock,
		 * allow pages that finish wake up asynchronously
		 * to acquire the lock and remove themselves
		 * from wait queue
		 */
		spin_unlock_irqrestore(&q->lock, flags);
		cpu_relax();
		spin_lock_irqsave(&q->lock, flags);
		__wake_up_locked_key_bookmark(q, TASK_NORMAL, &key, &bookmark);
	}

	/*
	 * It is possible for other pages to have collided on the waitqueue
	 * hash, so in that case check for a page match. That prevents a long-
	 * term waiter
	 *
	 * It is still possible to miss a case here, when we woke page waiters
	 * and removed them from the waitqueue, but there are still other
	 * page waiters.
	 */
	if (!waitqueue_active(q) || !key.page_match) {
		ClearPageWaiters(page);
		/*
		 * It's possible to miss clearing Waiters here, when we woke
		 * our page waiters, but the hashed waitqueue has waiters for
		 * other pages on it.
		 *
		 * That's okay, it's a rare case. The next waker will clear it.
		 */
	}
	spin_unlock_irqrestore(&q->lock, flags);
}