#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hslot ;
struct TYPE_13__ {int /*<<< orphan*/  statsTuple; } ;
typedef  TYPE_1__ VariableStatData ;
struct TYPE_16__ {int /*<<< orphan*/  fn_oid; } ;
struct TYPE_14__ {TYPE_4__ cmp_proc_finfo; } ;
typedef  TYPE_2__ TypeCacheEntry ;
struct TYPE_17__ {int /*<<< orphan*/  nnumbers; int /*<<< orphan*/ * numbers; int /*<<< orphan*/  nvalues; int /*<<< orphan*/ * values; } ;
struct TYPE_15__ {double stanullfrac; } ;
typedef  double Selectivity ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__* Form_pg_statistic ;
typedef  TYPE_4__ FmgrInfo ;
typedef  scalar_t__ Datum ;
typedef  TYPE_5__ AttStatsSlot ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int ATTSTATSSLOT_NUMBERS ; 
 int ATTSTATSSLOT_VALUES ; 
 double DEFAULT_SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DatumGetArrayTypeP (scalar_t__) ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  OID_ARRAY_CONTAINED_OP ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATISTIC_KIND_DECHIST ; 
 int /*<<< orphan*/  STATISTIC_KIND_MCELEM ; 
 int /*<<< orphan*/  TYPECACHE_CMP_PROC_FINFO ; 
 int /*<<< orphan*/  free_attstatsslot (TYPE_5__*) ; 
 scalar_t__ get_attstatsslot (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* lookup_type_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double mcelem_array_selec (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 scalar_t__ statistic_proc_security_check (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Selectivity
calc_arraycontsel(VariableStatData *vardata, Datum constval,
				  Oid elemtype, Oid operator)
{
	Selectivity selec;
	TypeCacheEntry *typentry;
	FmgrInfo   *cmpfunc;
	ArrayType  *array;

	/* Get element type's default comparison function */
	typentry = lookup_type_cache(elemtype, TYPECACHE_CMP_PROC_FINFO);
	if (!OidIsValid(typentry->cmp_proc_finfo.fn_oid))
		return DEFAULT_SEL(operator);
	cmpfunc = &typentry->cmp_proc_finfo;

	/*
	 * The caller made sure the const is an array with same element type, so
	 * get it now
	 */
	array = DatumGetArrayTypeP(constval);

	if (HeapTupleIsValid(vardata->statsTuple) &&
		statistic_proc_security_check(vardata, cmpfunc->fn_oid))
	{
		Form_pg_statistic stats;
		AttStatsSlot sslot;
		AttStatsSlot hslot;

		stats = (Form_pg_statistic) GETSTRUCT(vardata->statsTuple);

		/* MCELEM will be an array of same type as column */
		if (get_attstatsslot(&sslot, vardata->statsTuple,
							 STATISTIC_KIND_MCELEM, InvalidOid,
							 ATTSTATSSLOT_VALUES | ATTSTATSSLOT_NUMBERS))
		{
			/*
			 * For "array <@ const" case we also need histogram of distinct
			 * element counts.
			 */
			if (operator != OID_ARRAY_CONTAINED_OP ||
				!get_attstatsslot(&hslot, vardata->statsTuple,
								  STATISTIC_KIND_DECHIST, InvalidOid,
								  ATTSTATSSLOT_NUMBERS))
				memset(&hslot, 0, sizeof(hslot));

			/* Use the most-common-elements slot for the array Var. */
			selec = mcelem_array_selec(array, typentry,
									   sslot.values, sslot.nvalues,
									   sslot.numbers, sslot.nnumbers,
									   hslot.numbers, hslot.nnumbers,
									   operator);

			free_attstatsslot(&hslot);
			free_attstatsslot(&sslot);
		}
		else
		{
			/* No most-common-elements info, so do without */
			selec = mcelem_array_selec(array, typentry,
									   NULL, 0, NULL, 0, NULL, 0,
									   operator);
		}

		/*
		 * MCE stats count only non-null rows, so adjust for null rows.
		 */
		selec *= (1.0 - stats->stanullfrac);
	}
	else
	{
		/* No stats at all, so do without */
		selec = mcelem_array_selec(array, typentry,
								   NULL, 0, NULL, 0, NULL, 0,
								   operator);
		/* we assume no nulls here, so no stanullfrac correction */
	}

	/* If constant was toasted, release the copy we made */
	if (PointerGetDatum(array) != constval)
		pfree(array);

	return selec;
}