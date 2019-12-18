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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct completion {scalar_t__ done; TYPE_1__ wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_NORMAL ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  __wake_up_locked (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void complete(struct completion *x)
{
	unsigned long flags;

	spin_lock_irqsave(&x->wait.lock, flags);

	if (x->done != UINT_MAX)
		x->done++;
	__wake_up_locked(&x->wait, TASK_NORMAL, 1);
	spin_unlock_irqrestore(&x->wait.lock, flags);
}