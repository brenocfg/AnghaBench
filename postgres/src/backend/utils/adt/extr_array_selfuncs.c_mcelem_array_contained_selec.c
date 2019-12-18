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
typedef  float float4 ;
typedef  int /*<<< orphan*/  TypeCacheEntry ;
typedef  float Selectivity ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMP_PROBABILITY (float) ; 
 float DEFAULT_CONTAIN_SEL ; 
 int EFFORT ; 
 float Min (float,float) ; 
 float* calc_distr (float*,int,int,float) ; 
 float* calc_hist (float*,int,int) ; 
 int element_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float exp (float) ; 
 int /*<<< orphan*/  float_compare_desc ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (float*) ; 
 int /*<<< orphan*/  qsort (float*,int,int,int /*<<< orphan*/ ) ; 
 double sqrt (double) ; 

__attribute__((used)) static Selectivity
mcelem_array_contained_selec(Datum *mcelem, int nmcelem,
							 float4 *numbers, int nnumbers,
							 Datum *array_data, int nitems,
							 float4 *hist, int nhist,
							 Oid operator, TypeCacheEntry *typentry)
{
	int			mcelem_index,
				i,
				unique_nitems = 0;
	float		selec,
				minfreq,
				nullelem_freq;
	float	   *dist,
			   *mcelem_dist,
			   *hist_part;
	float		avg_count,
				mult,
				rest;
	float	   *elem_selec;

	/*
	 * There should be three more Numbers than Values in the MCELEM slot,
	 * because the last three cells should hold minimal and maximal frequency
	 * among the non-null elements, and then the frequency of null elements.
	 * Punt if not right, because we can't do much without the element freqs.
	 */
	if (numbers == NULL || nnumbers != nmcelem + 3)
		return DEFAULT_CONTAIN_SEL;

	/* Can't do much without a count histogram, either */
	if (hist == NULL || nhist < 3)
		return DEFAULT_CONTAIN_SEL;

	/*
	 * Grab some of the summary statistics that compute_array_stats() stores:
	 * lowest frequency, frequency of null elements, and average distinct
	 * element count.
	 */
	minfreq = numbers[nmcelem];
	nullelem_freq = numbers[nmcelem + 2];
	avg_count = hist[nhist - 1];

	/*
	 * "rest" will be the sum of the frequencies of all elements not
	 * represented in MCELEM.  The average distinct element count is the sum
	 * of the frequencies of *all* elements.  Begin with that; we will proceed
	 * to subtract the MCELEM frequencies.
	 */
	rest = avg_count;

	/*
	 * mult is a multiplier representing estimate of probability that each
	 * mcelem that is not present in constant doesn't occur.
	 */
	mult = 1.0f;

	/*
	 * elem_selec is array of estimated frequencies for elements in the
	 * constant.
	 */
	elem_selec = (float *) palloc(sizeof(float) * nitems);

	/* Scan mcelem and array in parallel. */
	mcelem_index = 0;
	for (i = 0; i < nitems; i++)
	{
		bool		match = false;

		/* Ignore any duplicates in the array data. */
		if (i > 0 &&
			element_compare(&array_data[i - 1], &array_data[i], typentry) == 0)
			continue;

		/*
		 * Iterate over MCELEM until we find an entry greater than or equal to
		 * this element of the constant.  Update "rest" and "mult" for mcelem
		 * entries skipped over.
		 */
		while (mcelem_index < nmcelem)
		{
			int			cmp = element_compare(&mcelem[mcelem_index],
											  &array_data[i],
											  typentry);

			if (cmp < 0)
			{
				mult *= (1.0f - numbers[mcelem_index]);
				rest -= numbers[mcelem_index];
				mcelem_index++;
			}
			else
			{
				if (cmp == 0)
					match = true;	/* mcelem is found */
				break;
			}
		}

		if (match)
		{
			/* MCELEM matches the array item. */
			elem_selec[unique_nitems] = numbers[mcelem_index];
			/* "rest" is decremented for all mcelems, matched or not */
			rest -= numbers[mcelem_index];
			mcelem_index++;
		}
		else
		{
			/*
			 * The element is not in MCELEM.  Punt, but assume that the
			 * selectivity cannot be more than minfreq / 2.
			 */
			elem_selec[unique_nitems] = Min(DEFAULT_CONTAIN_SEL,
											minfreq / 2);
		}

		unique_nitems++;
	}

	/*
	 * If we handled all constant elements without exhausting the MCELEM
	 * array, finish walking it to complete calculation of "rest" and "mult".
	 */
	while (mcelem_index < nmcelem)
	{
		mult *= (1.0f - numbers[mcelem_index]);
		rest -= numbers[mcelem_index];
		mcelem_index++;
	}

	/*
	 * The presence of many distinct rare elements materially decreases
	 * selectivity.  Use the Poisson distribution to estimate the probability
	 * of a column value having zero occurrences of such elements.  See above
	 * for the definition of "rest".
	 */
	mult *= exp(-rest);

	/*----------
	 * Using the distinct element count histogram requires
	 *		O(unique_nitems * (nmcelem + unique_nitems))
	 * operations.  Beyond a certain computational cost threshold, it's
	 * reasonable to sacrifice accuracy for decreased planning time.  We limit
	 * the number of operations to EFFORT * nmcelem; since nmcelem is limited
	 * by the column's statistics target, the work done is user-controllable.
	 *
	 * If the number of operations would be too large, we can reduce it
	 * without losing all accuracy by reducing unique_nitems and considering
	 * only the most-common elements of the constant array.  To make the
	 * results exactly match what we would have gotten with only those
	 * elements to start with, we'd have to remove any discarded elements'
	 * frequencies from "mult", but since this is only an approximation
	 * anyway, we don't bother with that.  Therefore it's sufficient to qsort
	 * elem_selec[] and take the largest elements.  (They will no longer match
	 * up with the elements of array_data[], but we don't care.)
	 *----------
	 */
#define EFFORT 100

	if ((nmcelem + unique_nitems) > 0 &&
		unique_nitems > EFFORT * nmcelem / (nmcelem + unique_nitems))
	{
		/*
		 * Use the quadratic formula to solve for largest allowable N.  We
		 * have A = 1, B = nmcelem, C = - EFFORT * nmcelem.
		 */
		double		b = (double) nmcelem;
		int			n;

		n = (int) ((sqrt(b * b + 4 * EFFORT * b) - b) / 2);

		/* Sort, then take just the first n elements */
		qsort(elem_selec, unique_nitems, sizeof(float),
			  float_compare_desc);
		unique_nitems = n;
	}

	/*
	 * Calculate probabilities of each distinct element count for both mcelems
	 * and constant elements.  At this point, assume independent element
	 * occurrence.
	 */
	dist = calc_distr(elem_selec, unique_nitems, unique_nitems, 0.0f);
	mcelem_dist = calc_distr(numbers, nmcelem, unique_nitems, rest);

	/* ignore hist[nhist-1], which is the average not a histogram member */
	hist_part = calc_hist(hist, nhist - 1, unique_nitems);

	selec = 0.0f;
	for (i = 0; i <= unique_nitems; i++)
	{
		/*
		 * mult * dist[i] / mcelem_dist[i] gives us probability of qual
		 * matching from assumption of independent element occurrence with the
		 * condition that distinct element count = i.
		 */
		if (mcelem_dist[i] > 0)
			selec += hist_part[i] * mult * dist[i] / mcelem_dist[i];
	}

	pfree(dist);
	pfree(mcelem_dist);
	pfree(hist_part);
	pfree(elem_selec);

	/* Take into account occurrence of NULL element. */
	selec *= (1.0f - nullelem_freq);

	CLAMP_PROBABILITY(selec);

	return selec;
}