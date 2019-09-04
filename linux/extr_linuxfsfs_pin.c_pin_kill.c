#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ wait_queue_entry_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct fs_pin {int done; TYPE_3__ wait; int /*<<< orphan*/  (* kill ) (struct fs_pin*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __add_wait_queue (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  init_wait (TYPE_1__*) ; 
 scalar_t__ likely (int) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fs_pin*) ; 

void pin_kill(struct fs_pin *p)
{
	wait_queue_entry_t wait;

	if (!p) {
		rcu_read_unlock();
		return;
	}
	init_wait(&wait);
	spin_lock_irq(&p->wait.lock);
	if (likely(!p->done)) {
		p->done = -1;
		spin_unlock_irq(&p->wait.lock);
		rcu_read_unlock();
		p->kill(p);
		return;
	}
	if (p->done > 0) {
		spin_unlock_irq(&p->wait.lock);
		rcu_read_unlock();
		return;
	}
	__add_wait_queue(&p->wait, &wait);
	while (1) {
		set_current_state(TASK_UNINTERRUPTIBLE);
		spin_unlock_irq(&p->wait.lock);
		rcu_read_unlock();
		schedule();
		rcu_read_lock();
		if (likely(list_empty(&wait.entry)))
			break;
		/* OK, we know p couldn't have been freed yet */
		spin_lock_irq(&p->wait.lock);
		if (p->done > 0) {
			spin_unlock_irq(&p->wait.lock);
			break;
		}
	}
	rcu_read_unlock();
}