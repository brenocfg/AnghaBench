#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  float4 ;
struct TYPE_4__ {int /*<<< orphan*/  frequency; int /*<<< orphan*/ * element; } ;
typedef  TYPE_1__ TextFreq ;
typedef  int /*<<< orphan*/  TSQuery ;
typedef  int /*<<< orphan*/  Selectivity ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GETOPERAND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GETQUERY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARATT_IS_COMPRESSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARATT_IS_EXTERNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 int /*<<< orphan*/  tsquery_opr_selec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsquery_opr_selec_no_stats (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Selectivity
mcelem_tsquery_selec(TSQuery query, Datum *mcelem, int nmcelem,
					 float4 *numbers, int nnumbers)
{
	float4		minfreq;
	TextFreq   *lookup;
	Selectivity selec;
	int			i;

	/*
	 * There should be two more Numbers than Values, because the last two
	 * cells are taken for minimal and maximal frequency.  Punt if not.
	 *
	 * (Note: the MCELEM statistics slot definition allows for a third extra
	 * number containing the frequency of nulls, but we're not expecting that
	 * to appear for a tsvector column.)
	 */
	if (nnumbers != nmcelem + 2)
		return tsquery_opr_selec_no_stats(query);

	/*
	 * Transpose the data into a single array so we can use bsearch().
	 */
	lookup = (TextFreq *) palloc(sizeof(TextFreq) * nmcelem);
	for (i = 0; i < nmcelem; i++)
	{
		/*
		 * The text Datums came from an array, so it cannot be compressed or
		 * stored out-of-line -- it's safe to use VARSIZE_ANY*.
		 */
		Assert(!VARATT_IS_COMPRESSED(mcelem[i]) && !VARATT_IS_EXTERNAL(mcelem[i]));
		lookup[i].element = (text *) DatumGetPointer(mcelem[i]);
		lookup[i].frequency = numbers[i];
	}

	/*
	 * Grab the lowest frequency. compute_tsvector_stats() stored it for us in
	 * the one before the last cell of the Numbers array. See ts_typanalyze.c
	 */
	minfreq = numbers[nnumbers - 2];

	selec = tsquery_opr_selec(GETQUERY(query), GETOPERAND(query), lookup,
							  nmcelem, minfreq);

	pfree(lookup);

	return selec;
}