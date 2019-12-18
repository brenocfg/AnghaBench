#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
typedef  scalar_t__ Pointer ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_constraint ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/  ARR_DATA_PTR (int /*<<< orphan*/ *) ; 
 int* ARR_DIMS (int /*<<< orphan*/ *) ; 
 scalar_t__ ARR_ELEMTYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ ARR_HASNULL (int /*<<< orphan*/ *) ; 
 int ARR_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Anum_pg_constraint_conffeqop ; 
 int /*<<< orphan*/  Anum_pg_constraint_confkey ; 
 int /*<<< orphan*/  Anum_pg_constraint_conkey ; 
 int /*<<< orphan*/  Anum_pg_constraint_conpfeqop ; 
 int /*<<< orphan*/  Anum_pg_constraint_conppeqop ; 
 int /*<<< orphan*/  CONSTROID ; 
 int /*<<< orphan*/ * DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int INDEX_MAX_KEYS ; 
 scalar_t__ INT2OID ; 
 scalar_t__ OIDOID ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

void
DeconstructFkConstraintRow(HeapTuple tuple, int *numfks,
						   AttrNumber *conkey, AttrNumber *confkey,
						   Oid *pf_eq_oprs, Oid *pp_eq_oprs, Oid *ff_eq_oprs)
{
	Oid			constrId;
	Datum		adatum;
	bool		isNull;
	ArrayType  *arr;
	int			numkeys;

	constrId = ((Form_pg_constraint) GETSTRUCT(tuple))->oid;

	/*
	 * We expect the arrays to be 1-D arrays of the right types; verify that.
	 * We don't need to use deconstruct_array() since the array data is just
	 * going to look like a C array of values.
	 */
	adatum = SysCacheGetAttr(CONSTROID, tuple,
							 Anum_pg_constraint_conkey, &isNull);
	if (isNull)
		elog(ERROR, "null conkey for constraint %u", constrId);
	arr = DatumGetArrayTypeP(adatum);	/* ensure not toasted */
	if (ARR_NDIM(arr) != 1 ||
		ARR_HASNULL(arr) ||
		ARR_ELEMTYPE(arr) != INT2OID)
		elog(ERROR, "conkey is not a 1-D smallint array");
	numkeys = ARR_DIMS(arr)[0];
	if (numkeys <= 0 || numkeys > INDEX_MAX_KEYS)
		elog(ERROR, "foreign key constraint cannot have %d columns", numkeys);
	memcpy(conkey, ARR_DATA_PTR(arr), numkeys * sizeof(int16));
	if ((Pointer) arr != DatumGetPointer(adatum))
		pfree(arr);				/* free de-toasted copy, if any */

	adatum = SysCacheGetAttr(CONSTROID, tuple,
							 Anum_pg_constraint_confkey, &isNull);
	if (isNull)
		elog(ERROR, "null confkey for constraint %u", constrId);
	arr = DatumGetArrayTypeP(adatum);	/* ensure not toasted */
	if (ARR_NDIM(arr) != 1 ||
		ARR_DIMS(arr)[0] != numkeys ||
		ARR_HASNULL(arr) ||
		ARR_ELEMTYPE(arr) != INT2OID)
		elog(ERROR, "confkey is not a 1-D smallint array");
	memcpy(confkey, ARR_DATA_PTR(arr), numkeys * sizeof(int16));
	if ((Pointer) arr != DatumGetPointer(adatum))
		pfree(arr);				/* free de-toasted copy, if any */

	if (pf_eq_oprs)
	{
		adatum = SysCacheGetAttr(CONSTROID, tuple,
								 Anum_pg_constraint_conpfeqop, &isNull);
		if (isNull)
			elog(ERROR, "null conpfeqop for constraint %u", constrId);
		arr = DatumGetArrayTypeP(adatum);	/* ensure not toasted */
		/* see TryReuseForeignKey if you change the test below */
		if (ARR_NDIM(arr) != 1 ||
			ARR_DIMS(arr)[0] != numkeys ||
			ARR_HASNULL(arr) ||
			ARR_ELEMTYPE(arr) != OIDOID)
			elog(ERROR, "conpfeqop is not a 1-D Oid array");
		memcpy(pf_eq_oprs, ARR_DATA_PTR(arr), numkeys * sizeof(Oid));
		if ((Pointer) arr != DatumGetPointer(adatum))
			pfree(arr);			/* free de-toasted copy, if any */
	}

	if (pp_eq_oprs)
	{
		adatum = SysCacheGetAttr(CONSTROID, tuple,
								 Anum_pg_constraint_conppeqop, &isNull);
		if (isNull)
			elog(ERROR, "null conppeqop for constraint %u", constrId);
		arr = DatumGetArrayTypeP(adatum);	/* ensure not toasted */
		if (ARR_NDIM(arr) != 1 ||
			ARR_DIMS(arr)[0] != numkeys ||
			ARR_HASNULL(arr) ||
			ARR_ELEMTYPE(arr) != OIDOID)
			elog(ERROR, "conppeqop is not a 1-D Oid array");
		memcpy(pp_eq_oprs, ARR_DATA_PTR(arr), numkeys * sizeof(Oid));
		if ((Pointer) arr != DatumGetPointer(adatum))
			pfree(arr);			/* free de-toasted copy, if any */
	}

	if (ff_eq_oprs)
	{
		adatum = SysCacheGetAttr(CONSTROID, tuple,
								 Anum_pg_constraint_conffeqop, &isNull);
		if (isNull)
			elog(ERROR, "null conffeqop for constraint %u", constrId);
		arr = DatumGetArrayTypeP(adatum);	/* ensure not toasted */
		if (ARR_NDIM(arr) != 1 ||
			ARR_DIMS(arr)[0] != numkeys ||
			ARR_HASNULL(arr) ||
			ARR_ELEMTYPE(arr) != OIDOID)
			elog(ERROR, "conffeqop is not a 1-D Oid array");
		memcpy(ff_eq_oprs, ARR_DATA_PTR(arr), numkeys * sizeof(Oid));
		if ((Pointer) arr != DatumGetPointer(adatum))
			pfree(arr);			/* free de-toasted copy, if any */
	}

	*numfks = numkeys;
}