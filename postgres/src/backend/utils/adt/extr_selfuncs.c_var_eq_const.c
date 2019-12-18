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
struct TYPE_11__ {int /*<<< orphan*/  statsTuple; TYPE_1__* rel; scalar_t__ isunique; } ;
typedef  TYPE_2__ VariableStatData ;
struct TYPE_13__ {int nvalues; double* numbers; int nnumbers; int /*<<< orphan*/ * values; int /*<<< orphan*/  stacoll; } ;
struct TYPE_12__ {double stanullfrac; } ;
struct TYPE_10__ {double tuples; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__* Form_pg_statistic ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_4__ AttStatsSlot ;

/* Variables and functions */
 int ATTSTATSSLOT_NUMBERS ; 
 int ATTSTATSSLOT_VALUES ; 
 int /*<<< orphan*/  CLAMP_PROBABILITY (double) ; 
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  STATISTIC_KIND_MCV ; 
 int /*<<< orphan*/  fmgr_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_attstatsslot (TYPE_4__*) ; 
 scalar_t__ get_attstatsslot (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_opcode (int /*<<< orphan*/ ) ; 
 double get_variable_numdistinct (TYPE_2__*,int*) ; 
 scalar_t__ statistic_proc_security_check (TYPE_2__*,int /*<<< orphan*/ ) ; 

double
var_eq_const(VariableStatData *vardata, Oid operator,
			 Datum constval, bool constisnull,
			 bool varonleft, bool negate)
{
	double		selec;
	double		nullfrac = 0.0;
	bool		isdefault;
	Oid			opfuncoid;

	/*
	 * If the constant is NULL, assume operator is strict and return zero, ie,
	 * operator will never return TRUE.  (It's zero even for a negator op.)
	 */
	if (constisnull)
		return 0.0;

	/*
	 * Grab the nullfrac for use below.  Note we allow use of nullfrac
	 * regardless of security check.
	 */
	if (HeapTupleIsValid(vardata->statsTuple))
	{
		Form_pg_statistic stats;

		stats = (Form_pg_statistic) GETSTRUCT(vardata->statsTuple);
		nullfrac = stats->stanullfrac;
	}

	/*
	 * If we matched the var to a unique index or DISTINCT clause, assume
	 * there is exactly one match regardless of anything else.  (This is
	 * slightly bogus, since the index or clause's equality operator might be
	 * different from ours, but it's much more likely to be right than
	 * ignoring the information.)
	 */
	if (vardata->isunique && vardata->rel && vardata->rel->tuples >= 1.0)
	{
		selec = 1.0 / vardata->rel->tuples;
	}
	else if (HeapTupleIsValid(vardata->statsTuple) &&
			 statistic_proc_security_check(vardata,
										   (opfuncoid = get_opcode(operator))))
	{
		AttStatsSlot sslot;
		bool		match = false;
		int			i;

		/*
		 * Is the constant "=" to any of the column's most common values?
		 * (Although the given operator may not really be "=", we will assume
		 * that seeing whether it returns TRUE is an appropriate test.  If you
		 * don't like this, maybe you shouldn't be using eqsel for your
		 * operator...)
		 */
		if (get_attstatsslot(&sslot, vardata->statsTuple,
							 STATISTIC_KIND_MCV, InvalidOid,
							 ATTSTATSSLOT_VALUES | ATTSTATSSLOT_NUMBERS))
		{
			FmgrInfo	eqproc;

			fmgr_info(opfuncoid, &eqproc);

			for (i = 0; i < sslot.nvalues; i++)
			{
				/* be careful to apply operator right way 'round */
				if (varonleft)
					match = DatumGetBool(FunctionCall2Coll(&eqproc,
														   sslot.stacoll,
														   sslot.values[i],
														   constval));
				else
					match = DatumGetBool(FunctionCall2Coll(&eqproc,
														   sslot.stacoll,
														   constval,
														   sslot.values[i]));
				if (match)
					break;
			}
		}
		else
		{
			/* no most-common-value info available */
			i = 0;				/* keep compiler quiet */
		}

		if (match)
		{
			/*
			 * Constant is "=" to this common value.  We know selectivity
			 * exactly (or as exactly as ANALYZE could calculate it, anyway).
			 */
			selec = sslot.numbers[i];
		}
		else
		{
			/*
			 * Comparison is against a constant that is neither NULL nor any
			 * of the common values.  Its selectivity cannot be more than
			 * this:
			 */
			double		sumcommon = 0.0;
			double		otherdistinct;

			for (i = 0; i < sslot.nnumbers; i++)
				sumcommon += sslot.numbers[i];
			selec = 1.0 - sumcommon - nullfrac;
			CLAMP_PROBABILITY(selec);

			/*
			 * and in fact it's probably a good deal less. We approximate that
			 * all the not-common values share this remaining fraction
			 * equally, so we divide by the number of other distinct values.
			 */
			otherdistinct = get_variable_numdistinct(vardata, &isdefault) -
				sslot.nnumbers;
			if (otherdistinct > 1)
				selec /= otherdistinct;

			/*
			 * Another cross-check: selectivity shouldn't be estimated as more
			 * than the least common "most common value".
			 */
			if (sslot.nnumbers > 0 && selec > sslot.numbers[sslot.nnumbers - 1])
				selec = sslot.numbers[sslot.nnumbers - 1];
		}

		free_attstatsslot(&sslot);
	}
	else
	{
		/*
		 * No ANALYZE stats available, so make a guess using estimated number
		 * of distinct values and assuming they are equally common. (The guess
		 * is unlikely to be very good, but we do know a few special cases.)
		 */
		selec = 1.0 / get_variable_numdistinct(vardata, &isdefault);
	}

	/* now adjust if we wanted <> rather than = */
	if (negate)
		selec = 1.0 - selec - nullfrac;

	/* result should be in range, but make sure... */
	CLAMP_PROBABILITY(selec);

	return selec;
}