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
struct work_struct {int /*<<< orphan*/  entry; } ;
struct timer_list {scalar_t__ function; scalar_t__ expires; } ;
struct delayed_work {int cpu; struct workqueue_struct* wq; struct work_struct work; struct timer_list timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int WORK_CPU_UNBOUND ; 
 int /*<<< orphan*/  __queue_work (int,struct workqueue_struct*,struct work_struct*) ; 
 int /*<<< orphan*/  add_timer (struct timer_list*) ; 
 int /*<<< orphan*/  add_timer_on (struct timer_list*,int) ; 
 scalar_t__ delayed_work_timer_fn ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int timer_pending (struct timer_list*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void __queue_delayed_work(int cpu, struct workqueue_struct *wq,
				struct delayed_work *dwork, unsigned long delay)
{
	struct timer_list *timer = &dwork->timer;
	struct work_struct *work = &dwork->work;

	WARN_ON_ONCE(!wq);
	WARN_ON_ONCE(timer->function != delayed_work_timer_fn);
	WARN_ON_ONCE(timer_pending(timer));
	WARN_ON_ONCE(!list_empty(&work->entry));

	/*
	 * If @delay is 0, queue @dwork->work immediately.  This is for
	 * both optimization and correctness.  The earliest @timer can
	 * expire is on the closest next tick and delayed_work users depend
	 * on that there's no such delay when @delay is 0.
	 */
	if (!delay) {
		__queue_work(cpu, wq, &dwork->work);
		return;
	}

	dwork->wq = wq;
	dwork->cpu = cpu;
	timer->expires = jiffies + delay;

	if (unlikely(cpu != WORK_CPU_UNBOUND))
		add_timer_on(timer, cpu);
	else
		add_timer(timer);
}