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
struct alarm_base {int /*<<< orphan*/  (* gettime ) () ;int /*<<< orphan*/  lock; } ;
struct alarm {size_t type; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 struct alarm_base* alarm_bases ; 
 int /*<<< orphan*/  alarmtimer_dequeue (struct alarm_base*,struct alarm*) ; 
 int hrtimer_try_to_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  trace_alarmtimer_cancel (struct alarm*,int /*<<< orphan*/ ) ; 

int alarm_try_to_cancel(struct alarm *alarm)
{
	struct alarm_base *base = &alarm_bases[alarm->type];
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&base->lock, flags);
	ret = hrtimer_try_to_cancel(&alarm->timer);
	if (ret >= 0)
		alarmtimer_dequeue(base, alarm);
	spin_unlock_irqrestore(&base->lock, flags);

	trace_alarmtimer_cancel(alarm, base->gettime());
	return ret;
}