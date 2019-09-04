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
struct task_struct {TYPE_1__* delays; } ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ swapin_delay; scalar_t__ blkio_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  nsec_to_clock_t (scalar_t__) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__u64 __delayacct_blkio_ticks(struct task_struct *tsk)
{
	__u64 ret;
	unsigned long flags;

	raw_spin_lock_irqsave(&tsk->delays->lock, flags);
	ret = nsec_to_clock_t(tsk->delays->blkio_delay +
				tsk->delays->swapin_delay);
	raw_spin_unlock_irqrestore(&tsk->delays->lock, flags);
	return ret;
}