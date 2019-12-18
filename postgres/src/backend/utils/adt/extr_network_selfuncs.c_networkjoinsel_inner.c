#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mcv2_slot ;
typedef  int /*<<< orphan*/  mcv1_slot ;
typedef  int /*<<< orphan*/  hist2_slot ;
typedef  int /*<<< orphan*/  hist1_slot ;
struct TYPE_9__ {int /*<<< orphan*/  statsTuple; } ;
typedef  TYPE_1__ VariableStatData ;
struct TYPE_11__ {int /*<<< orphan*/  nvalues; int /*<<< orphan*/  values; int /*<<< orphan*/  numbers; } ;
struct TYPE_10__ {double stanullfrac; } ;
typedef  double Selectivity ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__* Form_pg_statistic ;
typedef  TYPE_3__ AttStatsSlot ;

/* Variables and functions */
 int ATTSTATSSLOT_NUMBERS ; 
 int ATTSTATSSLOT_VALUES ; 
 double DEFAULT_SEL (int /*<<< orphan*/ ) ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  MAX_CONSIDERED_ELEMS ; 
 int Min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATISTIC_KIND_HISTOGRAM ; 
 int /*<<< orphan*/  STATISTIC_KIND_MCV ; 
 int /*<<< orphan*/  free_attstatsslot (TYPE_3__*) ; 
 int get_attstatsslot (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 double inet_hist_inclusion_join_sel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 double inet_mcv_hist_sel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ inet_mcv_join_sel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int inet_opr_codenum (int /*<<< orphan*/ ) ; 
 double mcv_population (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Selectivity
networkjoinsel_inner(Oid operator,
					 VariableStatData *vardata1, VariableStatData *vardata2)
{
	Form_pg_statistic stats;
	double		nullfrac1 = 0.0,
				nullfrac2 = 0.0;
	Selectivity selec = 0.0,
				sumcommon1 = 0.0,
				sumcommon2 = 0.0;
	bool		mcv1_exists = false,
				mcv2_exists = false,
				hist1_exists = false,
				hist2_exists = false;
	int			opr_codenum;
	int			mcv1_length = 0,
				mcv2_length = 0;
	AttStatsSlot mcv1_slot;
	AttStatsSlot mcv2_slot;
	AttStatsSlot hist1_slot;
	AttStatsSlot hist2_slot;

	if (HeapTupleIsValid(vardata1->statsTuple))
	{
		stats = (Form_pg_statistic) GETSTRUCT(vardata1->statsTuple);
		nullfrac1 = stats->stanullfrac;

		mcv1_exists = get_attstatsslot(&mcv1_slot, vardata1->statsTuple,
									   STATISTIC_KIND_MCV, InvalidOid,
									   ATTSTATSSLOT_VALUES | ATTSTATSSLOT_NUMBERS);
		hist1_exists = get_attstatsslot(&hist1_slot, vardata1->statsTuple,
										STATISTIC_KIND_HISTOGRAM, InvalidOid,
										ATTSTATSSLOT_VALUES);
		/* Arbitrarily limit number of MCVs considered */
		mcv1_length = Min(mcv1_slot.nvalues, MAX_CONSIDERED_ELEMS);
		if (mcv1_exists)
			sumcommon1 = mcv_population(mcv1_slot.numbers, mcv1_length);
	}
	else
	{
		memset(&mcv1_slot, 0, sizeof(mcv1_slot));
		memset(&hist1_slot, 0, sizeof(hist1_slot));
	}

	if (HeapTupleIsValid(vardata2->statsTuple))
	{
		stats = (Form_pg_statistic) GETSTRUCT(vardata2->statsTuple);
		nullfrac2 = stats->stanullfrac;

		mcv2_exists = get_attstatsslot(&mcv2_slot, vardata2->statsTuple,
									   STATISTIC_KIND_MCV, InvalidOid,
									   ATTSTATSSLOT_VALUES | ATTSTATSSLOT_NUMBERS);
		hist2_exists = get_attstatsslot(&hist2_slot, vardata2->statsTuple,
										STATISTIC_KIND_HISTOGRAM, InvalidOid,
										ATTSTATSSLOT_VALUES);
		/* Arbitrarily limit number of MCVs considered */
		mcv2_length = Min(mcv2_slot.nvalues, MAX_CONSIDERED_ELEMS);
		if (mcv2_exists)
			sumcommon2 = mcv_population(mcv2_slot.numbers, mcv2_length);
	}
	else
	{
		memset(&mcv2_slot, 0, sizeof(mcv2_slot));
		memset(&hist2_slot, 0, sizeof(hist2_slot));
	}

	opr_codenum = inet_opr_codenum(operator);

	/*
	 * Calculate selectivity for MCV vs MCV matches.
	 */
	if (mcv1_exists && mcv2_exists)
		selec += inet_mcv_join_sel(mcv1_slot.values, mcv1_slot.numbers,
								   mcv1_length,
								   mcv2_slot.values, mcv2_slot.numbers,
								   mcv2_length,
								   operator);

	/*
	 * Add in selectivities for MCV vs histogram matches, scaling according to
	 * the fractions of the populations represented by the histograms. Note
	 * that the second case needs to commute the operator.
	 */
	if (mcv1_exists && hist2_exists)
		selec += (1.0 - nullfrac2 - sumcommon2) *
			inet_mcv_hist_sel(mcv1_slot.values, mcv1_slot.numbers, mcv1_length,
							  hist2_slot.values, hist2_slot.nvalues,
							  opr_codenum);
	if (mcv2_exists && hist1_exists)
		selec += (1.0 - nullfrac1 - sumcommon1) *
			inet_mcv_hist_sel(mcv2_slot.values, mcv2_slot.numbers, mcv2_length,
							  hist1_slot.values, hist1_slot.nvalues,
							  -opr_codenum);

	/*
	 * Add in selectivity for histogram vs histogram matches, again scaling
	 * appropriately.
	 */
	if (hist1_exists && hist2_exists)
		selec += (1.0 - nullfrac1 - sumcommon1) *
			(1.0 - nullfrac2 - sumcommon2) *
			inet_hist_inclusion_join_sel(hist1_slot.values, hist1_slot.nvalues,
										 hist2_slot.values, hist2_slot.nvalues,
										 opr_codenum);

	/*
	 * If useful statistics are not available then use the default estimate.
	 * We can apply null fractions if known, though.
	 */
	if ((!mcv1_exists && !hist1_exists) || (!mcv2_exists && !hist2_exists))
		selec = (1.0 - nullfrac1) * (1.0 - nullfrac2) * DEFAULT_SEL(operator);

	/* Release stats. */
	free_attstatsslot(&mcv1_slot);
	free_attstatsslot(&mcv2_slot);
	free_attstatsslot(&hist1_slot);
	free_attstatsslot(&hist2_slot);

	return selec;
}