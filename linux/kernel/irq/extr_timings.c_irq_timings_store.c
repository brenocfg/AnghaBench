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
typedef  scalar_t__ u64 ;
struct irqt_stat {scalar_t__ last_ts; scalar_t__ count; } ;

/* Variables and functions */
 scalar_t__ NSEC_PER_SEC ; 
 int /*<<< orphan*/  __irq_timings_store (int,struct irqt_stat*,scalar_t__) ; 

__attribute__((used)) static inline void irq_timings_store(int irq, struct irqt_stat *irqs, u64 ts)
{
	u64 old_ts = irqs->last_ts;
	u64 interval;

	/*
	 * The timestamps are absolute time values, we need to compute
	 * the timing interval between two interrupts.
	 */
	irqs->last_ts = ts;

	/*
	 * The interval type is u64 in order to deal with the same
	 * type in our computation, that prevent mindfuck issues with
	 * overflow, sign and division.
	 */
	interval = ts - old_ts;

	/*
	 * The interrupt triggered more than one second apart, that
	 * ends the sequence as predictible for our purpose. In this
	 * case, assume we have the beginning of a sequence and the
	 * timestamp is the first value. As it is impossible to
	 * predict anything at this point, return.
	 *
	 * Note the first timestamp of the sequence will always fall
	 * in this test because the old_ts is zero. That is what we
	 * want as we need another timestamp to compute an interval.
	 */
	if (interval >= NSEC_PER_SEC) {
		irqs->count = 0;
		return;
	}

	__irq_timings_store(irq, irqs, interval);
}