#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct workqueue_struct {int dummy; } ;
struct delayed_work {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  __queue_delayed_work (int,struct workqueue_struct*,struct delayed_work*,unsigned long) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int try_to_grab_pending (int /*<<< orphan*/ *,int,unsigned long*) ; 
 scalar_t__ unlikely (int) ; 

bool mod_delayed_work_on(int cpu, struct workqueue_struct *wq,
			 struct delayed_work *dwork, unsigned long delay)
{
	unsigned long flags;
	int ret;

	do {
		ret = try_to_grab_pending(&dwork->work, true, &flags);
	} while (unlikely(ret == -EAGAIN));

	if (likely(ret >= 0)) {
		__queue_delayed_work(cpu, wq, dwork, delay);
		local_irq_restore(flags);
	}

	/* -ENOENT from try_to_grab_pending() becomes %true */
	return ret;
}