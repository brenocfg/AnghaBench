#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sigqueue {int flags; int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_4__ {TYPE_1__* sighand; } ;
struct TYPE_3__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SIGQUEUE_PREALLOC ; 
 int /*<<< orphan*/  __sigqueue_free (struct sigqueue*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void sigqueue_free(struct sigqueue *q)
{
	unsigned long flags;
	spinlock_t *lock = &current->sighand->siglock;

	BUG_ON(!(q->flags & SIGQUEUE_PREALLOC));
	/*
	 * We must hold ->siglock while testing q->list
	 * to serialize with collect_signal() or with
	 * __exit_signal()->flush_sigqueue().
	 */
	spin_lock_irqsave(lock, flags);
	q->flags &= ~SIGQUEUE_PREALLOC;
	/*
	 * If it is queued it will be freed when dequeued,
	 * like the "regular" sigqueue.
	 */
	if (!list_empty(&q->list))
		q = NULL;
	spin_unlock_irqrestore(lock, flags);

	if (q)
		__sigqueue_free(q);
}