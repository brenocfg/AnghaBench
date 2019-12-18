#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  vartype; int /*<<< orphan*/  statsTuple; } ;
typedef  TYPE_1__ VariableStatData ;
struct TYPE_14__ {int nvalues; int /*<<< orphan*/ * values; int /*<<< orphan*/  stacoll; scalar_t__ nnumbers; int /*<<< orphan*/  staop; } ;
struct TYPE_13__ {int /*<<< orphan*/  fn_oid; } ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_3__ AttStatsSlot ;

/* Variables and functions */
 int /*<<< orphan*/  ATTSTATSSLOT_NUMBERS ; 
 int /*<<< orphan*/  ATTSTATSSLOT_VALUES ; 
 int /*<<< orphan*/  CLAMP_PROBABILITY (double) ; 
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2Coll (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  STATISTIC_KIND_HISTOGRAM ; 
 int /*<<< orphan*/  STATISTIC_KIND_MCV ; 
 scalar_t__ convert_to_scalar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*,double*) ; 
 int /*<<< orphan*/  free_attstatsslot (TYPE_3__*) ; 
 int get_actual_variable_range (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ get_attstatsslot (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double get_variable_numdistinct (TYPE_1__*,int*) ; 
 scalar_t__ isnan (double) ; 
 scalar_t__ statistic_proc_security_check (TYPE_1__*,int /*<<< orphan*/ ) ; 

double
ineq_histogram_selectivity(PlannerInfo *root,
						   VariableStatData *vardata,
						   FmgrInfo *opproc, bool isgt, bool iseq,
						   Datum constval, Oid consttype)
{
	double		hist_selec;
	AttStatsSlot sslot;

	hist_selec = -1.0;

	/*
	 * Someday, ANALYZE might store more than one histogram per rel/att,
	 * corresponding to more than one possible sort ordering defined for the
	 * column type.  However, to make that work we will need to figure out
	 * which staop to search for --- it's not necessarily the one we have at
	 * hand!  (For example, we might have a '<=' operator rather than the '<'
	 * operator that will appear in staop.)  For now, assume that whatever
	 * appears in pg_statistic is sorted the same way our operator sorts, or
	 * the reverse way if isgt is true.
	 */
	if (HeapTupleIsValid(vardata->statsTuple) &&
		statistic_proc_security_check(vardata, opproc->fn_oid) &&
		get_attstatsslot(&sslot, vardata->statsTuple,
						 STATISTIC_KIND_HISTOGRAM, InvalidOid,
						 ATTSTATSSLOT_VALUES))
	{
		if (sslot.nvalues > 1)
		{
			/*
			 * Use binary search to find the desired location, namely the
			 * right end of the histogram bin containing the comparison value,
			 * which is the leftmost entry for which the comparison operator
			 * succeeds (if isgt) or fails (if !isgt).  (If the given operator
			 * isn't actually sort-compatible with the histogram, you'll get
			 * garbage results ... but probably not any more garbage-y than
			 * you would have from the old linear search.)
			 *
			 * In this loop, we pay no attention to whether the operator iseq
			 * or not; that detail will be mopped up below.  (We cannot tell,
			 * anyway, whether the operator thinks the values are equal.)
			 *
			 * If the binary search accesses the first or last histogram
			 * entry, we try to replace that endpoint with the true column min
			 * or max as found by get_actual_variable_range().  This
			 * ameliorates misestimates when the min or max is moving as a
			 * result of changes since the last ANALYZE.  Note that this could
			 * result in effectively including MCVs into the histogram that
			 * weren't there before, but we don't try to correct for that.
			 */
			double		histfrac;
			int			lobound = 0;	/* first possible slot to search */
			int			hibound = sslot.nvalues;	/* last+1 slot to search */
			bool		have_end = false;

			/*
			 * If there are only two histogram entries, we'll want up-to-date
			 * values for both.  (If there are more than two, we need at most
			 * one of them to be updated, so we deal with that within the
			 * loop.)
			 */
			if (sslot.nvalues == 2)
				have_end = get_actual_variable_range(root,
													 vardata,
													 sslot.staop,
													 &sslot.values[0],
													 &sslot.values[1]);

			while (lobound < hibound)
			{
				int			probe = (lobound + hibound) / 2;
				bool		ltcmp;

				/*
				 * If we find ourselves about to compare to the first or last
				 * histogram entry, first try to replace it with the actual
				 * current min or max (unless we already did so above).
				 */
				if (probe == 0 && sslot.nvalues > 2)
					have_end = get_actual_variable_range(root,
														 vardata,
														 sslot.staop,
														 &sslot.values[0],
														 NULL);
				else if (probe == sslot.nvalues - 1 && sslot.nvalues > 2)
					have_end = get_actual_variable_range(root,
														 vardata,
														 sslot.staop,
														 NULL,
														 &sslot.values[probe]);

				ltcmp = DatumGetBool(FunctionCall2Coll(opproc,
													   sslot.stacoll,
													   sslot.values[probe],
													   constval));
				if (isgt)
					ltcmp = !ltcmp;
				if (ltcmp)
					lobound = probe + 1;
				else
					hibound = probe;
			}

			if (lobound <= 0)
			{
				/*
				 * Constant is below lower histogram boundary.  More
				 * precisely, we have found that no entry in the histogram
				 * satisfies the inequality clause (if !isgt) or they all do
				 * (if isgt).  We estimate that that's true of the entire
				 * table, so set histfrac to 0.0 (which we'll flip to 1.0
				 * below, if isgt).
				 */
				histfrac = 0.0;
			}
			else if (lobound >= sslot.nvalues)
			{
				/*
				 * Inverse case: constant is above upper histogram boundary.
				 */
				histfrac = 1.0;
			}
			else
			{
				/* We have values[i-1] <= constant <= values[i]. */
				int			i = lobound;
				double		eq_selec = 0;
				double		val,
							high,
							low;
				double		binfrac;

				/*
				 * In the cases where we'll need it below, obtain an estimate
				 * of the selectivity of "x = constval".  We use a calculation
				 * similar to what var_eq_const() does for a non-MCV constant,
				 * ie, estimate that all distinct non-MCV values occur equally
				 * often.  But multiplication by "1.0 - sumcommon - nullfrac"
				 * will be done by our caller, so we shouldn't do that here.
				 * Therefore we can't try to clamp the estimate by reference
				 * to the least common MCV; the result would be too small.
				 *
				 * Note: since this is effectively assuming that constval
				 * isn't an MCV, it's logically dubious if constval in fact is
				 * one.  But we have to apply *some* correction for equality,
				 * and anyway we cannot tell if constval is an MCV, since we
				 * don't have a suitable equality operator at hand.
				 */
				if (i == 1 || isgt == iseq)
				{
					double		otherdistinct;
					bool		isdefault;
					AttStatsSlot mcvslot;

					/* Get estimated number of distinct values */
					otherdistinct = get_variable_numdistinct(vardata,
															 &isdefault);

					/* Subtract off the number of known MCVs */
					if (get_attstatsslot(&mcvslot, vardata->statsTuple,
										 STATISTIC_KIND_MCV, InvalidOid,
										 ATTSTATSSLOT_NUMBERS))
					{
						otherdistinct -= mcvslot.nnumbers;
						free_attstatsslot(&mcvslot);
					}

					/* If result doesn't seem sane, leave eq_selec at 0 */
					if (otherdistinct > 1)
						eq_selec = 1.0 / otherdistinct;
				}

				/*
				 * Convert the constant and the two nearest bin boundary
				 * values to a uniform comparison scale, and do a linear
				 * interpolation within this bin.
				 */
				if (convert_to_scalar(constval, consttype, sslot.stacoll,
									  &val,
									  sslot.values[i - 1], sslot.values[i],
									  vardata->vartype,
									  &low, &high))
				{
					if (high <= low)
					{
						/* cope if bin boundaries appear identical */
						binfrac = 0.5;
					}
					else if (val <= low)
						binfrac = 0.0;
					else if (val >= high)
						binfrac = 1.0;
					else
					{
						binfrac = (val - low) / (high - low);

						/*
						 * Watch out for the possibility that we got a NaN or
						 * Infinity from the division.  This can happen
						 * despite the previous checks, if for example "low"
						 * is -Infinity.
						 */
						if (isnan(binfrac) ||
							binfrac < 0.0 || binfrac > 1.0)
							binfrac = 0.5;
					}
				}
				else
				{
					/*
					 * Ideally we'd produce an error here, on the grounds that
					 * the given operator shouldn't have scalarXXsel
					 * registered as its selectivity func unless we can deal
					 * with its operand types.  But currently, all manner of
					 * stuff is invoking scalarXXsel, so give a default
					 * estimate until that can be fixed.
					 */
					binfrac = 0.5;
				}

				/*
				 * Now, compute the overall selectivity across the values
				 * represented by the histogram.  We have i-1 full bins and
				 * binfrac partial bin below the constant.
				 */
				histfrac = (double) (i - 1) + binfrac;
				histfrac /= (double) (sslot.nvalues - 1);

				/*
				 * At this point, histfrac is an estimate of the fraction of
				 * the population represented by the histogram that satisfies
				 * "x <= constval".  Somewhat remarkably, this statement is
				 * true regardless of which operator we were doing the probes
				 * with, so long as convert_to_scalar() delivers reasonable
				 * results.  If the probe constant is equal to some histogram
				 * entry, we would have considered the bin to the left of that
				 * entry if probing with "<" or ">=", or the bin to the right
				 * if probing with "<=" or ">"; but binfrac would have come
				 * out as 1.0 in the first case and 0.0 in the second, leading
				 * to the same histfrac in either case.  For probe constants
				 * between histogram entries, we find the same bin and get the
				 * same estimate with any operator.
				 *
				 * The fact that the estimate corresponds to "x <= constval"
				 * and not "x < constval" is because of the way that ANALYZE
				 * constructs the histogram: each entry is, effectively, the
				 * rightmost value in its sample bucket.  So selectivity
				 * values that are exact multiples of 1/(histogram_size-1)
				 * should be understood as estimates including a histogram
				 * entry plus everything to its left.
				 *
				 * However, that breaks down for the first histogram entry,
				 * which necessarily is the leftmost value in its sample
				 * bucket.  That means the first histogram bin is slightly
				 * narrower than the rest, by an amount equal to eq_selec.
				 * Another way to say that is that we want "x <= leftmost" to
				 * be estimated as eq_selec not zero.  So, if we're dealing
				 * with the first bin (i==1), rescale to make that true while
				 * adjusting the rest of that bin linearly.
				 */
				if (i == 1)
					histfrac += eq_selec * (1.0 - binfrac);

				/*
				 * "x <= constval" is good if we want an estimate for "<=" or
				 * ">", but if we are estimating for "<" or ">=", we now need
				 * to decrease the estimate by eq_selec.
				 */
				if (isgt == iseq)
					histfrac -= eq_selec;
			}

			/*
			 * Now the estimate is finished for "<" and "<=" cases.  If we are
			 * estimating for ">" or ">=", flip it.
			 */
			hist_selec = isgt ? (1.0 - histfrac) : histfrac;

			/*
			 * The histogram boundaries are only approximate to begin with,
			 * and may well be out of date anyway.  Therefore, don't believe
			 * extremely small or large selectivity estimates --- unless we
			 * got actual current endpoint values from the table, in which
			 * case just do the usual sanity clamp.  Somewhat arbitrarily, we
			 * set the cutoff for other cases at a hundredth of the histogram
			 * resolution.
			 */
			if (have_end)
				CLAMP_PROBABILITY(hist_selec);
			else
			{
				double		cutoff = 0.01 / (double) (sslot.nvalues - 1);

				if (hist_selec < cutoff)
					hist_selec = cutoff;
				else if (hist_selec > 1.0 - cutoff)
					hist_selec = 1.0 - cutoff;
			}
		}

		free_attstatsslot(&sslot);
	}

	return hist_selec;
}