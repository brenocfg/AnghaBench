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
struct alarm_base {int /*<<< orphan*/  (* gettime ) () ;int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  expires; } ;
struct alarm {size_t type; TYPE_1__ node; int /*<<< orphan*/  timer; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 struct alarm_base* alarm_bases ; 
 int /*<<< orphan*/  alarmtimer_enqueue (struct alarm_base*,struct alarm*) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  trace_alarmtimer_start (struct alarm*,int /*<<< orphan*/ ) ; 

void alarm_start(struct alarm *alarm, ktime_t start)
{
	struct alarm_base *base = &alarm_bases[alarm->type];
	unsigned long flags;

	spin_lock_irqsave(&base->lock, flags);
	alarm->node.expires = start;
	alarmtimer_enqueue(base, alarm);
	hrtimer_start(&alarm->timer, alarm->node.expires, HRTIMER_MODE_ABS);
	spin_unlock_irqrestore(&base->lock, flags);

	trace_alarmtimer_start(alarm, base->gettime());
}