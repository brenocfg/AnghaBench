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
struct slot_map {scalar_t__ c; TYPE_1__ q; } ;
struct TYPE_8__ {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (TYPE_2__) ; 
 int EINTR ; 
 int ETIMEDOUT ; 
 long HZ ; 
 long ORANGEFS_BUFMAP_WAIT_TIMEOUT_SECS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __add_wait_queue_entry_tail_exclusive (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __wake_up_locked_key (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 long schedule_timeout (long) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 long slot_timeout_secs ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 TYPE_2__ wait ; 
 scalar_t__ waitqueue_active (TYPE_1__*) ; 

__attribute__((used)) static int wait_for_free(struct slot_map *m)
{
	long left = slot_timeout_secs * HZ;
	DEFINE_WAIT(wait);

	do {
		long n = left, t;
		if (likely(list_empty(&wait.entry)))
			__add_wait_queue_entry_tail_exclusive(&m->q, &wait);
		set_current_state(TASK_INTERRUPTIBLE);

		if (m->c > 0)
			break;

		if (m->c < 0) {
			/* we are waiting for map to be installed */
			/* it would better be there soon, or we go away */
			if (n > ORANGEFS_BUFMAP_WAIT_TIMEOUT_SECS * HZ)
				n = ORANGEFS_BUFMAP_WAIT_TIMEOUT_SECS * HZ;
		}
		spin_unlock(&m->q.lock);
		t = schedule_timeout(n);
		spin_lock(&m->q.lock);
		if (unlikely(!t) && n != left && m->c < 0)
			left = t;
		else
			left = t + (left - n);
		if (signal_pending(current))
			left = -EINTR;
	} while (left > 0);

	if (!list_empty(&wait.entry))
		list_del(&wait.entry);
	else if (left <= 0 && waitqueue_active(&m->q))
		__wake_up_locked_key(&m->q, TASK_INTERRUPTIBLE, NULL);
	__set_current_state(TASK_RUNNING);

	if (likely(left > 0))
		return 0;

	return left < 0 ? -EINTR : -ETIMEDOUT;
}