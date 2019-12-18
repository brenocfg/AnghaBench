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
struct TYPE_10__ {scalar_t__ nnumbers; double* numbers; int /*<<< orphan*/ * values; } ;
struct TYPE_9__ {double stanullfrac; } ;
typedef  int /*<<< orphan*/  SpecialJoinInfo ;
typedef  int /*<<< orphan*/  Selectivity ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  JoinType ;
typedef  TYPE_2__* Form_pg_statistic ;
typedef  int BoolTestType ;
typedef  TYPE_3__ AttStatsSlot ;

/* Variables and functions */
 int ATTSTATSSLOT_NUMBERS ; 
 int ATTSTATSSLOT_VALUES ; 
 int /*<<< orphan*/  CLAMP_PROBABILITY (double) ; 
 double DEFAULT_NOT_UNK_SEL ; 
 double DEFAULT_UNK_SEL ; 
 scalar_t__ DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
#define  IS_FALSE 133 
#define  IS_NOT_FALSE 132 
#define  IS_NOT_TRUE 131 
#define  IS_NOT_UNKNOWN 130 
#define  IS_TRUE 129 
#define  IS_UNKNOWN 128 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ReleaseVariableStats (TYPE_1__) ; 
 int /*<<< orphan*/  STATISTIC_KIND_MCV ; 
 scalar_t__ clause_selectivity (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  examine_variable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  free_attstatsslot (TYPE_3__*) ; 
 scalar_t__ get_attstatsslot (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

Selectivity
booltestsel(PlannerInfo *root, BoolTestType booltesttype, Node *arg,
			int varRelid, JoinType jointype, SpecialJoinInfo *sjinfo)
{
	VariableStatData vardata;
	double		selec;

	examine_variable(root, arg, varRelid, &vardata);

	if (HeapTupleIsValid(vardata.statsTuple))
	{
		Form_pg_statistic stats;
		double		freq_null;
		AttStatsSlot sslot;

		stats = (Form_pg_statistic) GETSTRUCT(vardata.statsTuple);
		freq_null = stats->stanullfrac;

		if (get_attstatsslot(&sslot, vardata.statsTuple,
							 STATISTIC_KIND_MCV, InvalidOid,
							 ATTSTATSSLOT_VALUES | ATTSTATSSLOT_NUMBERS)
			&& sslot.nnumbers > 0)
		{
			double		freq_true;
			double		freq_false;

			/*
			 * Get first MCV frequency and derive frequency for true.
			 */
			if (DatumGetBool(sslot.values[0]))
				freq_true = sslot.numbers[0];
			else
				freq_true = 1.0 - sslot.numbers[0] - freq_null;

			/*
			 * Next derive frequency for false. Then use these as appropriate
			 * to derive frequency for each case.
			 */
			freq_false = 1.0 - freq_true - freq_null;

			switch (booltesttype)
			{
				case IS_UNKNOWN:
					/* select only NULL values */
					selec = freq_null;
					break;
				case IS_NOT_UNKNOWN:
					/* select non-NULL values */
					selec = 1.0 - freq_null;
					break;
				case IS_TRUE:
					/* select only TRUE values */
					selec = freq_true;
					break;
				case IS_NOT_TRUE:
					/* select non-TRUE values */
					selec = 1.0 - freq_true;
					break;
				case IS_FALSE:
					/* select only FALSE values */
					selec = freq_false;
					break;
				case IS_NOT_FALSE:
					/* select non-FALSE values */
					selec = 1.0 - freq_false;
					break;
				default:
					elog(ERROR, "unrecognized booltesttype: %d",
						 (int) booltesttype);
					selec = 0.0;	/* Keep compiler quiet */
					break;
			}

			free_attstatsslot(&sslot);
		}
		else
		{
			/*
			 * No most-common-value info available. Still have null fraction
			 * information, so use it for IS [NOT] UNKNOWN. Otherwise adjust
			 * for null fraction and assume a 50-50 split of TRUE and FALSE.
			 */
			switch (booltesttype)
			{
				case IS_UNKNOWN:
					/* select only NULL values */
					selec = freq_null;
					break;
				case IS_NOT_UNKNOWN:
					/* select non-NULL values */
					selec = 1.0 - freq_null;
					break;
				case IS_TRUE:
				case IS_FALSE:
					/* Assume we select half of the non-NULL values */
					selec = (1.0 - freq_null) / 2.0;
					break;
				case IS_NOT_TRUE:
				case IS_NOT_FALSE:
					/* Assume we select NULLs plus half of the non-NULLs */
					/* equiv. to freq_null + (1.0 - freq_null) / 2.0 */
					selec = (freq_null + 1.0) / 2.0;
					break;
				default:
					elog(ERROR, "unrecognized booltesttype: %d",
						 (int) booltesttype);
					selec = 0.0;	/* Keep compiler quiet */
					break;
			}
		}
	}
	else
	{
		/*
		 * If we can't get variable statistics for the argument, perhaps
		 * clause_selectivity can do something with it.  We ignore the
		 * possibility of a NULL value when using clause_selectivity, and just
		 * assume the value is either TRUE or FALSE.
		 */
		switch (booltesttype)
		{
			case IS_UNKNOWN:
				selec = DEFAULT_UNK_SEL;
				break;
			case IS_NOT_UNKNOWN:
				selec = DEFAULT_NOT_UNK_SEL;
				break;
			case IS_TRUE:
			case IS_NOT_FALSE:
				selec = (double) clause_selectivity(root, arg,
													varRelid,
													jointype, sjinfo);
				break;
			case IS_FALSE:
			case IS_NOT_TRUE:
				selec = 1.0 - (double) clause_selectivity(root, arg,
														  varRelid,
														  jointype, sjinfo);
				break;
			default:
				elog(ERROR, "unrecognized booltesttype: %d",
					 (int) booltesttype);
				selec = 0.0;	/* Keep compiler quiet */
				break;
		}
	}

	ReleaseVariableStats(vardata);

	/* result should be in range, but make sure... */
	CLAMP_PROBABILITY(selec);

	return (Selectivity) selec;
}