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
typedef  int float4 ;

/* Variables and functions */
 scalar_t__ palloc (int) ; 

__attribute__((used)) static float *
calc_hist(const float4 *hist, int nhist, int n)
{
	float	   *hist_part;
	int			k,
				i = 0;
	float		prev_interval = 0,
				next_interval;
	float		frac;

	hist_part = (float *) palloc((n + 1) * sizeof(float));

	/*
	 * frac is a probability contribution for each interval between histogram
	 * values.  We have nhist - 1 intervals, so contribution of each one will
	 * be 1 / (nhist - 1).
	 */
	frac = 1.0f / ((float) (nhist - 1));

	for (k = 0; k <= n; k++)
	{
		int			count = 0;

		/*
		 * Count the histogram boundaries equal to k.  (Although the histogram
		 * should theoretically contain only exact integers, entries are
		 * floats so there could be roundoff error in large values.  Treat any
		 * fractional value as equal to the next larger k.)
		 */
		while (i < nhist && hist[i] <= k)
		{
			count++;
			i++;
		}

		if (count > 0)
		{
			/* k is an exact bound for at least one histogram box. */
			float		val;

			/* Find length between current histogram value and the next one */
			if (i < nhist)
				next_interval = hist[i] - hist[i - 1];
			else
				next_interval = 0;

			/*
			 * count - 1 histogram boxes contain k exclusively.  They
			 * contribute a total of (count - 1) * frac probability.  Also
			 * factor in the partial histogram boxes on either side.
			 */
			val = (float) (count - 1);
			if (next_interval > 0)
				val += 0.5f / next_interval;
			if (prev_interval > 0)
				val += 0.5f / prev_interval;
			hist_part[k] = frac * val;

			prev_interval = next_interval;
		}
		else
		{
			/* k does not appear as an exact histogram bound. */
			if (prev_interval > 0)
				hist_part[k] = frac / prev_interval;
			else
				hist_part[k] = 0.0f;
		}
	}

	return hist_part;
}