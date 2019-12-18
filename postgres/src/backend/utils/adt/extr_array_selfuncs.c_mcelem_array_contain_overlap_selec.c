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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int float4 ;
typedef  int /*<<< orphan*/  TypeCacheEntry ;
typedef  double Selectivity ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMP_PROBABILITY (double) ; 
 scalar_t__ DEFAULT_CONTAIN_SEL ; 
 double Min (scalar_t__,int) ; 
 scalar_t__ OID_ARRAY_CONTAINS_OP ; 
 int element_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int find_next_mcelem (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int floor_log2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Selectivity
mcelem_array_contain_overlap_selec(Datum *mcelem, int nmcelem,
								   float4 *numbers, int nnumbers,
								   Datum *array_data, int nitems,
								   Oid operator, TypeCacheEntry *typentry)
{
	Selectivity selec,
				elem_selec;
	int			mcelem_index,
				i;
	bool		use_bsearch;
	float4		minfreq;

	/*
	 * There should be three more Numbers than Values, because the last three
	 * cells should hold minimal and maximal frequency among the non-null
	 * elements, and then the frequency of null elements.  Ignore the Numbers
	 * if not right.
	 */
	if (nnumbers != nmcelem + 3)
	{
		numbers = NULL;
		nnumbers = 0;
	}

	if (numbers)
	{
		/* Grab the lowest observed frequency */
		minfreq = numbers[nmcelem];
	}
	else
	{
		/* Without statistics make some default assumptions */
		minfreq = 2 * (float4) DEFAULT_CONTAIN_SEL;
	}

	/* Decide whether it is faster to use binary search or not. */
	if (nitems * floor_log2((uint32) nmcelem) < nmcelem + nitems)
		use_bsearch = true;
	else
		use_bsearch = false;

	if (operator == OID_ARRAY_CONTAINS_OP)
	{
		/*
		 * Initial selectivity for "column @> const" query is 1.0, and it will
		 * be decreased with each element of constant array.
		 */
		selec = 1.0;
	}
	else
	{
		/*
		 * Initial selectivity for "column && const" query is 0.0, and it will
		 * be increased with each element of constant array.
		 */
		selec = 0.0;
	}

	/* Scan mcelem and array in parallel. */
	mcelem_index = 0;
	for (i = 0; i < nitems; i++)
	{
		bool		match = false;

		/* Ignore any duplicates in the array data. */
		if (i > 0 &&
			element_compare(&array_data[i - 1], &array_data[i], typentry) == 0)
			continue;

		/* Find the smallest MCELEM >= this array item. */
		if (use_bsearch)
		{
			match = find_next_mcelem(mcelem, nmcelem, array_data[i],
									 &mcelem_index, typentry);
		}
		else
		{
			while (mcelem_index < nmcelem)
			{
				int			cmp = element_compare(&mcelem[mcelem_index],
												  &array_data[i],
												  typentry);

				if (cmp < 0)
					mcelem_index++;
				else
				{
					if (cmp == 0)
						match = true;	/* mcelem is found */
					break;
				}
			}
		}

		if (match && numbers)
		{
			/* MCELEM matches the array item; use its frequency. */
			elem_selec = numbers[mcelem_index];
			mcelem_index++;
		}
		else
		{
			/*
			 * The element is not in MCELEM.  Punt, but assume that the
			 * selectivity cannot be more than minfreq / 2.
			 */
			elem_selec = Min(DEFAULT_CONTAIN_SEL, minfreq / 2);
		}

		/*
		 * Update overall selectivity using the current element's selectivity
		 * and an assumption of element occurrence independence.
		 */
		if (operator == OID_ARRAY_CONTAINS_OP)
			selec *= elem_selec;
		else
			selec = selec + elem_selec - selec * elem_selec;

		/* Clamp intermediate results to stay sane despite roundoff error */
		CLAMP_PROBABILITY(selec);
	}

	return selec;
}