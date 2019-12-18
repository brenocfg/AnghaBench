#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct kernfs_node {int flags; int /*<<< orphan*/  rb; int /*<<< orphan*/  active; } ;
struct TYPE_2__ {int /*<<< orphan*/  deactivate_waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int KERNFS_SUICIDAL ; 
 int KERNFS_SUICIDED ; 
 scalar_t__ KN_DEACTIVATED_BIAS ; 
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __kernfs_remove (struct kernfs_node*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernfs_break_active_protection (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_mutex ; 
 TYPE_1__* kernfs_root (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_unbreak_active_protection (struct kernfs_node*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  wait ; 

bool kernfs_remove_self(struct kernfs_node *kn)
{
	bool ret;

	mutex_lock(&kernfs_mutex);
	kernfs_break_active_protection(kn);

	/*
	 * SUICIDAL is used to arbitrate among competing invocations.  Only
	 * the first one will actually perform removal.  When the removal
	 * is complete, SUICIDED is set and the active ref is restored
	 * while holding kernfs_mutex.  The ones which lost arbitration
	 * waits for SUICDED && drained which can happen only after the
	 * enclosing kernfs operation which executed the winning instance
	 * of kernfs_remove_self() finished.
	 */
	if (!(kn->flags & KERNFS_SUICIDAL)) {
		kn->flags |= KERNFS_SUICIDAL;
		__kernfs_remove(kn);
		kn->flags |= KERNFS_SUICIDED;
		ret = true;
	} else {
		wait_queue_head_t *waitq = &kernfs_root(kn)->deactivate_waitq;
		DEFINE_WAIT(wait);

		while (true) {
			prepare_to_wait(waitq, &wait, TASK_UNINTERRUPTIBLE);

			if ((kn->flags & KERNFS_SUICIDED) &&
			    atomic_read(&kn->active) == KN_DEACTIVATED_BIAS)
				break;

			mutex_unlock(&kernfs_mutex);
			schedule();
			mutex_lock(&kernfs_mutex);
		}
		finish_wait(waitq, &wait);
		WARN_ON_ONCE(!RB_EMPTY_NODE(&kn->rb));
		ret = false;
	}

	/*
	 * This must be done while holding kernfs_mutex; otherwise, waiting
	 * for SUICIDED && deactivated could finish prematurely.
	 */
	kernfs_unbreak_active_protection(kn);

	mutex_unlock(&kernfs_mutex);
	return ret;
}