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
 double sqrt (double) ; 

__attribute__((used)) static int
analyze_mcv_list(int *mcv_counts,
				 int num_mcv,
				 double stadistinct,
				 double stanullfrac,
				 int samplerows,
				 double totalrows)
{
	double		ndistinct_table;
	double		sumcount;
	int			i;

	/*
	 * If the entire table was sampled, keep the whole list.  This also
	 * protects us against division by zero in the code below.
	 */
	if (samplerows == totalrows || totalrows <= 1.0)
		return num_mcv;

	/* Re-extract the estimated number of distinct nonnull values in table */
	ndistinct_table = stadistinct;
	if (ndistinct_table < 0)
		ndistinct_table = -ndistinct_table * totalrows;

	/*
	 * Exclude the least common values from the MCV list, if they are not
	 * significantly more common than the estimated selectivity they would
	 * have if they weren't in the list.  All non-MCV values are assumed to be
	 * equally common, after taking into account the frequencies of all the
	 * values in the MCV list and the number of nulls (c.f. eqsel()).
	 *
	 * Here sumcount tracks the total count of all but the last (least common)
	 * value in the MCV list, allowing us to determine the effect of excluding
	 * that value from the list.
	 *
	 * Note that we deliberately do this by removing values from the full
	 * list, rather than starting with an empty list and adding values,
	 * because the latter approach can fail to add any values if all the most
	 * common values have around the same frequency and make up the majority
	 * of the table, so that the overall average frequency of all values is
	 * roughly the same as that of the common values.  This would lead to any
	 * uncommon values being significantly overestimated.
	 */
	sumcount = 0.0;
	for (i = 0; i < num_mcv - 1; i++)
		sumcount += mcv_counts[i];

	while (num_mcv > 0)
	{
		double		selec,
					otherdistinct,
					N,
					n,
					K,
					variance,
					stddev;

		/*
		 * Estimated selectivity the least common value would have if it
		 * wasn't in the MCV list (c.f. eqsel()).
		 */
		selec = 1.0 - sumcount / samplerows - stanullfrac;
		if (selec < 0.0)
			selec = 0.0;
		if (selec > 1.0)
			selec = 1.0;
		otherdistinct = ndistinct_table - (num_mcv - 1);
		if (otherdistinct > 1)
			selec /= otherdistinct;

		/*
		 * If the value is kept in the MCV list, its population frequency is
		 * assumed to equal its sample frequency.  We use the lower end of a
		 * textbook continuity-corrected Wald-type confidence interval to
		 * determine if that is significantly more common than the non-MCV
		 * frequency --- specifically we assume the population frequency is
		 * highly likely to be within around 2 standard errors of the sample
		 * frequency, which equates to an interval of 2 standard deviations
		 * either side of the sample count, plus an additional 0.5 for the
		 * continuity correction.  Since we are sampling without replacement,
		 * this is a hypergeometric distribution.
		 *
		 * XXX: Empirically, this approach seems to work quite well, but it
		 * may be worth considering more advanced techniques for estimating
		 * the confidence interval of the hypergeometric distribution.
		 */
		N = totalrows;
		n = samplerows;
		K = N * mcv_counts[num_mcv - 1] / n;
		variance = n * K * (N - K) * (N - n) / (N * N * (N - 1));
		stddev = sqrt(variance);

		if (mcv_counts[num_mcv - 1] > selec * samplerows + 2 * stddev + 0.5)
		{
			/*
			 * The value is significantly more common than the non-MCV
			 * selectivity would suggest.  Keep it, and all the other more
			 * common values in the list.
			 */
			break;
		}
		else
		{
			/* Discard this value and consider the next least common value */
			num_mcv--;
			if (num_mcv == 0)
				break;
			sumcount -= mcv_counts[num_mcv - 1];
		}
	}
	return num_mcv;
}