#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct signalfd_ctx {int /*<<< orphan*/  sigmask; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  siginfo_t ;
struct TYPE_7__ {TYPE_1__* sighand; } ;
struct TYPE_6__ {int /*<<< orphan*/  signalfd_wqh; int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int EAGAIN ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 int dequeue_signal (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static ssize_t signalfd_dequeue(struct signalfd_ctx *ctx, siginfo_t *info,
				int nonblock)
{
	ssize_t ret;
	DECLARE_WAITQUEUE(wait, current);

	spin_lock_irq(&current->sighand->siglock);
	ret = dequeue_signal(current, &ctx->sigmask, info);
	switch (ret) {
	case 0:
		if (!nonblock)
			break;
		ret = -EAGAIN;
	default:
		spin_unlock_irq(&current->sighand->siglock);
		return ret;
	}

	add_wait_queue(&current->sighand->signalfd_wqh, &wait);
	for (;;) {
		set_current_state(TASK_INTERRUPTIBLE);
		ret = dequeue_signal(current, &ctx->sigmask, info);
		if (ret != 0)
			break;
		if (signal_pending(current)) {
			ret = -ERESTARTSYS;
			break;
		}
		spin_unlock_irq(&current->sighand->siglock);
		schedule();
		spin_lock_irq(&current->sighand->siglock);
	}
	spin_unlock_irq(&current->sighand->siglock);

	remove_wait_queue(&current->sighand->signalfd_wqh, &wait);
	__set_current_state(TASK_RUNNING);

	return ret;
}