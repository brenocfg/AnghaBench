#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  statsTuple; } ;
typedef  TYPE_1__ VariableStatData ;
struct TYPE_14__ {int /*<<< orphan*/  nnumbers; int /*<<< orphan*/  numbers; int /*<<< orphan*/  nvalues; int /*<<< orphan*/  values; } ;
struct TYPE_13__ {double stanullfrac; } ;
struct TYPE_12__ {scalar_t__ size; } ;
typedef  TYPE_2__* TSQuery ;
typedef  double Selectivity ;
typedef  TYPE_3__* Form_pg_statistic ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_4__ AttStatsSlot ;

/* Variables and functions */
 int ATTSTATSSLOT_NUMBERS ; 
 int ATTSTATSSLOT_VALUES ; 
 TYPE_2__* DatumGetTSQuery (int /*<<< orphan*/ ) ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  STATISTIC_KIND_MCELEM ; 
 int /*<<< orphan*/  free_attstatsslot (TYPE_4__*) ; 
 scalar_t__ get_attstatsslot (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 double mcelem_tsquery_selec (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double tsquery_opr_selec_no_stats (TYPE_2__*) ; 

__attribute__((used)) static Selectivity
tsquerysel(VariableStatData *vardata, Datum constval)
{
	Selectivity selec;
	TSQuery		query;

	/* The caller made sure the const is a TSQuery, so get it now */
	query = DatumGetTSQuery(constval);

	/* Empty query matches nothing */
	if (query->size == 0)
		return (Selectivity) 0.0;

	if (HeapTupleIsValid(vardata->statsTuple))
	{
		Form_pg_statistic stats;
		AttStatsSlot sslot;

		stats = (Form_pg_statistic) GETSTRUCT(vardata->statsTuple);

		/* MCELEM will be an array of TEXT elements for a tsvector column */
		if (get_attstatsslot(&sslot, vardata->statsTuple,
							 STATISTIC_KIND_MCELEM, InvalidOid,
							 ATTSTATSSLOT_VALUES | ATTSTATSSLOT_NUMBERS))
		{
			/*
			 * There is a most-common-elements slot for the tsvector Var, so
			 * use that.
			 */
			selec = mcelem_tsquery_selec(query, sslot.values, sslot.nvalues,
										 sslot.numbers, sslot.nnumbers);
			free_attstatsslot(&sslot);
		}
		else
		{
			/* No most-common-elements info, so do without */
			selec = tsquery_opr_selec_no_stats(query);
		}

		/*
		 * MCE stats count only non-null rows, so adjust for null rows.
		 */
		selec *= (1.0 - stats->stanullfrac);
	}
	else
	{
		/* No stats at all, so do without */
		selec = tsquery_opr_selec_no_stats(query);
		/* we assume no nulls here, so no stanullfrac correction */
	}

	return selec;
}