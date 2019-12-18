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
struct TYPE_2__ {int pronargs; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_proc ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/  ARR_DATA_PTR (int /*<<< orphan*/ *) ; 
 int* ARR_DIMS (int /*<<< orphan*/ *) ; 
 scalar_t__ ARR_ELEMTYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ ARR_HASNULL (int /*<<< orphan*/ *) ; 
 int ARR_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Anum_pg_proc_protrftypes ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ OIDOID ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc (int) ; 

int
get_func_trftypes(HeapTuple procTup,
				  Oid **p_trftypes)
{
	Datum		protrftypes;
	ArrayType  *arr;
	int			nelems;
	bool		isNull;

	protrftypes = SysCacheGetAttr(PROCOID, procTup,
								  Anum_pg_proc_protrftypes,
								  &isNull);
	if (!isNull)
	{
		/*
		 * We expect the arrays to be 1-D arrays of the right types; verify
		 * that.  For the OID and char arrays, we don't need to use
		 * deconstruct_array() since the array data is just going to look like
		 * a C array of values.
		 */
		arr = DatumGetArrayTypeP(protrftypes);	/* ensure not toasted */
		nelems = ARR_DIMS(arr)[0];
		if (ARR_NDIM(arr) != 1 ||
			nelems < 0 ||
			ARR_HASNULL(arr) ||
			ARR_ELEMTYPE(arr) != OIDOID)
			elog(ERROR, "protrftypes is not a 1-D Oid array");
		Assert(nelems >= ((Form_pg_proc) GETSTRUCT(procTup))->pronargs);
		*p_trftypes = (Oid *) palloc(nelems * sizeof(Oid));
		memcpy(*p_trftypes, ARR_DATA_PTR(arr),
			   nelems * sizeof(Oid));

		return nelems;
	}
	else
		return 0;
}