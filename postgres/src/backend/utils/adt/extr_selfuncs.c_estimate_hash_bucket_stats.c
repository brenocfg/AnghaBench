#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* rel; int /*<<< orphan*/  statsTuple; } ;
typedef  TYPE_2__ VariableStatData ;
struct TYPE_13__ {scalar_t__ nnumbers; double* numbers; } ;
struct TYPE_12__ {double stanullfrac; } ;
struct TYPE_10__ {double tuples; double rows; } ;
typedef  double Selectivity ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_3__* Form_pg_statistic ;
typedef  TYPE_4__ AttStatsSlot ;

/* Variables and functions */
 int /*<<< orphan*/  ATTSTATSSLOT_NUMBERS ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ Max (double,double) ; 
 int /*<<< orphan*/  ReleaseVariableStats (TYPE_2__) ; 
 int /*<<< orphan*/  STATISTIC_KIND_MCV ; 
 double clamp_row_est (double) ; 
 int /*<<< orphan*/  examine_variable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  free_attstatsslot (TYPE_4__*) ; 
 scalar_t__ get_attstatsslot (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double get_variable_numdistinct (TYPE_2__*,int*) ; 

void
estimate_hash_bucket_stats(PlannerInfo *root, Node *hashkey, double nbuckets,
						   Selectivity *mcv_freq,
						   Selectivity *bucketsize_frac)
{
	VariableStatData vardata;
	double		estfract,
				ndistinct,
				stanullfrac,
				avgfreq;
	bool		isdefault;
	AttStatsSlot sslot;

	examine_variable(root, hashkey, 0, &vardata);

	/* Look up the frequency of the most common value, if available */
	*mcv_freq = 0.0;

	if (HeapTupleIsValid(vardata.statsTuple))
	{
		if (get_attstatsslot(&sslot, vardata.statsTuple,
							 STATISTIC_KIND_MCV, InvalidOid,
							 ATTSTATSSLOT_NUMBERS))
		{
			/*
			 * The first MCV stat is for the most common value.
			 */
			if (sslot.nnumbers > 0)
				*mcv_freq = sslot.numbers[0];
			free_attstatsslot(&sslot);
		}
	}

	/* Get number of distinct values */
	ndistinct = get_variable_numdistinct(&vardata, &isdefault);

	/*
	 * If ndistinct isn't real, punt.  We normally return 0.1, but if the
	 * mcv_freq is known to be even higher than that, use it instead.
	 */
	if (isdefault)
	{
		*bucketsize_frac = (Selectivity) Max(0.1, *mcv_freq);
		ReleaseVariableStats(vardata);
		return;
	}

	/* Get fraction that are null */
	if (HeapTupleIsValid(vardata.statsTuple))
	{
		Form_pg_statistic stats;

		stats = (Form_pg_statistic) GETSTRUCT(vardata.statsTuple);
		stanullfrac = stats->stanullfrac;
	}
	else
		stanullfrac = 0.0;

	/* Compute avg freq of all distinct data values in raw relation */
	avgfreq = (1.0 - stanullfrac) / ndistinct;

	/*
	 * Adjust ndistinct to account for restriction clauses.  Observe we are
	 * assuming that the data distribution is affected uniformly by the
	 * restriction clauses!
	 *
	 * XXX Possibly better way, but much more expensive: multiply by
	 * selectivity of rel's restriction clauses that mention the target Var.
	 */
	if (vardata.rel && vardata.rel->tuples > 0)
	{
		ndistinct *= vardata.rel->rows / vardata.rel->tuples;
		ndistinct = clamp_row_est(ndistinct);
	}

	/*
	 * Initial estimate of bucketsize fraction is 1/nbuckets as long as the
	 * number of buckets is less than the expected number of distinct values;
	 * otherwise it is 1/ndistinct.
	 */
	if (ndistinct > nbuckets)
		estfract = 1.0 / nbuckets;
	else
		estfract = 1.0 / ndistinct;

	/*
	 * Adjust estimated bucketsize upward to account for skewed distribution.
	 */
	if (avgfreq > 0.0 && *mcv_freq > avgfreq)
		estfract *= *mcv_freq / avgfreq;

	/*
	 * Clamp bucketsize to sane range (the above adjustment could easily
	 * produce an out-of-range result).  We set the lower bound a little above
	 * zero, since zero isn't a very sane result.
	 */
	if (estfract < 1.0e-6)
		estfract = 1.0e-6;
	else if (estfract > 1.0)
		estfract = 1.0;

	*bucketsize_frac = (Selectivity) estfract;

	ReleaseVariableStats(vardata);
}