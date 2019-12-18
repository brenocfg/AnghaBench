#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  statsTuple; } ;
typedef  TYPE_1__ VariableStatData ;
struct TYPE_10__ {scalar_t__ stanullfrac; } ;
struct TYPE_9__ {int /*<<< orphan*/  opno; } ;
typedef  double Selectivity ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_2__ OpExpr ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_3__* Form_pg_statistic ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BTEqualStrategyNumber ; 
 int const BTGreaterEqualStrategyNumber ; 
#define  BTGreaterStrategyNumber 129 
 int const BTLessEqualStrategyNumber ; 
#define  BTLessStrategyNumber 128 
 int /*<<< orphan*/  CLAMP_PROBABILITY (double) ; 
 double DEFAULT_INEQ_SEL ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseVariableStats (TYPE_1__) ; 
 int /*<<< orphan*/  examine_variable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * get_leftop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_op_opfamily_properties (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_opfamily_member (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/ * get_rightop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_variable_range (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_opclause (int /*<<< orphan*/ *) ; 
 double scalarineqsel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mergejoinscansel(PlannerInfo *root, Node *clause,
				 Oid opfamily, int strategy, bool nulls_first,
				 Selectivity *leftstart, Selectivity *leftend,
				 Selectivity *rightstart, Selectivity *rightend)
{
	Node	   *left,
			   *right;
	VariableStatData leftvar,
				rightvar;
	int			op_strategy;
	Oid			op_lefttype;
	Oid			op_righttype;
	Oid			opno,
				lsortop,
				rsortop,
				lstatop,
				rstatop,
				ltop,
				leop,
				revltop,
				revleop;
	bool		isgt;
	Datum		leftmin,
				leftmax,
				rightmin,
				rightmax;
	double		selec;

	/* Set default results if we can't figure anything out. */
	/* XXX should default "start" fraction be a bit more than 0? */
	*leftstart = *rightstart = 0.0;
	*leftend = *rightend = 1.0;

	/* Deconstruct the merge clause */
	if (!is_opclause(clause))
		return;					/* shouldn't happen */
	opno = ((OpExpr *) clause)->opno;
	left = get_leftop((Expr *) clause);
	right = get_rightop((Expr *) clause);
	if (!right)
		return;					/* shouldn't happen */

	/* Look for stats for the inputs */
	examine_variable(root, left, 0, &leftvar);
	examine_variable(root, right, 0, &rightvar);

	/* Extract the operator's declared left/right datatypes */
	get_op_opfamily_properties(opno, opfamily, false,
							   &op_strategy,
							   &op_lefttype,
							   &op_righttype);
	Assert(op_strategy == BTEqualStrategyNumber);

	/*
	 * Look up the various operators we need.  If we don't find them all, it
	 * probably means the opfamily is broken, but we just fail silently.
	 *
	 * Note: we expect that pg_statistic histograms will be sorted by the '<'
	 * operator, regardless of which sort direction we are considering.
	 */
	switch (strategy)
	{
		case BTLessStrategyNumber:
			isgt = false;
			if (op_lefttype == op_righttype)
			{
				/* easy case */
				ltop = get_opfamily_member(opfamily,
										   op_lefttype, op_righttype,
										   BTLessStrategyNumber);
				leop = get_opfamily_member(opfamily,
										   op_lefttype, op_righttype,
										   BTLessEqualStrategyNumber);
				lsortop = ltop;
				rsortop = ltop;
				lstatop = lsortop;
				rstatop = rsortop;
				revltop = ltop;
				revleop = leop;
			}
			else
			{
				ltop = get_opfamily_member(opfamily,
										   op_lefttype, op_righttype,
										   BTLessStrategyNumber);
				leop = get_opfamily_member(opfamily,
										   op_lefttype, op_righttype,
										   BTLessEqualStrategyNumber);
				lsortop = get_opfamily_member(opfamily,
											  op_lefttype, op_lefttype,
											  BTLessStrategyNumber);
				rsortop = get_opfamily_member(opfamily,
											  op_righttype, op_righttype,
											  BTLessStrategyNumber);
				lstatop = lsortop;
				rstatop = rsortop;
				revltop = get_opfamily_member(opfamily,
											  op_righttype, op_lefttype,
											  BTLessStrategyNumber);
				revleop = get_opfamily_member(opfamily,
											  op_righttype, op_lefttype,
											  BTLessEqualStrategyNumber);
			}
			break;
		case BTGreaterStrategyNumber:
			/* descending-order case */
			isgt = true;
			if (op_lefttype == op_righttype)
			{
				/* easy case */
				ltop = get_opfamily_member(opfamily,
										   op_lefttype, op_righttype,
										   BTGreaterStrategyNumber);
				leop = get_opfamily_member(opfamily,
										   op_lefttype, op_righttype,
										   BTGreaterEqualStrategyNumber);
				lsortop = ltop;
				rsortop = ltop;
				lstatop = get_opfamily_member(opfamily,
											  op_lefttype, op_lefttype,
											  BTLessStrategyNumber);
				rstatop = lstatop;
				revltop = ltop;
				revleop = leop;
			}
			else
			{
				ltop = get_opfamily_member(opfamily,
										   op_lefttype, op_righttype,
										   BTGreaterStrategyNumber);
				leop = get_opfamily_member(opfamily,
										   op_lefttype, op_righttype,
										   BTGreaterEqualStrategyNumber);
				lsortop = get_opfamily_member(opfamily,
											  op_lefttype, op_lefttype,
											  BTGreaterStrategyNumber);
				rsortop = get_opfamily_member(opfamily,
											  op_righttype, op_righttype,
											  BTGreaterStrategyNumber);
				lstatop = get_opfamily_member(opfamily,
											  op_lefttype, op_lefttype,
											  BTLessStrategyNumber);
				rstatop = get_opfamily_member(opfamily,
											  op_righttype, op_righttype,
											  BTLessStrategyNumber);
				revltop = get_opfamily_member(opfamily,
											  op_righttype, op_lefttype,
											  BTGreaterStrategyNumber);
				revleop = get_opfamily_member(opfamily,
											  op_righttype, op_lefttype,
											  BTGreaterEqualStrategyNumber);
			}
			break;
		default:
			goto fail;			/* shouldn't get here */
	}

	if (!OidIsValid(lsortop) ||
		!OidIsValid(rsortop) ||
		!OidIsValid(lstatop) ||
		!OidIsValid(rstatop) ||
		!OidIsValid(ltop) ||
		!OidIsValid(leop) ||
		!OidIsValid(revltop) ||
		!OidIsValid(revleop))
		goto fail;				/* insufficient info in catalogs */

	/* Try to get ranges of both inputs */
	if (!isgt)
	{
		if (!get_variable_range(root, &leftvar, lstatop,
								&leftmin, &leftmax))
			goto fail;			/* no range available from stats */
		if (!get_variable_range(root, &rightvar, rstatop,
								&rightmin, &rightmax))
			goto fail;			/* no range available from stats */
	}
	else
	{
		/* need to swap the max and min */
		if (!get_variable_range(root, &leftvar, lstatop,
								&leftmax, &leftmin))
			goto fail;			/* no range available from stats */
		if (!get_variable_range(root, &rightvar, rstatop,
								&rightmax, &rightmin))
			goto fail;			/* no range available from stats */
	}

	/*
	 * Now, the fraction of the left variable that will be scanned is the
	 * fraction that's <= the right-side maximum value.  But only believe
	 * non-default estimates, else stick with our 1.0.
	 */
	selec = scalarineqsel(root, leop, isgt, true, &leftvar,
						  rightmax, op_righttype);
	if (selec != DEFAULT_INEQ_SEL)
		*leftend = selec;

	/* And similarly for the right variable. */
	selec = scalarineqsel(root, revleop, isgt, true, &rightvar,
						  leftmax, op_lefttype);
	if (selec != DEFAULT_INEQ_SEL)
		*rightend = selec;

	/*
	 * Only one of the two "end" fractions can really be less than 1.0;
	 * believe the smaller estimate and reset the other one to exactly 1.0. If
	 * we get exactly equal estimates (as can easily happen with self-joins),
	 * believe neither.
	 */
	if (*leftend > *rightend)
		*leftend = 1.0;
	else if (*leftend < *rightend)
		*rightend = 1.0;
	else
		*leftend = *rightend = 1.0;

	/*
	 * Also, the fraction of the left variable that will be scanned before the
	 * first join pair is found is the fraction that's < the right-side
	 * minimum value.  But only believe non-default estimates, else stick with
	 * our own default.
	 */
	selec = scalarineqsel(root, ltop, isgt, false, &leftvar,
						  rightmin, op_righttype);
	if (selec != DEFAULT_INEQ_SEL)
		*leftstart = selec;

	/* And similarly for the right variable. */
	selec = scalarineqsel(root, revltop, isgt, false, &rightvar,
						  leftmin, op_lefttype);
	if (selec != DEFAULT_INEQ_SEL)
		*rightstart = selec;

	/*
	 * Only one of the two "start" fractions can really be more than zero;
	 * believe the larger estimate and reset the other one to exactly 0.0. If
	 * we get exactly equal estimates (as can easily happen with self-joins),
	 * believe neither.
	 */
	if (*leftstart < *rightstart)
		*leftstart = 0.0;
	else if (*leftstart > *rightstart)
		*rightstart = 0.0;
	else
		*leftstart = *rightstart = 0.0;

	/*
	 * If the sort order is nulls-first, we're going to have to skip over any
	 * nulls too.  These would not have been counted by scalarineqsel, and we
	 * can safely add in this fraction regardless of whether we believe
	 * scalarineqsel's results or not.  But be sure to clamp the sum to 1.0!
	 */
	if (nulls_first)
	{
		Form_pg_statistic stats;

		if (HeapTupleIsValid(leftvar.statsTuple))
		{
			stats = (Form_pg_statistic) GETSTRUCT(leftvar.statsTuple);
			*leftstart += stats->stanullfrac;
			CLAMP_PROBABILITY(*leftstart);
			*leftend += stats->stanullfrac;
			CLAMP_PROBABILITY(*leftend);
		}
		if (HeapTupleIsValid(rightvar.statsTuple))
		{
			stats = (Form_pg_statistic) GETSTRUCT(rightvar.statsTuple);
			*rightstart += stats->stanullfrac;
			CLAMP_PROBABILITY(*rightstart);
			*rightend += stats->stanullfrac;
			CLAMP_PROBABILITY(*rightend);
		}
	}

	/* Disbelieve start >= end, just in case that can happen */
	if (*leftstart >= *leftend)
	{
		*leftstart = 0.0;
		*leftend = 1.0;
	}
	if (*rightstart >= *rightend)
	{
		*rightstart = 0.0;
		*rightend = 1.0;
	}

fail:
	ReleaseVariableStats(leftvar);
	ReleaseVariableStats(rightvar);
}