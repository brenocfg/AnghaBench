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
struct fprop_local_percpu {unsigned int period; int /*<<< orphan*/  lock; int /*<<< orphan*/  events; } ;
struct fprop_global {unsigned int period; } ;
typedef  unsigned int s64 ;

/* Variables and functions */
 unsigned int BITS_PER_LONG ; 
 unsigned int PROP_BATCH ; 
 unsigned int nr_cpu_ids ; 
 int /*<<< orphan*/  percpu_counter_add_batch (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 unsigned int percpu_counter_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_counter_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int percpu_counter_sum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fprop_reflect_period_percpu(struct fprop_global *p,
					struct fprop_local_percpu *pl)
{
	unsigned int period = p->period;
	unsigned long flags;

	/* Fast path - period didn't change */
	if (pl->period == period)
		return;
	raw_spin_lock_irqsave(&pl->lock, flags);
	/* Someone updated pl->period while we were spinning? */
	if (pl->period >= period) {
		raw_spin_unlock_irqrestore(&pl->lock, flags);
		return;
	}
	/* Aging zeroed our fraction? */
	if (period - pl->period < BITS_PER_LONG) {
		s64 val = percpu_counter_read(&pl->events);

		if (val < (nr_cpu_ids * PROP_BATCH))
			val = percpu_counter_sum(&pl->events);

		percpu_counter_add_batch(&pl->events,
			-val + (val >> (period-pl->period)), PROP_BATCH);
	} else
		percpu_counter_set(&pl->events, 0);
	pl->period = period;
	raw_spin_unlock_irqrestore(&pl->lock, flags);
}