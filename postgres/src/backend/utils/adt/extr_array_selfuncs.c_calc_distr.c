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
 float DEFAULT_CONTAIN_SEL ; 
 float exp (float) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (float*) ; 

__attribute__((used)) static float *
calc_distr(const float *p, int n, int m, float rest)
{
	float	   *row,
			   *prev_row,
			   *tmp;
	int			i,
				j;

	/*
	 * Since we return only the last row of the matrix and need only the
	 * current and previous row for calculations, allocate two rows.
	 */
	row = (float *) palloc((m + 1) * sizeof(float));
	prev_row = (float *) palloc((m + 1) * sizeof(float));

	/* M[0,0] = 1 */
	row[0] = 1.0f;
	for (i = 1; i <= n; i++)
	{
		float		t = p[i - 1];

		/* Swap rows */
		tmp = row;
		row = prev_row;
		prev_row = tmp;

		/* Calculate next row */
		for (j = 0; j <= i && j <= m; j++)
		{
			float		val = 0.0f;

			if (j < i)
				val += prev_row[j] * (1.0f - t);
			if (j > 0)
				val += prev_row[j - 1] * t;
			row[j] = val;
		}
	}

	/*
	 * The presence of many distinct rare (not in "p") elements materially
	 * decreases selectivity.  Model their collective occurrence with the
	 * Poisson distribution.
	 */
	if (rest > DEFAULT_CONTAIN_SEL)
	{
		float		t;

		/* Swap rows */
		tmp = row;
		row = prev_row;
		prev_row = tmp;

		for (i = 0; i <= m; i++)
			row[i] = 0.0f;

		/* Value of Poisson distribution for 0 occurrences */
		t = exp(-rest);

		/*
		 * Calculate convolution of previously computed distribution and the
		 * Poisson distribution.
		 */
		for (i = 0; i <= m; i++)
		{
			for (j = 0; j <= m - i; j++)
				row[j + i] += prev_row[j] * t;

			/* Get Poisson distribution value for (i + 1) occurrences */
			t *= rest / (float) (i + 1);
		}
	}

	pfree(prev_row);
	return row;
}