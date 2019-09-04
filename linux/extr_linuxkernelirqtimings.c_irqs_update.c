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
struct irqt_stat {scalar_t__ last_ts; scalar_t__ avg; int nr_samples; int variance; int valid; scalar_t__ next_evt; scalar_t__ anomalies; } ;
typedef  int s64 ;

/* Variables and functions */
 int IRQ_TIMINGS_SHIFT ; 
 scalar_t__ NSEC_PER_SEC ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (struct irqt_stat*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void irqs_update(struct irqt_stat *irqs, u64 ts)
{
	u64 old_ts = irqs->last_ts;
	u64 variance = 0;
	u64 interval;
	s64 diff;

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
		memset(irqs, 0, sizeof(*irqs));
		irqs->last_ts = ts;
		return;
	}

	/*
	 * Pre-compute the delta with the average as the result is
	 * used several times in this function.
	 */
	diff = interval - irqs->avg;

	/*
	 * Increment the number of samples.
	 */
	irqs->nr_samples++;

	/*
	 * Online variance divided by the number of elements if there
	 * is more than one sample.  Normally the formula is division
	 * by nr_samples - 1 but we assume the number of element will be
	 * more than 32 and dividing by 32 instead of 31 is enough
	 * precise.
	 */
	if (likely(irqs->nr_samples > 1))
		variance = irqs->variance >> IRQ_TIMINGS_SHIFT;

	/*
	 * The rule of thumb in statistics for the normal distribution
	 * is having at least 30 samples in order to have the model to
	 * apply. Values outside the interval are considered as an
	 * anomaly.
	 */
	if ((irqs->nr_samples >= 30) && ((diff * diff) > (9 * variance))) {
		/*
		 * After three consecutive anomalies, we reset the
		 * stats as it is no longer stable enough.
		 */
		if (irqs->anomalies++ >= 3) {
			memset(irqs, 0, sizeof(*irqs));
			irqs->last_ts = ts;
			return;
		}
	} else {
		/*
		 * The anomalies must be consecutives, so at this
		 * point, we reset the anomalies counter.
		 */
		irqs->anomalies = 0;
	}

	/*
	 * The interrupt is considered stable enough to try to predict
	 * the next event on it.
	 */
	irqs->valid = 1;

	/*
	 * Online average algorithm:
	 *
	 *  new_average = average + ((value - average) / count)
	 *
	 * The variance computation depends on the new average
	 * to be computed here first.
	 *
	 */
	irqs->avg = irqs->avg + (diff >> IRQ_TIMINGS_SHIFT);

	/*
	 * Online variance algorithm:
	 *
	 *  new_variance = variance + (value - average) x (value - new_average)
	 *
	 * Warning: irqs->avg is updated with the line above, hence
	 * 'interval - irqs->avg' is no longer equal to 'diff'
	 */
	irqs->variance = irqs->variance + (diff * (interval - irqs->avg));

	/*
	 * Update the next event
	 */
	irqs->next_evt = ts + irqs->avg;
}