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
struct userfaultfd_wake_range {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct userfaultfd_ctx {TYPE_1__ fault_pending_wqh; TYPE_1__ fault_wqh; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_NORMAL ; 
 int /*<<< orphan*/  __wake_up (TYPE_1__*,int /*<<< orphan*/ ,int,struct userfaultfd_wake_range*) ; 
 int /*<<< orphan*/  __wake_up_locked_key (TYPE_1__*,int /*<<< orphan*/ ,struct userfaultfd_wake_range*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (TYPE_1__*) ; 

__attribute__((used)) static void __wake_userfault(struct userfaultfd_ctx *ctx,
			     struct userfaultfd_wake_range *range)
{
	spin_lock_irq(&ctx->fault_pending_wqh.lock);
	/* wake all in the range and autoremove */
	if (waitqueue_active(&ctx->fault_pending_wqh))
		__wake_up_locked_key(&ctx->fault_pending_wqh, TASK_NORMAL,
				     range);
	if (waitqueue_active(&ctx->fault_wqh))
		__wake_up(&ctx->fault_wqh, TASK_NORMAL, 1, range);
	spin_unlock_irq(&ctx->fault_pending_wqh.lock);
}