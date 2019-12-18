#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lslot ;
struct TYPE_29__ {int /*<<< orphan*/  statsTuple; } ;
typedef  TYPE_3__ VariableStatData ;
struct TYPE_28__ {int /*<<< orphan*/  fn_oid; } ;
struct TYPE_27__ {int /*<<< orphan*/  fn_oid; } ;
struct TYPE_30__ {TYPE_2__ rng_subdiff_finfo; TYPE_1__ rng_cmp_proc_finfo; } ;
typedef  TYPE_4__ TypeCacheEntry ;
struct TYPE_32__ {int nvalues; int /*<<< orphan*/ * values; } ;
struct TYPE_31__ {int /*<<< orphan*/  infinite; } ;
typedef  int /*<<< orphan*/  RangeType ;
typedef  TYPE_5__ RangeBound ;
typedef  int Oid ;
typedef  TYPE_6__ AttStatsSlot ;

/* Variables and functions */
 int /*<<< orphan*/  ATTSTATSSLOT_VALUES ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  const* DatumGetRangeTypeP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
#define  OID_RANGE_CONTAINED_OP 139 
#define  OID_RANGE_CONTAINS_ELEM_OP 138 
#define  OID_RANGE_CONTAINS_OP 137 
#define  OID_RANGE_GREATER_EQUAL_OP 136 
#define  OID_RANGE_GREATER_OP 135 
#define  OID_RANGE_LEFT_OP 134 
#define  OID_RANGE_LESS_EQUAL_OP 133 
#define  OID_RANGE_LESS_OP 132 
#define  OID_RANGE_OVERLAPS_LEFT_OP 131 
#define  OID_RANGE_OVERLAPS_RIGHT_OP 130 
#define  OID_RANGE_OVERLAP_OP 129 
#define  OID_RANGE_RIGHT_OP 128 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATISTIC_KIND_BOUNDS_HISTOGRAM ; 
 int /*<<< orphan*/  STATISTIC_KIND_RANGE_LENGTH_HISTOGRAM ; 
 double calc_hist_selectivity_contained (TYPE_4__*,TYPE_5__*,TYPE_5__*,TYPE_5__*,int,int /*<<< orphan*/ *,int) ; 
 double calc_hist_selectivity_contains (TYPE_4__*,TYPE_5__*,TYPE_5__*,TYPE_5__*,int,int /*<<< orphan*/ *,int) ; 
 double calc_hist_selectivity_scalar (TYPE_4__*,TYPE_5__*,TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_attstatsslot (TYPE_6__*) ; 
 scalar_t__ get_attstatsslot (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  range_deserialize (TYPE_4__*,int /*<<< orphan*/  const*,TYPE_5__*,TYPE_5__*,int*) ; 
 int /*<<< orphan*/  statistic_proc_security_check (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static double
calc_hist_selectivity(TypeCacheEntry *typcache, VariableStatData *vardata,
					  const RangeType *constval, Oid operator)
{
	AttStatsSlot hslot;
	AttStatsSlot lslot;
	int			nhist;
	RangeBound *hist_lower;
	RangeBound *hist_upper;
	int			i;
	RangeBound	const_lower;
	RangeBound	const_upper;
	bool		empty;
	double		hist_selec;

	/* Can't use the histogram with insecure range support functions */
	if (!statistic_proc_security_check(vardata,
									   typcache->rng_cmp_proc_finfo.fn_oid))
		return -1;
	if (OidIsValid(typcache->rng_subdiff_finfo.fn_oid) &&
		!statistic_proc_security_check(vardata,
									   typcache->rng_subdiff_finfo.fn_oid))
		return -1;

	/* Try to get histogram of ranges */
	if (!(HeapTupleIsValid(vardata->statsTuple) &&
		  get_attstatsslot(&hslot, vardata->statsTuple,
						   STATISTIC_KIND_BOUNDS_HISTOGRAM, InvalidOid,
						   ATTSTATSSLOT_VALUES)))
		return -1.0;

	/*
	 * Convert histogram of ranges into histograms of its lower and upper
	 * bounds.
	 */
	nhist = hslot.nvalues;
	hist_lower = (RangeBound *) palloc(sizeof(RangeBound) * nhist);
	hist_upper = (RangeBound *) palloc(sizeof(RangeBound) * nhist);
	for (i = 0; i < nhist; i++)
	{
		range_deserialize(typcache, DatumGetRangeTypeP(hslot.values[i]),
						  &hist_lower[i], &hist_upper[i], &empty);
		/* The histogram should not contain any empty ranges */
		if (empty)
			elog(ERROR, "bounds histogram contains an empty range");
	}

	/* @> and @< also need a histogram of range lengths */
	if (operator == OID_RANGE_CONTAINS_OP ||
		operator == OID_RANGE_CONTAINED_OP)
	{
		if (!(HeapTupleIsValid(vardata->statsTuple) &&
			  get_attstatsslot(&lslot, vardata->statsTuple,
							   STATISTIC_KIND_RANGE_LENGTH_HISTOGRAM,
							   InvalidOid,
							   ATTSTATSSLOT_VALUES)))
		{
			free_attstatsslot(&hslot);
			return -1.0;
		}

		/* check that it's a histogram, not just a dummy entry */
		if (lslot.nvalues < 2)
		{
			free_attstatsslot(&lslot);
			free_attstatsslot(&hslot);
			return -1.0;
		}
	}
	else
		memset(&lslot, 0, sizeof(lslot));

	/* Extract the bounds of the constant value. */
	range_deserialize(typcache, constval, &const_lower, &const_upper, &empty);
	Assert(!empty);

	/*
	 * Calculate selectivity comparing the lower or upper bound of the
	 * constant with the histogram of lower or upper bounds.
	 */
	switch (operator)
	{
		case OID_RANGE_LESS_OP:

			/*
			 * The regular b-tree comparison operators (<, <=, >, >=) compare
			 * the lower bounds first, and the upper bounds for values with
			 * equal lower bounds. Estimate that by comparing the lower bounds
			 * only. This gives a fairly accurate estimate assuming there
			 * aren't many rows with a lower bound equal to the constant's
			 * lower bound.
			 */
			hist_selec =
				calc_hist_selectivity_scalar(typcache, &const_lower,
											 hist_lower, nhist, false);
			break;

		case OID_RANGE_LESS_EQUAL_OP:
			hist_selec =
				calc_hist_selectivity_scalar(typcache, &const_lower,
											 hist_lower, nhist, true);
			break;

		case OID_RANGE_GREATER_OP:
			hist_selec =
				1 - calc_hist_selectivity_scalar(typcache, &const_lower,
												 hist_lower, nhist, false);
			break;

		case OID_RANGE_GREATER_EQUAL_OP:
			hist_selec =
				1 - calc_hist_selectivity_scalar(typcache, &const_lower,
												 hist_lower, nhist, true);
			break;

		case OID_RANGE_LEFT_OP:
			/* var << const when upper(var) < lower(const) */
			hist_selec =
				calc_hist_selectivity_scalar(typcache, &const_lower,
											 hist_upper, nhist, false);
			break;

		case OID_RANGE_RIGHT_OP:
			/* var >> const when lower(var) > upper(const) */
			hist_selec =
				1 - calc_hist_selectivity_scalar(typcache, &const_upper,
												 hist_lower, nhist, true);
			break;

		case OID_RANGE_OVERLAPS_RIGHT_OP:
			/* compare lower bounds */
			hist_selec =
				1 - calc_hist_selectivity_scalar(typcache, &const_lower,
												 hist_lower, nhist, false);
			break;

		case OID_RANGE_OVERLAPS_LEFT_OP:
			/* compare upper bounds */
			hist_selec =
				calc_hist_selectivity_scalar(typcache, &const_upper,
											 hist_upper, nhist, true);
			break;

		case OID_RANGE_OVERLAP_OP:
		case OID_RANGE_CONTAINS_ELEM_OP:

			/*
			 * A && B <=> NOT (A << B OR A >> B).
			 *
			 * Since A << B and A >> B are mutually exclusive events we can
			 * sum their probabilities to find probability of (A << B OR A >>
			 * B).
			 *
			 * "range @> elem" is equivalent to "range && [elem,elem]". The
			 * caller already constructed the singular range from the element
			 * constant, so just treat it the same as &&.
			 */
			hist_selec =
				calc_hist_selectivity_scalar(typcache, &const_lower, hist_upper,
											 nhist, false);
			hist_selec +=
				(1.0 - calc_hist_selectivity_scalar(typcache, &const_upper, hist_lower,
													nhist, true));
			hist_selec = 1.0 - hist_selec;
			break;

		case OID_RANGE_CONTAINS_OP:
			hist_selec =
				calc_hist_selectivity_contains(typcache, &const_lower,
											   &const_upper, hist_lower, nhist,
											   lslot.values, lslot.nvalues);
			break;

		case OID_RANGE_CONTAINED_OP:
			if (const_lower.infinite)
			{
				/*
				 * Lower bound no longer matters. Just estimate the fraction
				 * with an upper bound <= const upper bound
				 */
				hist_selec =
					calc_hist_selectivity_scalar(typcache, &const_upper,
												 hist_upper, nhist, true);
			}
			else if (const_upper.infinite)
			{
				hist_selec =
					1.0 - calc_hist_selectivity_scalar(typcache, &const_lower,
													   hist_lower, nhist, false);
			}
			else
			{
				hist_selec =
					calc_hist_selectivity_contained(typcache, &const_lower,
													&const_upper, hist_lower, nhist,
													lslot.values, lslot.nvalues);
			}
			break;

		default:
			elog(ERROR, "unknown range operator %u", operator);
			hist_selec = -1.0;	/* keep compiler quiet */
			break;
	}

	free_attstatsslot(&lslot);
	free_attstatsslot(&hslot);

	return hist_selec;
}