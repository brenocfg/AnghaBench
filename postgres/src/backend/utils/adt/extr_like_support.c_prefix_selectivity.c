#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  statsTuple; } ;
typedef  TYPE_1__ VariableStatData ;
struct TYPE_13__ {int /*<<< orphan*/  stacoll; } ;
struct TYPE_12__ {int /*<<< orphan*/  constvalue; int /*<<< orphan*/  consttype; } ;
typedef  double Selectivity ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  TYPE_2__ Const ;
typedef  TYPE_3__ AttStatsSlot ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  BTGreaterEqualStrategyNumber ; 
 int /*<<< orphan*/  BTLessStrategyNumber ; 
 int /*<<< orphan*/  DEFAULT_COLLATION_OID ; 
 double DEFAULT_MATCH_SEL ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
 double Max (double,double) ; 
 int /*<<< orphan*/  STATISTIC_KIND_HISTOGRAM ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  fmgr_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ get_attstatsslot (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_opcode (scalar_t__) ; 
 scalar_t__ get_opfamily_member (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 double ineq_histogram_selectivity (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* make_greater_string (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 double var_eq_const (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static Selectivity
prefix_selectivity(PlannerInfo *root, VariableStatData *vardata,
				   Oid vartype, Oid opfamily, Const *prefixcon)
{
	Selectivity prefixsel;
	Oid			cmpopr;
	FmgrInfo	opproc;
	AttStatsSlot sslot;
	Const	   *greaterstrcon;
	Selectivity eq_sel;

	cmpopr = get_opfamily_member(opfamily, vartype, vartype,
								 BTGreaterEqualStrategyNumber);
	if (cmpopr == InvalidOid)
		elog(ERROR, "no >= operator for opfamily %u", opfamily);
	fmgr_info(get_opcode(cmpopr), &opproc);

	prefixsel = ineq_histogram_selectivity(root, vardata,
										   &opproc, true, true,
										   prefixcon->constvalue,
										   prefixcon->consttype);

	if (prefixsel < 0.0)
	{
		/* No histogram is present ... return a suitable default estimate */
		return DEFAULT_MATCH_SEL;
	}

	/*-------
	 * If we can create a string larger than the prefix, say
	 * "x < greaterstr".  We try to generate the string referencing the
	 * collation of the var's statistics, but if that's not available,
	 * use DEFAULT_COLLATION_OID.
	 *-------
	 */
	if (HeapTupleIsValid(vardata->statsTuple) &&
		get_attstatsslot(&sslot, vardata->statsTuple,
						 STATISTIC_KIND_HISTOGRAM, InvalidOid, 0))
		 /* sslot.stacoll is set up */ ;
	else
		sslot.stacoll = DEFAULT_COLLATION_OID;
	cmpopr = get_opfamily_member(opfamily, vartype, vartype,
								 BTLessStrategyNumber);
	if (cmpopr == InvalidOid)
		elog(ERROR, "no < operator for opfamily %u", opfamily);
	fmgr_info(get_opcode(cmpopr), &opproc);
	greaterstrcon = make_greater_string(prefixcon, &opproc, sslot.stacoll);
	if (greaterstrcon)
	{
		Selectivity topsel;

		topsel = ineq_histogram_selectivity(root, vardata,
											&opproc, false, false,
											greaterstrcon->constvalue,
											greaterstrcon->consttype);

		/* ineq_histogram_selectivity worked before, it shouldn't fail now */
		Assert(topsel >= 0.0);

		/*
		 * Merge the two selectivities in the same way as for a range query
		 * (see clauselist_selectivity()).  Note that we don't need to worry
		 * about double-exclusion of nulls, since ineq_histogram_selectivity
		 * doesn't count those anyway.
		 */
		prefixsel = topsel + prefixsel - 1.0;
	}

	/*
	 * If the prefix is long then the two bounding values might be too close
	 * together for the histogram to distinguish them usefully, resulting in a
	 * zero estimate (plus or minus roundoff error). To avoid returning a
	 * ridiculously small estimate, compute the estimated selectivity for
	 * "variable = 'foo'", and clamp to that. (Obviously, the resultant
	 * estimate should be at least that.)
	 *
	 * We apply this even if we couldn't make a greater string.  That case
	 * suggests that the prefix is near the maximum possible, and thus
	 * probably off the end of the histogram, and thus we probably got a very
	 * small estimate from the >= condition; so we still need to clamp.
	 */
	cmpopr = get_opfamily_member(opfamily, vartype, vartype,
								 BTEqualStrategyNumber);
	if (cmpopr == InvalidOid)
		elog(ERROR, "no = operator for opfamily %u", opfamily);
	eq_sel = var_eq_const(vardata, cmpopr, prefixcon->constvalue,
						  false, true, false);

	prefixsel = Max(prefixsel, eq_sel);

	return prefixsel;
}