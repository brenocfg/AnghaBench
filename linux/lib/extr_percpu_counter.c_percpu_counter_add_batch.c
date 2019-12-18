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
struct percpu_counter {int /*<<< orphan*/ * counters; int /*<<< orphan*/  lock; scalar_t__ count; } ;
typedef  scalar_t__ s64 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_sub (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  this_cpu_add (int /*<<< orphan*/ ,scalar_t__) ; 

void percpu_counter_add_batch(struct percpu_counter *fbc, s64 amount, s32 batch)
{
	s64 count;

	preempt_disable();
	count = __this_cpu_read(*fbc->counters) + amount;
	if (count >= batch || count <= -batch) {
		unsigned long flags;
		raw_spin_lock_irqsave(&fbc->lock, flags);
		fbc->count += count;
		__this_cpu_sub(*fbc->counters, count - amount);
		raw_spin_unlock_irqrestore(&fbc->lock, flags);
	} else {
		this_cpu_add(*fbc->counters, amount);
	}
	preempt_enable();
}