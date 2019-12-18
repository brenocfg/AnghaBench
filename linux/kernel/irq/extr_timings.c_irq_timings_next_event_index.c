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

/* Variables and functions */
 int PREDICTION_PERIOD_MIN ; 
 int /*<<< orphan*/  memcmp (int*,int*,size_t) ; 

__attribute__((used)) static int irq_timings_next_event_index(int *buffer, size_t len, int period_max)
{
	int period;

	/*
	 * Move the beginning pointer to the end minus the max period x 3.
	 * We are at the point we can begin searching the pattern
	 */
	buffer = &buffer[len - (period_max * 3)];

	/* Adjust the length to the maximum allowed period x 3 */
	len = period_max * 3;

	/*
	 * The buffer contains the suite of intervals, in a ilog2
	 * basis, we are looking for a repetition. We point the
	 * beginning of the search three times the length of the
	 * period beginning at the end of the buffer. We do that for
	 * each suffix.
	 */
	for (period = period_max; period >= PREDICTION_PERIOD_MIN; period--) {

		/*
		 * The first comparison always succeed because the
		 * suffix is deduced from the first n-period bytes of
		 * the buffer and we compare the initial suffix with
		 * itself, so we can skip the first iteration.
		 */
		int idx = period;
		size_t size = period;

		/*
		 * We look if the suite with period 'i' repeat
		 * itself. If it is truncated at the end, as it
		 * repeats we can use the period to find out the next
		 * element with the modulo.
		 */
		while (!memcmp(buffer, &buffer[idx], size * sizeof(int))) {

			/*
			 * Move the index in a period basis
			 */
			idx += size;

			/*
			 * If this condition is reached, all previous
			 * memcmp were successful, so the period is
			 * found.
			 */
			if (idx == len)
				return buffer[len % period];

			/*
			 * If the remaining elements to compare are
			 * smaller than the period, readjust the size
			 * of the comparison for the last iteration.
			 */
			if (len - idx < period)
				size = len - idx;
		}
	}

	return -1;
}