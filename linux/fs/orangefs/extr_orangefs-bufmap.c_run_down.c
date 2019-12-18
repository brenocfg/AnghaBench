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
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct slot_map {int c; TYPE_2__ q; int /*<<< orphan*/ * map; } ;
struct TYPE_7__ {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (TYPE_1__) ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __add_wait_queue_entry_tail (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  __remove_wait_queue (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ wait ; 

__attribute__((used)) static void run_down(struct slot_map *m)
{
	DEFINE_WAIT(wait);
	spin_lock(&m->q.lock);
	if (m->c != -1) {
		for (;;) {
			if (likely(list_empty(&wait.entry)))
				__add_wait_queue_entry_tail(&m->q, &wait);
			set_current_state(TASK_UNINTERRUPTIBLE);

			if (m->c == -1)
				break;

			spin_unlock(&m->q.lock);
			schedule();
			spin_lock(&m->q.lock);
		}
		__remove_wait_queue(&m->q, &wait);
		__set_current_state(TASK_RUNNING);
	}
	m->map = NULL;
	spin_unlock(&m->q.lock);
}